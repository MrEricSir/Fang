#ifndef WEBPAGEGRABBER_H
#define WEBPAGEGRABBER_H

#include <QDomElement>
#include <QDomDocument>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QTimer>
#include "../FangObject.h"
#include "SimpleHTTPDownloader.h"

/**
 * @brief Loads a web page at a given URL and signals with the XHTML document when done.
 *
 * Note that this class is not rentrant -- one page at a time, fellas.
 */
class WebPageGrabber : public FangObject
{
    Q_OBJECT
public:
    // If handleMetaRefresh is true, we'll perform HTML-based redirects.

    /**
     * @brief WebPageGrabber creates an XML document from either a string or a URL.
     * @param handleMetaRefresh If true, handles refreshes from within HTML documents rather than
     *                          just HTTP communication.
     * @param timeoutMS         Timeout after last download activity in milliseconds
     * @param parent
     */
    explicit WebPageGrabber(bool handleMetaRefresh = true, int timeoutMS = 5000, QObject *parent = 0);
    virtual ~WebPageGrabber();
    
signals:
    // If you requested a URL, ready() will be emitted when it's ready!
    void ready(QDomDocument* page);
    
public slots:
    // Fetches the webpage and emits ready() with the DOM document.
    // Signals with null on an error.
    void load(const QUrl &url);

    // Load the HTML string into a DOM document and returns it (no signal is emmitted.)
    // Returns null on an error.
    QDomDocument* load(const QString& htmlString);
    
private slots:
    // Uh oh, an error!
    void onDownloadError(QString err);

    // We got some HTTP content!
    void onDownloadFinished(QByteArray array);

    // Recursively searches for a meta refresh in the XHTML DOM.
    // Sets redirectURL if one is found.
    void traveseXML(const QDomNode& node);
    
private:
    SimpleHTTPDownloader downloader;
    QDomDocument document;
    bool handleMetaRefresh;
    QString redirectURL;
};

#endif // WEBPAGEGRABBER_H
