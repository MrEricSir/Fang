#ifndef RAWFEEDIMAGESIZEREWRITER_H
#define RAWFEEDIMAGESIZEREWRITER_H

#include <QObject>
#include <QList>

#include "WebImageSizeRewriter.h"
#include "../parser/RawNews.h"
#include "../FangObject.h"

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
    
private slots:
    void onImageSizerFinished();
    
    // Generates an element name.
    QString elementName(int i, bool description);
    
    /**
     * @brief Performs the sanitization on a single news element.
     */
    void takeOutTrash(QWebElement newsContainer);
    
    // Strips all subelements of element that match the CSS selector
    void removeAll(const QString& selector, QWebElement element);
    
    // Recursively deal with shyte.
    void visitElement(const QWebElement &parentElement);
    
private:
    WebImageSizeRewriter imageSizer;
    QList<RawNews*>* newsList;
    
};

#endif // RAWFEEDIMAGESIZEREWRITER_H
