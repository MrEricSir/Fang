#ifndef WEBPAGEGRABBER_H
#define WEBPAGEGRABBER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QTimer>
#include "../FangObject.h"
#include "../network/NetworkDownloadCore.h"

#define DEFAULT_HANDLE_META_REFRESH true
#define DEFAULT_TIMEOUT_MS 5000
#define MAX_REDIRECTS 10

/*!
    \brief Loads a web page at a given URL and signals with the XHTML document when done.

    Note that this class is not rentrant.
 */
class WebPageGrabber : public FangObject
{
    Q_OBJECT
public:
    /*!
        \brief WebPageGrabber creates an XHTML document from either a string or a URL.
        \param handleMetaRefresh If true, handles refreshes from within HTML documents rather than
                                 just HTTP communication.
        \param timeoutMS         Timeout after last download activity in milliseconds
        \param parent
        \param networkManager    Optional network manager for dependency injection (for testing)
     */
    explicit WebPageGrabber(bool handleMetaRefresh = DEFAULT_HANDLE_META_REFRESH,
                            int timeoutMS = DEFAULT_TIMEOUT_MS,
                            QObject *parent = nullptr,
                            QNetworkAccessManager* networkManager = nullptr);

    /*!
     * \brief Just like the above but with all the defaults specified *except* for parent.
     */
    explicit WebPageGrabber(QObject *parent);


signals:
    // If you requested a URL, ready() will be emitted when it's ready!
    // If document is null, an error happened. :(
    void ready(WebPageGrabber* grabber, QString* document);

public slots:
    // Fetches the webpage and emits ready() with the XHTML document.
    // Signals with null on an error.
    virtual void load(const QUrl &url);

    // Load the HTML string into a Tidy'd XHTML document and returns it (no signal is emmitted.)
    // Returns null on an error.
    QString* load(const QString& htmlString);

    // Returns the previously loaded document, or the empty string if there was an error.
    inline QString* getDocument() { return error ? nullptr : &document; }

    inline QUrl getOriginalURL() const { return originalUrl; }

    inline bool isDone() const { return done; }
    
private slots:
    // Internal load methods.
    void loadInternal(const QUrl &url);
    QString* loadInternal(const QString& htmlString, bool handleRefresh);

    // Uh oh, an error!
    void onDownloadError(const QUrl& url, const QString& errorString);

    // We got some HTTP content!
    void onDownloadFinished(const QUrl& url, const QByteArray& data);

    // Searches the XHTML'd document for a redirect URL.
    // Returns the redirect URL, or the empty string.
    QString searchForRedirect(const QString& document);

    // Handles the boilerplate involved with emitting the ready() signal.
    void emitReadySignal(QString* document);
    
private:
    void init();

    NetworkDownloadCore* core;
    QString document;
    bool handleMetaRefresh;
    int redirectAttempts;
    bool error;
    QUrl originalUrl;
    bool done;
};

#endif // WEBPAGEGRABBER_H
