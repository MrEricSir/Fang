#include "WebInteractor.h"
#include <QDebug>
#include <QList>

WebInteractor::WebInteractor(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    currentFeed(NULL),
    manager(NULL),
    isLoading(false),
    isSettingBookmark(false)
{
    
}

void WebInteractor::init(OperationManager *manager)
{
    this->manager = manager;
}

void WebInteractor::loadNext()
{
    if (isLoading)
        return;
    
    qDebug() << "Load next!";
    
    // Load MOAR
    doLoadNews(LoadNews::Append);
}

void WebInteractor::loadPrevious()
{
    if (isLoading)
        return;
    
    qDebug() << "Load prev!";
    
    // Load the PREVIOUS
    doLoadNews(LoadNews::Prepend);
}

void WebInteractor::jumpToBookmark()
{
    if (currentFeed->getBookmark() == NULL)
        return; // Nothing to do!
    
    // Jump to the item following the bookmark, if possible.
    int index = currentFeed->getNewsList()->indexOf(currentFeed->getBookmark()) + 1;
    emit jumpTo(index < currentFeed->getNewsList()->size() ? currentFeed->getNewsList()->at(index)->id() : currentFeed->getBookmark()->id());
}

void WebInteractor::setBookmark(QString sId)
{
    if (isSettingBookmark)
        return;
    
    //qDebug() << "Look where we're jumping... " << id;
    qint64 id = sId.replace(NEWS_ITEM_ID_PREIX, "").toLongLong();
    qDebug() << "Setting bookmark to... " << id;
    
    // Locate the item!
    NewsItem* bookmarkItem = NULL;
    foreach(NewsItem* item, *currentFeed->getNewsList()) {
        if (item->getDbID() == id) {
            // We found it, yo!
            bookmarkItem = item;
            break;
        }
    }
    
    if (bookmarkItem == NULL) {
        isSettingBookmark = false;
        qDebug() << "Bookmark itm was not found for the current feed!";
        
        return; // We didn't find it.  Perhaps this is an old request? Either way, fuck it.
    }
    
    // I bookmark you!
    SetBookmarkOperation* bookmarkOp = new SetBookmarkOperation(manager, currentFeed, bookmarkItem);
    isSettingBookmark =  true;
    connect(bookmarkOp, SIGNAL(finished(Operation*)), this, SLOT(onSetBookmarkFinished(Operation*)));
    manager->add(bookmarkOp);
}

void WebInteractor::setFeed(FeedItem *feed)
{
    if (feed == NULL)
        return;
    
    // To save memory, clean up the old feed before continuing.
    if (currentFeed != NULL)
        currentFeed->clearNews();
    
    currentFeed = feed;
    
    // Clear the view.
    emit clear();
    
    // Okay, now LOAD the damn feed, y'all.
    doLoadNews(LoadNews::Initial);
}

void WebInteractor::onLoadNewsFinished(Operation* operation)
{
    LoadNews* loader = qobject_cast<LoadNews*>(operation);
    Q_ASSERT(loader != NULL); // If this ever happens, we're fucked.
    
    if (currentFeed != loader->getFeedItem()) {
        isLoading = false;
        return; // Throw this away, it's from a previous load attempt.
    }
    
    // Stuff the new items into our feed.
    QList<NewsItem*>* newsList = loader->getNewsList();
    if (newsList != NULL)
        foreach(NewsItem* item, *newsList)
            addNewsItem(loader->getMode(), item);
    
    // If this is the initial load, draw and jump to the bookmark.
    if (loader->getMode() == LoadNews::Initial && currentFeed->getBookmark() != NULL) {
        jumpToBookmark();
        
        emit drawBookmark(currentFeed->getBookmark()->id());
    }
    
    isLoading = false;
}

void WebInteractor::onSetBookmarkFinished(Operation *operation)
{
    SetBookmarkOperation* bookmarkOp = qobject_cast<SetBookmarkOperation*>(operation);
    Q_ASSERT(bookmarkOp != NULL);
    
    isSettingBookmark = false;
    
    if (bookmarkOp->getFeed() != currentFeed)
        return; // Too slow, no go, bro.
    
    currentFeed->setBookmark(bookmarkOp->getBookmarkItem());
    emit drawBookmark(currentFeed->getBookmark()->id());
}

QString WebInteractor::escapeCharacters(const QString& string)
{
    // Based on:
    // http://developer.nokia.com/Community/Wiki/Add_data_to_a_web_page_with_JavaScript,_WebKit,_and_Qt
    // (Key difference: single quotes instead of double)
    QString rValue = QString(string);
    /** Assign \\ to backSlash */
    QString backSlash = QString(QChar(0x5c)).append(QChar(0x5c));
    /** Replace \ with \\ */
    rValue = rValue.replace('\\', backSlash);
    /** Assing \' to quote. */
    QString quote = QString(QChar(0x5c)).append(QChar(0x27));
    /** Replace ' with \' */
    rValue = rValue.replace('\'', quote);
    
    // Replace slash r with nothing
    rValue = rValue.replace('\r', "");
    
    // Replace slash n with space
    rValue = rValue.replace('\n', " ");
    
    return rValue;
}

void WebInteractor::addNewsItem(LoadNews::LoadMode mode, NewsItem *item)
{
    //qDebug() << "Add news: " << item->id();
    emit add(mode != LoadNews::Prepend,
             item->id(),
             escapeCharacters(item->getTitle()),
             escapeCharacters(item->getURL().toString()),
             escapeCharacters(item->getFeed()->getTitle()),
             escapeCharacters(item->getTimestamp().toString()),
             escapeCharacters( item->getContent() != "" ? item->getContent() : item->getSummary()) );
}

void WebInteractor::doLoadNews(LoadNews::LoadMode mode)
{
    Q_ASSERT(currentFeed != NULL);
    
    LoadNews* loader = (currentFeed->getDbId() < 0) ? new LoadAllNewsOperation(manager, currentFeed, mode) :
                new LoadNews(manager, currentFeed, mode);
    isLoading =  true;
    connect(loader, SIGNAL(finished(Operation*)), this, SLOT(onLoadNewsFinished(Operation*)));
    manager->add(loader);
}

