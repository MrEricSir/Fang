#include "RSSAtomParser.h"
#include "FeedDateParser.h"
#include "FeedParserLogging.h"

// Returns true if the string contains only whitespace (or is empty).
static bool isBlankOrEmpty(const QString& s)
{
    return QStringView(s).trimmed().isEmpty();
}

// Some feeds (e.g. excelsior.com.mx) double-escape CDATA markers, producing
// literal "<![CDATA[...]]>" text instead of actual CDATA sections. Strip them.
static QString stripEscapedCDATA(const QString& text)
{
    QStringView view = QStringView(text).trimmed();
    if (view.startsWith(u"<![CDATA[") && view.endsWith(u"]]>")) {
        return view.mid(9, view.size() - 12).trimmed().toString();
    }
    return text;
}

std::unique_ptr<RawFeed> RSSAtomParser::parse(const QByteArray& data)
{
    RSSAtomParser worker;
    worker.feed = std::make_unique<RawFeed>();
    worker.isValid = true;

    worker.xml.addData(data);
    while (!worker.xml.atEnd()) {
        worker.xml.readNext();
        if (worker.xml.isStartElement()) {
            worker.elementStart();
        } else if (worker.xml.isEndElement()) {
            worker.elementEnd();
        } else if (worker.xml.isCharacters() && !worker.xml.isWhitespace()) {
            worker.elementContents();
        }
    }

    if (worker.xml.error()
        && worker.xml.error() != QXmlStreamReader::PrematureEndOfDocumentError
        && worker.xml.error() != QXmlStreamReader::NotWellFormedError) {
        worker.isValid = false;
        qCWarning(logFeedParser) << "XML ERROR:" << worker.xml.lineNumber()
                                 << ": " << worker.xml.errorString();
    }

    if (!worker.isValid) {
        return nullptr;
    }

    if (worker.feed->items.size() == 0) {
        worker.saveSummary();
    }

    // No items and no feed title means we never found RSS/Atom content.
    if (worker.feed->items.isEmpty() && worker.feed->title.isEmpty()) {
        return nullptr;
    }

    return std::move(worker.feed);
}

void RSSAtomParser::elementStart()
{
    QString tagName = xml.name().toString().toLower();

    if ((tagName == "item" || tagName == "entry") && !state.inAtomXHTML) {

        if (state.urlHref.isEmpty()) {
            state.urlHref = xml.attributes().value("rss:about").toString();
        }

        if (state.numItems == 0) {
            saveSummary();
        }

        currentItem = std::make_shared<RawNews>();
        state.numItems++;
    } else if ((tagName == "content" || tagName == "summary") &&
               xml.attributes().value("type").toString().toLower() == "xhtml") {
        state.inAtomXHTML = true;
        state.content.reserve(4096);
    } else if (state.inAtomXHTML) {
        // Rebuild the XHTML tag directly into content (no temporaries).
        state.content.append('<');
        state.content.append(xml.qualifiedName());
        for (const auto& attribute : xml.attributes()) {
            state.content.append(' ');
            state.content.append(attribute.name());
            state.content.append(QStringLiteral("=\""));
            state.content.append(attribute.value());
            state.content.append('"');
        }
        state.content.append('>');

        return;
    }

    state.currentTag = tagName;
    state.currentPrefix = xml.prefix().toString().toLower();
    state.hasType = xml.attributes().hasAttribute("type");

    // Podcast detection: only flag itunes elements that are specific to actual
    // podcast feeds. Many non-podcast feeds (e.g. Substack blogs) include generic
    // itunes metadata like itunes:owner, itunes:author, and itunes:block.
    if (state.currentPrefix == "itunes") {
        if (state.currentTag == "duration" || state.currentTag == "episode"
                || state.currentTag == "episodetype" || state.currentTag == "season"
                || state.currentTag == "explicit" || state.currentTag == "category") {
            state.hasPodcastSignals = true;
        }
    }

    // Podcast detection: audio enclosures.
    if (state.currentTag == "enclosure") {
        QString type = xml.attributes().value("type").toString().toLower();
        if (type.startsWith("audio/")) {
            state.hasPodcastSignals = true;
        }
    }

    // Media RSS image extraction (media:thumbnail and media:content).
    if (currentItem && state.currentPrefix == "media") {
        if (state.currentTag == "thumbnail") {
            QString url = xml.attributes().value("url").toString();
            int width = xml.attributes().value("width").toString().toInt();
            if (!url.isEmpty() && (state.mediaImageURL.isEmpty() || width > state.mediaImageWidth)) {
                state.mediaImageURL = url;
                state.mediaImageWidth = width;
            }
        } else if (state.currentTag == "content") {
            QString type = xml.attributes().value("type").toString().toLower();
            if (type.startsWith("image/")) {
                QString url = xml.attributes().value("url").toString();
                int width = xml.attributes().value("width").toString().toInt();
                if (!url.isEmpty() && (state.mediaImageURL.isEmpty() || width > state.mediaImageWidth)) {
                    state.mediaImageURL = url;
                    state.mediaImageWidth = width;
                }
            }
        }
    }

    if (state.currentTag == "link" && state.urlHref.isEmpty() && xml.attributes().hasAttribute("href")) {
        state.urlHref = xml.attributes().value("href").toString();
    }

    state.tagStack.push(tagName);
}

void RSSAtomParser::elementEnd()
{
    if (!state.inAtomXHTML) {
        state.tagStack.pop();
    }

    QString tagName = xml.name().toString().toLower();

    if ((tagName == "item" || tagName == "entry") && !state.inAtomXHTML) {
        if (!currentItem) {
            qCWarning(logFeedParser) << "Current item is null!";
            qCWarning(logFeedParser) << "Current title: " << state.title;
            qCWarning(logFeedParser) << "Xml element: " << tagName;
            return;
        }

        // Figure out which date to use.
        QString timestamp;
        if (!isBlankOrEmpty(state.pubdate)) {
            timestamp = state.pubdate;
        } else if (!isBlankOrEmpty(state.lastbuilddate)) {
            timestamp = state.lastbuilddate;
        } else if (!isBlankOrEmpty(state.created)) {
            timestamp = state.created;
        } else if (!isBlankOrEmpty(state.date)) {
            timestamp = state.date;
        } else if (!isBlankOrEmpty(state.updated)) {
            timestamp = state.updated;
        }

        // Determine the GUID.
        QString myGuid;
        if (!isBlankOrEmpty(state.id)) {
            myGuid = state.id.trimmed();
        } else if (!isBlankOrEmpty(state.guid)) {
            myGuid = state.guid.trimmed();
        } else if (!isBlankOrEmpty(state.urlData)) {
            myGuid = state.urlData.trimmed();
        } else {
            myGuid = state.urlHref.trimmed();
        }

        // Skip items without a GUID - malformed feed
        if (myGuid.isEmpty()) {
            qCWarning(logFeedParser) << "RSSAtomParser: RSS/Atom item missing GUID/URL, skipping item";
            qCWarning(logFeedParser) << "  Title:" << state.title;
            currentItem.reset();
            state.clearItemFields();
            return;
        }

        // Item space.
        currentItem->author = state.author;
        currentItem->title = stripEscapedCDATA(state.title);
        currentItem->description = stripEscapedCDATA(state.subtitle);
        currentItem->content = stripEscapedCDATA(state.content);

        currentItem->mediaImageURL = state.mediaImageURL;

        currentItem->url = state.urlData.isEmpty() ? QUrl(state.urlHref) : QUrl(state.urlData);
        currentItem->timestamp = FeedDateParser::dateFromFeedString(timestamp);
        currentItem->guid = myGuid;

        if (!currentItem->timestamp.isValid()) {
            qCDebug(logFeedParser) << "Time string: " << timestamp;
            qCDebug(logFeedParser) << "invalid date!";
        }


        feed->items.append(currentItem);
        feed->isPodcast = feed->isPodcast || state.hasPodcastSignals;
        currentItem.reset();

        state.clearItemFields();
    } else if (tagName == "content" || tagName == "summary") {
        if (state.inAtomXHTML) {
            state.inAtomXHTML = false;
            state.tagStack.pop();
        }
    }

    if (state.inAtomXHTML) {
        state.content.append(QStringLiteral("</"));
        state.content.append(xml.qualifiedName());
        state.content.append('>');
    }
}

void RSSAtomParser::elementContents()
{
    if (state.inAtomXHTML) {
        state.content += xml.text().toString();
        return;
    }

    QStringView parentTag = getTagStackAt(1);
    if (parentTag == u"item" || parentTag == u"entry") {
        //
        // Inside a news item.
        //

        if (state.currentTag == "title" && state.currentPrefix == "") {
            state.title += xml.text().toString();
        } else if (state.currentTag == "link" && state.currentPrefix == "") {
            state.urlData += xml.text().toString();
        } else if ((state.currentTag == "description" || state.currentTag == "summary")
                   && state.currentPrefix == "") {
            state.subtitle += xml.text().toString();
        } else if (state.currentTag == "name"
                   || (state.currentTag == "creator" && state.currentPrefix == "dc")) {
            state.author += xml.text().toString();
        } else if (state.currentTag == "pubdate") {
            state.pubdate += xml.text().toString();
        } else if (state.currentTag == "lastbuilddate") {
            state.lastbuilddate += xml.text().toString();
        } else if (state.currentTag == "created") {
            state.created += xml.text().toString();
        } else if (state.currentTag == "updated") {
            state.updated += xml.text().toString();
        } else if (state.currentTag == "date") {
            state.date += xml.text().toString();
        } else if (state.currentTag == "guid") {
            state.guid += xml.text().toString();
        } else if (state.currentTag == "id") {
            state.id += xml.text().toString();
        } else if ((state.currentTag == "encoded" && state.currentPrefix == "content")
                   || (state.currentTag == "content" && state.hasType)) {
            state.content += xml.text().toString();
        }
    } else if (parentTag == u"channel" || parentTag == u"feed") {
        //
        // Top level items.
        //

        if (state.currentTag == "title" && state.currentPrefix == "") {
            state.title += xml.text().toString();
        } else if (state.currentTag == "link" && state.currentPrefix == "") {
            state.urlData += xml.text().toString();
        } else if ((state.currentTag == "description" || state.currentTag == "summary")
                   && state.currentPrefix == "") {
            state.subtitle += xml.text().toString();
        }
    }
}

void RSSAtomParser::ParseState::clearItemFields()
{
    title.clear();
    subtitle.clear();
    content.clear();
    author.clear();
    urlHref.clear();
    urlData.clear();
    pubdate.clear();
    lastbuilddate.clear();
    created.clear();
    updated.clear();
    date.clear();
    guid.clear();
    id.clear();
    mediaImageURL.clear();
    mediaImageWidth = 0;
}

void RSSAtomParser::saveSummary()
{
    feed->title = state.title;
    feed->subtitle = state.subtitle;
    feed->siteURL = state.urlData.isEmpty() ? QUrl(state.urlHref) : QUrl(state.urlData);
    feed->isPodcast = state.hasPodcastSignals;

    state.clearItemFields();
}


QStringView RSSAtomParser::getTagStackAt(qint32 n)
{
    if (state.tagStack.isEmpty() || (state.tagStack.size() - 1) < n) {
        return QStringView();
    }

    return state.tagStack.at(state.tagStack.size() - 1 - n);
}
