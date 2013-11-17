#ifndef WEBINTERACTOR_H
#define WEBINTERACTOR_H

#include <QDeclarativeItem>
#include <QString>

#include "FeedItem.h"
#include "NewsItem.h"
#include "../operations/OperationManager.h"
#include "../operations/Operation.h"
#include "../operations/LoadNews.h"

/**
 * @brief Passes news between the JavaScript and C++ layers, yo.
 */
class WebInteractor : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(WebInteractor)
    
public:
    explicit WebInteractor(QDeclarativeItem *parent = 0);
    virtual ~WebInteractor() {}
    
    void init(OperationManager* manager);
    
signals:
    
    /**
     * @brief Add a little something to the web page.
     * 
     * @param append      True for appending, false for prepending.
     * @param title       Title of the news item
     * @param url         URL of the story
     * @param feedTitle   Feed's title
     * @param timestamp   String timestamp
     * @param content     HTML content
     */
    void add(bool append, QString title, QString url, QString feedTitle, QString timestamp, QString content);
    
public slots:
    
    // Call this when the feed changes, g-dawg.
    void setFeed(FeedItem* feed);
    
    // This says, like, ok we're ready for the next batch of news.
    Q_INVOKABLE void loadNext();
    
    // Beep beep beep! http://www.youtube.com/watch?v=B_H7WZGsIjM
    Q_INVOKABLE void loadPrevious();
    
private slots:
    
    // Called when a load has completed.
    void onLoadNewsFinished(Operation* operation);
    
    QString escapeCharacters(const QString& string);
    
    void addNewsItem(bool append, NewsItem* item);
    
private:
    // The currently selected news feed.
    FeedItem* currentFeed;
    
    // Op man!
    OperationManager* manager;
    
    // Reentrancy guard.
    bool isLoading;
    
};

#endif // WEBINTERACTOR_H
