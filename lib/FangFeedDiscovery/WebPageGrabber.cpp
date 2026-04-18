#include "WebPageGrabber.h"
#include "QWebDownload.h"
#include "QTidyLibClassic.h"
#include <QXmlStreamReader>

#include "FeedDiscoveryLogging.h"

WebPageGrabber::WebPageGrabber(bool handleMetaRefresh, int timeoutMS, QObject *parent, QNetworkAccessManager* networkManager) :
    QObject(parent),
    core(nullptr),
    handleMetaRefresh(handleMetaRefresh),
    redirectAttempts(0),
    error(true),
    done(false)
{
    WebDownloadConfig config;
    config.timeoutMs = timeoutMS;
    config.maxRedirects = 10;
    config.useInactivityTimeout = true;
    core = new QWebDownload(config, this, networkManager);
    init();
}

WebPageGrabber::WebPageGrabber(QObject *parent) :
    QObject(parent),
    core(nullptr),
    handleMetaRefresh(defaultHandleMetaRefresh),
    redirectAttempts(0),
    error(true),
    done(false)
{
    WebDownloadConfig config;
    config.timeoutMs = defaultTimeoutMs;
    config.maxRedirects = 10;
    config.useInactivityTimeout = true;
    core = new QWebDownload(config, this, nullptr);
    init();
}


void WebPageGrabber::load(const QUrl& url)
{
    // Reset!
    redirectAttempts = 0;
    error = true;

    // Now GO!
    loadInternal(url);
}

QString *WebPageGrabber::load(const QString& htmlString)
{
    // Reset!
    error = true;

    return loadInternal(htmlString, false);
}

void WebPageGrabber::loadInternal(const QUrl& url)
{
    originalUrl = url;
    core->get(url);
}

QString *WebPageGrabber::loadInternal(const QString& htmlString, bool handleRefresh)
{
    document.clear();

    QString result = QTidyLibClassic::toXhtml(htmlString);
    if (result.isEmpty()) {
        qCDebug(logFeedDiscovery) << "WebPageGrabber error!";
        emitReadySignal(nullptr);
        return nullptr;
    }

    document = result;

    // Check for an HTML meta refresh if requested.
    if (handleRefresh) {
        QString redirectURL = searchForRedirect(document);
        if (redirectAttempts > maxRedirects) {
            qCDebug(logFeedDiscovery) << "Error: Maximum HTML redirects";
            emitReadySignal(nullptr);
            return nullptr;
        } else if (!redirectURL.isEmpty()) {
            QUrl url(redirectURL);
            if (url.isValid()) {
                // Bump counter and call our internal load method that doesn't reset it.
                redirectAttempts++;
                loadInternal(url);
                return nullptr;
            }
        }
    }

    // Woo-hoo! We have a document!
    error = false;
    emitReadySignal(&document);
    return &document;
}

void WebPageGrabber::onDownloadError(const QUrl& url, const QString& errorString)
{
    Q_UNUSED(url);
    Q_UNUSED(errorString);

    // Crap. :(
    emitReadySignal(nullptr);
}

void WebPageGrabber::onDownloadFinished(const QUrl& url, const QByteArray& data)
{
    Q_UNUSED(url);
    loadInternal(data, handleMetaRefresh);
}

QString WebPageGrabber::searchForRedirect(const QString& document)
{
    // Examples of what we're looking for:
    //     <meta http-equiv="refresh" content="0; url=http://example.com/">
    //     <meta http-equiv="refresh" content="0;URL='http://thetudors.example.com/'" />
    //     <meta http-equiv="refresh" content="0;URL=http://www.mrericsir.com/blog/" />

    QXmlStreamReader xml;
    xml.addData(document);

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            QString tagName = xml.name().toString().toLower();
            if (tagName == "body") {
                return QString();
            }

            if (tagName == "meta") {
                QXmlStreamAttributes attributes = xml.attributes();

                if (attributes.hasAttribute("http-equiv") && attributes.hasAttribute("content") &&
                        attributes.value("", "http-equiv").toString().toLower() == "refresh") {

                    // For this method we're assuming that URL is always the last parameter in
                    // the content attribute.
                    QString content = attributes.value("", "content").toString();
                    int index = content.indexOf("url=", 0, Qt::CaseInsensitive);
                    if (index >= 0) {
                        // URLs are allowed to be in quotes, so we have to check for that.
                        QString url = content.mid(index + 4).trimmed();  // "url=" is 4 chars
                        if (!url.isEmpty()) {
                            QChar firstChar = url.at(0);
                            if (firstChar == '\'' || firstChar == '\"') {
                                url = url.mid(1);
                                if (url.endsWith('\'') || url.endsWith('\"')) {
                                    url.chop(1);
                                }
                            }
                            return url;
                        }
                    }
                }
            }
        }
    }

    return QString();
}

void WebPageGrabber::emitReadySignal(QString* document)
{
    // Remember that we're done.
    done = true;

    // Now emit the signal.
    emit ready(this, document);
}

void WebPageGrabber::init()
{
    connect(core, &QWebDownload::error, this, &WebPageGrabber::onDownloadError);
    connect(core, &QWebDownload::finished, this, &WebPageGrabber::onDownloadFinished);
}

QString WebPageGrabber::htmlToXhtml(const QByteArray& html)
{
    return QTidyLibClassic::toXhtml(html);
}


