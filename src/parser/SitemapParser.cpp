#include "SitemapParser.h"

#include <QXmlStreamReader>

#include "FeedParserLogging.h"

SitemapParser::SitemapParser()
    : _hasNewsEntries(false)
{
}

SitemapParser::SitemapType SitemapParser::parse(const QString& xml)
{
    _entries.clear();
    _subSitemaps.clear();
    _hasNewsEntries = false;

    QXmlStreamReader reader(xml);
    return parseImpl(reader);
}

SitemapParser::SitemapType SitemapParser::parse(const QByteArray& data)
{
    _entries.clear();
    _subSitemaps.clear();
    _hasNewsEntries = false;

    QXmlStreamReader reader(data);
    return parseImpl(reader);
}

SitemapParser::SitemapType SitemapParser::parseImpl(QXmlStreamReader& reader)
{
    // Find the root element.
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            QString root = reader.name().toString().toLower();
            if (root == "urlset") {
                parseUrlSet(reader);
                return UrlSet;
            } else if (root == "sitemapindex") {
                parseSitemapIndex(reader);
                return SitemapIndex;
            } else {
                qCDebug(logFeedParser) << "SitemapParser: unexpected root element:" << root;
                return Invalid;
            }
        }
    }

    qCDebug(logFeedParser) << "SitemapParser: no root element found";
    return Invalid;
}

void SitemapParser::parseUrlSet(QXmlStreamReader& xml)
{
    // We're inside <urlset>. Look for <url> children.
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement() && xml.name().toString().toLower() == "url") {
            SitemapEntry entry;

            // Parse children of <url>. This includes both standard sitemap
            // elements (<loc>, <lastmod>) and Google News extension elements
            // nested inside <news:news>.
            int depth = 1; // Track nesting depth within <url>
            while (!xml.atEnd() && depth > 0) {
                xml.readNext();

                if (xml.isEndElement()) {
                    if (xml.name().toString().toLower() == "url") {
                        depth = 0;
                    }
                }

                if (xml.isStartElement()) {
                    // The namespace-qualified local names come through as just
                    // the local part (e.g. "title" for news:title), so we use
                    // the qualified name to distinguish.
                    QString localName = xml.name().toString().toLower();
                    QString qualifiedName = xml.qualifiedName().toString().toLower();

                    if (localName == "loc" && !qualifiedName.contains(':')) {
                        entry.url = QUrl(xml.readElementText().trimmed());
                    } else if (localName == "lastmod" && !qualifiedName.contains(':')) {
                        entry.lastmod = QDateTime::fromString(
                            xml.readElementText().trimmed(), Qt::ISODate);
                    } else if (qualifiedName == "news:title"
                               || (localName == "title"
                                   && xml.namespaceUri().toString().contains("sitemap-news"))) {
                        entry.newsTitle = xml.readElementText().trimmed();
                    } else if (qualifiedName == "news:publication_date"
                               || (localName == "publication_date"
                                   && xml.namespaceUri().toString().contains("sitemap-news"))) {
                        entry.publicationDate = QDateTime::fromString(
                            xml.readElementText().trimmed(), Qt::ISODate);
                    } else if (qualifiedName == "news:language"
                               || (localName == "language"
                                   && xml.namespaceUri().toString().contains("sitemap-news"))) {
                        entry.language = xml.readElementText().trimmed().toLower();
                    } else if (qualifiedName == "news:name"
                               || (localName == "name"
                                   && xml.namespaceUri().toString().contains("sitemap-news"))) {
                        entry.publicationName = xml.readElementText().trimmed();
                    } else if (qualifiedName == "image:loc"
                               || (localName == "loc"
                                   && xml.namespaceUri().toString().contains("sitemap-image"))) {
                        entry.imageUrl = QUrl(xml.readElementText().trimmed());
                    }
                }
            }

            if (entry.url.isValid()) {
                if (!entry.newsTitle.isEmpty()) {
                    _hasNewsEntries = true;
                }
                _entries.append(entry);
            }
        }
    }

    qCDebug(logFeedParser) << "SitemapParser: parsed" << _entries.size() << "URL entries"
                        << (_hasNewsEntries ? "(with news extensions)" : "(no news extensions)");
}

void SitemapParser::parseSitemapIndex(QXmlStreamReader& xml)
{
    // We're inside <sitemapindex>. Look for <sitemap> children.
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement() && xml.name().toString().toLower() == "sitemap") {
            SubSitemap sub;

            // Parse children of <sitemap>.
            while (!xml.atEnd()) {
                xml.readNext();

                if (xml.isEndElement() && xml.name().toString().toLower() == "sitemap") {
                    break;
                }

                if (xml.isStartElement()) {
                    QString tag = xml.name().toString().toLower();
                    if (tag == "loc") {
                        sub.url = QUrl(xml.readElementText().trimmed());
                    } else if (tag == "lastmod") {
                        sub.lastmod = QDateTime::fromString(
                            xml.readElementText().trimmed(), Qt::ISODate);
                    }
                }
            }

            if (sub.url.isValid()) {
                _subSitemaps.append(sub);
            }
        }
    }

    qCDebug(logFeedParser) << "SitemapParser: parsed" << _subSitemaps.size() << "sub-sitemaps";
}
