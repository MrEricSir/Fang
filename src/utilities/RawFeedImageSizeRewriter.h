#ifndef RAWFEEDIMAGESIZEREWRITER_H
#define RAWFEEDIMAGESIZEREWRITER_H

#include <QObject>
#include <QList>

#include "WebImageSizeRewriter.h"
#include "../parser/RawNews.h"

class RawFeedImageSizeRewriter : public QObject
{
    Q_OBJECT
public:
    explicit RawFeedImageSizeRewriter(QObject *parent = 0);
    
    
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
    
private:
    WebImageSizeRewriter imageSizer;
    QList<RawNews*>* newsList;
    
};

#endif // RAWFEEDIMAGESIZEREWRITER_H
