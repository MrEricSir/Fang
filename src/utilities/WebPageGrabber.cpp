#include "WebPageGrabber.h"

#include <QDebug>

// TidyLib
#include <tidy.h>
#include <buffio.h>

WebPageGrabber::WebPageGrabber(bool handleMetaRefresh, int timeoutMS, QObject *parent) :
    handleMetaRefresh(handleMetaRefresh), downloader(timeoutMS), FangObject(parent)
{
    connect(&downloader, &SimpleHTTPDownloader::error, this, &WebPageGrabber::onDownloadError);
    connect(&downloader, &SimpleHTTPDownloader::finished, this, &WebPageGrabber::onDownloadFinished);
}

WebPageGrabber::~WebPageGrabber()
{

}

void WebPageGrabber::load(const QUrl& url)
{
    redirectURL = "";
    downloader.load(url);
}

QDomDocument* WebPageGrabber::load(const QString& htmlString)
{
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

    // Shove into QtXML doc.
    document.setContent(result);

    if (handleMetaRefresh) {
        // Recursively walk the DOM to check for a meta refresh.
        traveseXML(document);
        if (redirectURL.size()) {
            QUrl url(redirectURL);
            if (url.isValid()) {
                load(url);

                return NULL;
            }
        }
    }

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
    load(array);
}

void WebPageGrabber::traveseXML(const QDomNode &node)
{
    QDomNode domNode = node;
    QDomElement domElement;

    // Loop sibblings at this level.
    while(!(domNode.isNull()))
    {
        QString nodeName = domNode.nodeName();
        //qDebug() << "Node: " << nodeName;
        //qDebug() << "Value: "  << domNode.nodeValue();

        // Stop conditions.
        if (nodeName == "body" || redirectURL.size()) {
            return;
        }

        if (domNode.isElement())
        {
            domElement = domNode.toElement();
            if(!(domElement.isNull()))
            {
                // Examples of what we're looking for:
                //     <meta http-equiv="refresh" content="0; url=http://example.com/">
                //     <meta http-equiv="refresh" content="0;URL='http://thetudors.example.com/'" />
                //     <meta http-equiv="refresh" content="0;URL=http://www.mrericsir.com/blog/" />
                if (nodeName == "meta" && domElement.attribute("http-equiv").toLower() == "refresh"
                        && domElement.hasAttribute("content")) {
                    const QString URL_TOKEN = "url=";
                    QString content = domElement.attribute("content");
                    int index = content.indexOf(URL_TOKEN, 0, Qt::CaseInsensitive);
                    if (index >= 0) {
                        // So there is a URL. Now we just have to defuckify it.
                        QString url = content.mid(index + URL_TOKEN.size()).trimmed();
                        QChar firstChar = url.at(0);
                        if (firstChar == '\"' || firstChar == '\"') {
                            url = url.mid(1);
                            if (url.endsWith('\'') || url.endsWith('\"')) {
                                url.left(1);
                            }
                            redirectURL = url;
                        } else {
                            redirectURL = url;
                        }
                    }
                }
            }
        }

        // Recurse children.
        QDomNode child = domNode.firstChild();
        while(!child.isNull()) {
            // Recurse!
            traveseXML(child);
            child = child.nextSibling();
        }

        // Continue outter loop.
        domNode = domNode.nextSibling();
    }
}


