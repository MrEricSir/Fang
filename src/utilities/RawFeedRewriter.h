#ifndef RAWFEEDIMAGESIZEREWRITER_H
#define RAWFEEDIMAGESIZEREWRITER_H

#include <QObject>
#include <QList>

#include "../parser/RawNews.h"
#include "../FangObject.h"
#include "ImageGrabber.h"
#include "WebPageGrabber.h"

// Represents a DOM node.
class DOMNode {
public:
    DOMNode(QString tagName, int intID) :
        tagName(tagName),
        intID(intID),
        nonEmptyTextCount(0),
        numChildren(0)
    {}

    // Stack requires a default c'tor
    DOMNode() :
        intID(0),
        nonEmptyTextCount(0),
        numChildren(0)
    {}

    QString tagName;
    int intID;
    int nonEmptyTextCount;
    int numChildren;
};

/**
 * @brief Takes a "raw" HTML feed and processes it in the following ways:
 *          - Tidy'd into XHTML fragments
 *          - Image sizes are baked in
 *          - Javascript is stripped
 *          - Common social media buttons removed
 *          - Tracking pixels?  Nope.
 */
class RawFeedRewriter : public FangObject
{
    Q_OBJECT
public:
    explicit RawFeedRewriter(QObject *parent = nullptr);
    
    
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

    // Turns an int into an ID.
    QString intToID(int id);

    // First pass rewriter.
    QString rewriteFirstPass(const QString& document, QSet<QUrl>& imageURLs);

    // Calls rewriteSecondPass() on all news HTML.
    void rewriteAllSecondPass();

    // Same as above, but this takes care of the images (if needed) and deletes empty elements.
    QString rewriteSecondPass(QString& docString);

    // Post-process our news list.
    void postProcess();

    // Remove headers, footers, and other garbage.
    void postProcessDocString(QString& docString);

    // Resizes image dimensions.
    void imageResize(int width, int height, int* newWidth, int* newHeight);

    // Removes excessive newlines.
    void removeNewlinesBothSides(QString& docString);

    // Some news is text instead of HTML (Hearst's papers, for example.)
    QString rewriteTextOnlyNews(QString input);

protected slots:
    // We've grabbed our images.
    void onImageGrabberFinished();

    
private:
    // The current news list.
    QList<RawNews*>* newsList;

    // Web page grabber.
    WebPageGrabber webPageGrabber;

    // Image grabber!  GRAB GRAB GRAB
    ImageGrabber imageGrabber;

    // Setup.
    QSet<QString> tagsToRemove;
    QSet<QString> classesToRemove;
    QList<QString> shareButtonURLs;
    QSet<QString> containerTags;
    
    // Element IDs.
    QSet<QString> idsToDelete;
    int intID;
};

#endif // RAWFEEDIMAGESIZEREWRITER_H
