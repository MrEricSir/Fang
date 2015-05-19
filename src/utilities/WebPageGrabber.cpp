#include "WebPageGrabber.h"
#include <QXmlStreamReader>

#include <QDebug>
//#include <iostream>

// TidyLib
#include <tidy.h>
#include <buffio.h>

WebPageGrabber::WebPageGrabber(bool handleMetaRefresh, int timeoutMS, QObject *parent) :
    handleMetaRefresh(handleMetaRefresh),
    redirectAttempts(0),
    downloader(timeoutMS),
    error(true),
    FangObject(parent)
{
    connect(&downloader, &SimpleHTTPDownloader::error, this, &WebPageGrabber::onDownloadError);
    connect(&downloader, &SimpleHTTPDownloader::finished, this, &WebPageGrabber::onDownloadFinished);
}

WebPageGrabber::~WebPageGrabber()
{

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
    downloader.load(url);
}

QString *WebPageGrabber::loadInternal(const QString& htmlString, bool handleRefresh)
{
    document = "";

    // Tidy up the string!
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};

    int rc = -1;
    Bool ok;

    TidyDoc tdoc = tidyCreate();                     // Initialize "document"

    // QString can convert to/from utf8
    tidySetInCharEncoding(tdoc, "utf8");
    tidySetOutCharEncoding(tdoc, "utf8");

    //printf( "Tidying:\t%s\n", input );

    ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
    if ( ok )
        ok = tidyOptSetInt( tdoc, TidyIndentContent, TidyNoState );  // Don't pretty print
    if ( ok )
      rc = tidySetErrorBuffer( tdoc, &errbuf );      // Capture diagnostics
    if ( rc >= 0 )
      rc = tidyParseString( tdoc, htmlString.toUtf8().constData());           // Parse the input
    if ( rc >= 0 )
      rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
    if ( rc >= 0 )
      rc = tidyRunDiagnostics( tdoc );               // Kvetch
    if ( rc > 1 )                                    // If error, force output.
      rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
    if ( rc >= 0 )
      rc = tidySaveBuffer( tdoc, &output );          // Pretty Print

    QString result = "";
    if (rc > 0 && output.bp) {
        result = QString::fromUtf8((char*)output.bp);
    } else {
        qDebug() << "WebPageGrabber error!";
        emit ready(NULL);
        return NULL;
    }

    // Free memory.
    tidyBufFree( &output );
    tidyBufFree( &errbuf );
    tidyRelease( tdoc );


    //std::cout << "Tidy: " << result.toStdString();

    // Remember </spock>
    document = result;

    // Check for an HTML meta refresh if requested.
    if (handleRefresh) {
        QString redirectURL = searchForRedirect(document);
        if (redirectAttempts > MAX_REDIRECTS) {
            qDebug() << "Error: Maximum HTML redirects";
            emit ready(NULL);

            return NULL;
        } else if (redirectURL.size()) {
            QUrl url(redirectURL);
            if (url.isValid()) {
                // Bump counter and call our internal load method that doesn't reset it.
                redirectAttempts++;
                loadInternal(url);

                return NULL;
            }
        }
    }

    error = false;
    emit ready(&document);
    return &document;
}

void WebPageGrabber::onDownloadError(QString err)
{
    Q_UNUSED(err);

    // Crap. :(
    emit ready(NULL);
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
    const QString S_HTTP_EQUIV = "http-equiv";
    const QString S_CONTENT = "content";
    const QString URL_TOKEN = "url=";

    QXmlStreamReader xml;
    xml.addData(document);

    while (!xml.atEnd()) {
        // Grab the next thingie.
        xml.readNext();

        if (xml.isStartElement()) {
            QString tagName = xml.name().toString().toLower();
            if (tagName == "body") {
                // We're done with the header, so bail.
                return "";
            }

            if (tagName == "meta") {
                // Possible redirect! Let's examine further, shall we?
                QXmlStreamAttributes attributes = xml.attributes();

                if (attributes.hasAttribute(S_HTTP_EQUIV) && attributes.hasAttribute(S_CONTENT) &&
                        attributes.value("", S_HTTP_EQUIV).toString().toLower() == "refresh") {

                    // For this method we're assuming that URL is always the last parameter in
                    // the content attribute.
                    QString content = attributes.value("", "content").toString();
                    int index = content.indexOf(URL_TOKEN, 0, Qt::CaseInsensitive);
                    if (index >= 0) {
                        // URLs are allowed to be in quotes, so we have to check for that.
                        QString url = content.mid(index + URL_TOKEN.size()).trimmed();
                        QChar firstChar = url.at(0);
                        if (firstChar == '\"' || firstChar == '\"') {
                            url = url.mid(1);
                            if (url.endsWith('\'') || url.endsWith('\"')) {
                                url.left(1);
                            }
                            return url;
                        } else {
                            return url;
                        }
                    }
                }
            }
        }
    }

    // We didn't find a redirect (and we never encountered a body tag either. Weird!)
    return "";
}


