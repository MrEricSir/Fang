#ifndef WEBIMAGESIZEREWRITER_H
#define WEBIMAGESIZEREWRITER_H

#include <QObject>
#include <QString>
#include <QWebPage>
#include <QSet>
#include <QUrl>
#include <QWebElement>

#include "WebPageGrabber.h"
#include "ImageGrabber.h"

#include "../FangObject.h"

/**
 * @brief Given an HTML string, this class fetches images that
 * are missing inline dimension attributes.
 *
 * Why?  Well you can't really skip down the page to a specific
 * point if the images are still loading.  That's a baa-a-a-a-a-ad
 * user experience.
 *
 * Oops, I just turned into a goat.  Gotta go.
 */
class WebImageSizeRewriter : public FangObject
{
    Q_OBJECT
public:
    
    /**
     * @param maxWidth  [optional] If you want to scale images to
     *                  a max width, gimmie it here.
     * @param parent    QObject's parent.
     */
    explicit WebImageSizeRewriter(int maxWidth = -1,
                                  QObject *parent = 0);
    
    
signals:
    
    /**
     * @brief We're done!  Call getHTML() or getDocument().
     */
    void finished();
    
public slots:
    
    /**
     * @param html The HTML you want to rewrite.
     */
    void rewrite(const QString& html);
    
    /**
     * @brief Result: only call this after finished() is emitted.
     * @return The modified or unmodified raw HTML.
     */
    QString getHTML() { return html; }
    
    /**
     * @brief Result: only call this after finished() is emitted.
     * @return The "document" that contains the processed HTML 
     *         -- OR -- a null document if the HTML was unchanged.
     */
    QWebElement getDocument();
    
private slots:
    // Page computed.
    void onWebGrabberReady(QWebPage* page);
    
    // Images grabbed.
    void onImageGrabberFinished();
    
    // Gets the images that need sizes.
    QWebElementCollection getImgElementsInNeed();
    
private:
    int maxWidth;
    WebPageGrabber webGrabber;
    QString html;
    QSet<QUrl> imageURLs;
    QWebElement document;
    ImageGrabber imageGrabber;
};

#endif // WEBIMAGESIZEREWRITER_H
