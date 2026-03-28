#include "PageMetadataExtractor.h"

#include <QXmlStreamReader>

PageMetadata PageMetadataExtractor::extract(const QString& xhtml)
{
    PageMetadata meta;

    QString ogTitle;
    QString ogDescription;
    QUrl ogImage;
    QString ogAuthor;
    QString htmlTitle;
    QString metaDescription;
    QString metaAuthor;
    QString htmlLang;

    QXmlStreamReader xml(xhtml);

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            QString tag = xml.name().toString().toLower();

            // Extract lang from <html lang="...">.
            if (tag == "html") {
                QXmlStreamAttributes attrs = xml.attributes();
                if (attrs.hasAttribute("lang")) {
                    htmlLang = attrs.value("lang").toString().toLower();
                }
            }

            // Stop at <body> -- we only care about <head>.
            if (tag == "body") {
                break;
            }

            if (tag == "title") {
                htmlTitle = xml.readElementText().trimmed();
            } else if (tag == "meta") {
                QXmlStreamAttributes attrs = xml.attributes();

                // OpenGraph tags: <meta property="og:..." content="...">
                if (attrs.hasAttribute("property") && attrs.hasAttribute("content")) {
                    QString property = attrs.value("property").toString().toLower();
                    QString content = attrs.value("content").toString();

                    if (property == "og:title") {
                        ogTitle = content;
                    } else if (property == "og:description") {
                        ogDescription = content;
                    } else if (property == "og:image") {
                        ogImage = QUrl(content);
                    } else if (property == "article:author") {
                        ogAuthor = content;
                    }
                }

                // Standard meta tags: <meta name="..." content="...">
                if (attrs.hasAttribute("name") && attrs.hasAttribute("content")) {
                    QString name = attrs.value("name").toString().toLower();
                    QString content = attrs.value("content").toString();

                    if (name == "description") {
                        metaDescription = content;
                    } else if (name == "author") {
                        metaAuthor = content;
                    }
                }
            }
        }
    }

    // Apply priority: OG > standard HTML.
    meta.title = !ogTitle.isEmpty() ? ogTitle : htmlTitle;
    meta.description = !ogDescription.isEmpty() ? ogDescription : metaDescription;
    meta.imageUrl = ogImage;
    meta.author = !ogAuthor.isEmpty() ? ogAuthor : metaAuthor;
    meta.lang = htmlLang;

    return meta;
}
