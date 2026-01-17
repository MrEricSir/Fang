#include "WebPageGrabber.h"
#include <QXmlStreamReader>
#include <memory>

// TidyLib
#include <tidy.h>
#include <buffio.h>

#include "FangLogging.h"

namespace {
    // RAII wrapper for TidyDoc to ensure cleanup
    struct TidyDocDeleter {
        void operator()(TidyDoc doc) const {
            if (doc) {
                tidyRelease(doc);
            }
        }
    };
    using TidyDocPtr = std::unique_ptr<std::remove_pointer<TidyDoc>::type, TidyDocDeleter>;
}

WebPageGrabber::WebPageGrabber(bool handleMetaRefresh, int timeoutMS, QObject *parent, QNetworkAccessManager* networkManager) :
    FangObject(parent),
    downloader(timeoutMS, this, networkManager),
    handleMetaRefresh(handleMetaRefresh),
    redirectAttempts(0),
    error(true),
    done(false)

{
    init();
}

WebPageGrabber::WebPageGrabber(QObject *parent) :
    FangObject(parent),
    downloader(DEFAULT_HANDLE_META_REFRESH, this, nullptr),
    handleMetaRefresh(DEFAULT_TIMEOUT_MS),
    redirectAttempts(0),
    error(true),
    done(false)
{
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
    downloader.load(url);
}

QString *WebPageGrabber::loadInternal(const QString& htmlString, bool handleRefresh)
{
    document.clear();

    // Tidy up the string!
    TidyBuffer output;
    TidyBuffer errbuf;
    tidyBufInit(&output);
    tidyBufInit(&errbuf);

    TidyDocPtr tdoc(tidyCreate());
    if (!tdoc) {
        emitReadySignal(nullptr);
        return nullptr;
    }

    // QString can convert to/from utf8
    tidySetInCharEncoding(tdoc.get(), "utf8");
    tidySetOutCharEncoding(tdoc.get(), "utf8");

    // Configure and process the HTML
    if (!tidyOptSetBool(tdoc.get(), TidyXhtmlOut, yes)) {
        tidyBufFree(&output);
        tidyBufFree(&errbuf);
        emitReadySignal(nullptr);
        return nullptr;
    }

    if (!tidyOptSetInt(tdoc.get(), TidyIndentContent, TidyNoState)) {
        tidyBufFree(&output);
        tidyBufFree(&errbuf);
        emitReadySignal(nullptr);
        return nullptr;
    }

    int rc = tidySetErrorBuffer(tdoc.get(), &errbuf);
    if (rc >= 0) {
        rc = tidyParseString(tdoc.get(), htmlString.toUtf8().constData());
    }
    if (rc >= 0) {
        rc = tidyCleanAndRepair(tdoc.get());
    }
    if (rc >= 0) {
        rc = tidyRunDiagnostics(tdoc.get());
    }
    if (rc > 1) {
        // If error, force output
        rc = tidyOptSetBool(tdoc.get(), TidyForceOutput, yes) ? rc : -1;
    }
    if (rc >= 0) {
        rc = tidySaveBuffer(tdoc.get(), &output);
    }

    QString result;
    qCDebug(logWebPage) << "TidyLib rc:" << rc << "output.bp:" << (output.bp != nullptr);

    if (rc >= 0 && output.bp) {
        result = QString::fromUtf8(reinterpret_cast<const char*>(output.bp));
    } else {
        qCDebug(logWebPage) << "WebPageGrabber error!";
        tidyBufFree(&output);
        tidyBufFree(&errbuf);
        emitReadySignal(nullptr);
        return nullptr;
    }

    // Free memory (tdoc is automatically freed by unique_ptr)
    tidyBufFree(&output);
    tidyBufFree(&errbuf);

    document = result;

    // Check for an HTML meta refresh if requested.
    if (handleRefresh) {
        QString redirectURL = searchForRedirect(document);
        if (redirectAttempts > MAX_REDIRECTS) {
            qCDebug(logWebPage) << "Error: Maximum HTML redirects";
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

void WebPageGrabber::onDownloadError(QString err)
{
    Q_UNUSED(err);

    // Crap. :(
    emitReadySignal(nullptr);
}

void WebPageGrabber::onDownloadFinished(QByteArray array)
{
    loadInternal(array, handleMetaRefresh);
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
    connect(&downloader, &SimpleHTTPDownloader::error, this, &WebPageGrabber::onDownloadError);
    connect(&downloader, &SimpleHTTPDownloader::finished, this, &WebPageGrabber::onDownloadFinished);
}


