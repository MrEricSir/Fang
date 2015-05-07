#ifndef RAWFEEDIMAGESIZEREWRITER_H
#define RAWFEEDIMAGESIZEREWRITER_H

#include <QObject>
#include <QList>
#include <QDomElement>

#include "../parser/RawNews.h"
#include "../FangObject.h"
#include "ImageGrabber.h"

/**
 * @brief Takes in a "raw" HTML feed and processes it in the following ways:
 *          - Image sizes are baked into the HTML
 *          - Javascript is stripped
 *          - Those fucking "share this on social media!!11" buttons are removed
 *          - Tracking images?  Nope.
 */
class RawFeedRewriter : public FangObject
{
    Q_OBJECT
public:
    explicit RawFeedRewriter(QObject *parent = 0);
    
    
signals:
    /**
     * @brief We're done!  The feed you passed in as been modified.
     */
    void finished();
    
public slots:
    
    void rewrite(QList<RawNews*>* newsList);
    
    /**
     * @return 
     */
    inline QList<RawNews*>* getNewsList() { return newsList; }

protected:
    // Returns true if the text in a node is just whitespace.
    bool isHTMLEmpty(QString html);

    // Check whether we're looking at a share button URL.
    bool isShareURL(const QString& url);

    // Recursive DOM walker.
    void traverseXmlNode(const QDomNode& node, QSet<QUrl>& imageURLs);

    // Rewrites an HTML 4 u.
    QString rewriteHTML(const QString& input, QSet<QUrl>& imageURLs);

    // Same as above, but this takes care of the images (2nd step.)
    void rewriteImages(QString& docString);

    // Recursively walks the DOM and resizes the images.
    // Note: Can only be called after ImageGrabber completes!
    void traveseAndResizeImages(const QDomNode& node);

    // Post-process our news list.
    void postProcess();

    // Remove headers, footers, and other garbage.
    void postProcessDocString(QString& docString);

    // Resizes image dimensions.
    void imageResize(int width, int height, int* newWidth, int* newHeight);

protected slots:
    // We've grabbed our images.
    void onImageGrabberFinished();

    
private:
    // The current news list.
    QList<RawNews*>* newsList;

    // Image grabber.
    ImageGrabber imageGrabber;

    // Setup.
    QSet<QString> tagsToRemove;
    QSet<QString> classesToRemove;
    QList<QString> attributesToRemove;
    QList<QString> shareButtonURLs;
    
};

#endif // RAWFEEDIMAGESIZEREWRITER_H
