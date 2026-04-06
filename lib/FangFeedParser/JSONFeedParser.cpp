#include "JSONFeedParser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

#include "RawFeed.h"
#include "RawNews.h"

std::unique_ptr<RawFeed> JSONFeedParser::parse(const QByteArray& data)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        return nullptr;
    }

    QJsonObject root = doc.object();

    // Validate version field.
    QString version = root.value("version").toString();
    if (!version.startsWith("https://jsonfeed.org/version/")) {
        return nullptr;
    }

    auto feed = std::make_unique<RawFeed>();
    feed->feedType = RawFeed::JSONFeed;

    feed->title = root.value("title").toString("");
    feed->subtitle = root.value("description").toString("");

    QString homePageUrl = root.value("home_page_url").toString();
    if (!homePageUrl.isEmpty()) {
        feed->siteURL = QUrl(homePageUrl);
    }

    QString feedUrl = root.value("feed_url").toString();
    if (!feedUrl.isEmpty()) {
        feed->url = QUrl(feedUrl);
    }

    // Prefer icon over favicon for the feed image.
    QString icon = root.value("icon").toString();
    if (icon.isEmpty()) {
        icon = root.value("favicon").toString();
    }
    if (!icon.isEmpty()) {
        feed->imageURL = QUrl(icon);
    }

    // Parse items.
    QJsonArray items = root.value("items").toArray();
    for (const QJsonValue& itemVal : items) {
        if (!itemVal.isObject()) {
            continue;
        }

        QJsonObject itemObj = itemVal.toObject();

        // Skip items without an id.
        QString id = itemObj.value("id").toString();
        if (id.isEmpty()) {
            continue;
        }

        auto news = std::make_shared<RawNews>();
        news->guid = id;

        QString itemUrl = itemObj.value("url").toString();
        if (!itemUrl.isEmpty()) {
            news->url = QUrl(itemUrl);
        }

        news->title = itemObj.value("title").toString();

        // content_html takes priority over content_text for the content field.
        QString contentHtml = itemObj.value("content_html").toString("");
        QString contentText = itemObj.value("content_text").toString("");
        if (!contentHtml.isEmpty()) {
            news->content = contentHtml;
        } else if (!contentText.isEmpty()) {
            news->content = contentText;
        }

        // summary => description; fall back to content_text if no summary.
        QString summary = itemObj.value("summary").toString("");
        if (!summary.isEmpty()) {
            news->description = summary;
        } else if (!contentText.isEmpty()) {
            news->description = contentText;
        }

        // Timestamp.
        QString datePublished = itemObj.value("date_published").toString();
        if (!datePublished.isEmpty()) {
            news->timestamp = QDateTime::fromString(datePublished, Qt::ISODate);
            if (news->timestamp.isValid()) {
                news->timestamp = news->timestamp.toUTC();
            }
        }

        // Image.
        QString image = itemObj.value("image").toString();
        if (!image.isEmpty()) {
            news->mediaImageURL = image;
        }

        // Author. Try v1.1 authors array first, then v1.0 author object.
        QJsonArray authors = itemObj.value("authors").toArray();
        if (!authors.isEmpty()) {
            QJsonObject firstAuthor = authors.first().toObject();
            news->author = firstAuthor.value("name").toString("");
        } else {
            QJsonObject authorObj = itemObj.value("author").toObject();
            if (!authorObj.isEmpty()) {
                news->author = authorObj.value("name").toString("");
            }
        }

        feed->items.append(news);
    }

    return feed;
}
