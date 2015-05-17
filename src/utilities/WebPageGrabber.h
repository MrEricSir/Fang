#ifndef WEBPAGEGRABBER_H
#define WEBPAGEGRABBER_H

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
    // If document is null, an error happened. :(
    void ready(QString* document);
    
public slots:
    // Fetches the webpage and emits ready() with the XHTML document.
    // Signals with null on an error.
    void load(const QUrl &url);

    // Load the HTML string into a Tidy'd XHTML document and returns it (no signal is emmitted.)
    // Returns null on an error.
    QString* load(const QString& htmlString);
    
private slots:
    // Uh oh, an error!
    void onDownloadError(QString err);

    // We got some HTTP content!
    void onDownloadFinished(QByteArray array);

    // Searches the XHTML'd document for a redirect URL.
    // Returns the redirect URL, or the empty string.
    QString searchForRedirect(const QString& document);
    
private:
    SimpleHTTPDownloader downloader;
    QString document;
    bool handleMetaRefresh;
};

#endif // WEBPAGEGRABBER_H
