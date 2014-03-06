#include "WebInteractor.h"
#include <QDebug>
#include <QList>
#include <QDesktopServices>

WebInteractor::WebInteractor(QQuickItem *parent) :
    QQuickItem(parent),
    currentFeed(NULL),
    manager(NULL),
    isLoading(false),
    isSettingBookmark(false),
    isReady(false),
    feedList(NULL)
{
    
}

void WebInteractor::init(OperationManager *manager, ListModel *feedList)
{
    this->manager = manager;
    this->feedList = feedList;
}

void WebInteractor::loadNext()
{
    if (isLoading && !isReady)
        return;
    
    qDebug() << "Load next!";
    
    // Load MOAR
    doLoadNews(LoadNews::Append);
}

void WebInteractor::loadPrevious()
{
    if (isLoading && !isReady)
        return;
    
    qDebug() << "Load prev!";
    
    // Load the PREVIOUS
    doLoadNews(LoadNews::Prepend);
}

void WebInteractor::jumpToBookmark()
{
    if (currentFeed == NULL || currentFeed->getBookmark() == NULL)
        return; // Nothing to do!
    
    // Jump to the item following the bookmark, if possible.
    int index = currentFeed->getNewsList()->indexOf(currentFeed->getBookmark()) + 1;
    emit jumpTo(index < currentFeed->getNewsList()->size() ? currentFeed->getNewsList()->at(index)->id() : currentFeed->getBookmark()->id());
}

void WebInteractor::orderChanged()
{
    for (int i = 0; i < feedList->rowCount(); i++)
    {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != NULL);
        
        if (feed->getDbId() < 0)
            continue; // Skip all news.
        
        // Set the new ordinal.
        feed->setOrdinal(i);
        //qDebug() << "Feed " << feed->getTitle() << " #" << feed->getOrdinal();
    }
    
    // Write to DB.
    UpdateOrdinalsOperation* updateOp = new UpdateOrdinalsOperation(manager, feedList);
    manager->add(updateOp);
}

void WebInteractor::setBookmark(QString sId)
{
    qDebug() << "Setting bookmark to: " << sId;
    if (isSettingBookmark)
        return;
    
    qint64 id = sId.replace(NEWS_ITEM_ID_PREIX, "").toLongLong();
    //qDebug() << "Setting bookmark to... " << id;
    
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
    
    if (!currentFeed->canBookmark(bookmarkItem)) {
        isSettingBookmark = false;
        qDebug() << "Cannot set bookmark to: " << bookmarkItem->getTitle();
        
        return;
    }
    
    // I bookmark you!
    SetBookmarkOperation* bookmarkOp = new SetBookmarkOperation(manager, currentFeed, bookmarkItem);
    isSettingBookmark =  true;
    connect(bookmarkOp, SIGNAL(finished(Operation*)), this, SLOT(onSetBookmarkFinished(Operation*)));
    manager->add(bookmarkOp);
}

void WebInteractor::pageLoaded()
{
    isReady = true;
    
    setFeed(currentFeed);
}

void WebInteractor::openLink(QString link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void WebInteractor::refreshFeed(FeedItem *item)
{
    if (item == NULL)
        return;
    
    QList<FeedItem*> feedsToUpdate;
    
    // Special handling for all news.
    // TODO: Handle folders
    if (currentFeed->getDbId() < 0) {
        // Update ALL the feeds (except all news, obviously.)
        for (int i = 1; i < feedList->rowCount(); i++)
        {
            FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
            Q_ASSERT(feed != NULL);
            feedsToUpdate.append(feed);
        }
    } else {
        feedsToUpdate.append(item);
    }
    
    // Update 'em all!
    foreach(FeedItem* item, feedsToUpdate)
        manager->add(new UpdateFeedOperation(manager, item));
}

void WebInteractor::refreshFeed(const qint64 id)
{
    refreshFeed(feedForId(id));
}

void WebInteractor::refreshCurrentFeed()
{
    refreshFeed(currentFeed);
}

void WebInteractor::setFeed(FeedItem *feed)
{
    /**
      * VERY IMPORTANT!!!
      * 
      * Before changing any logic here, make sure it works with pageLoaded() above.
      */
    
    if (feed == NULL)
        return;
    
    // To save memory, clean up the old feed before continuing.
    if (currentFeed != NULL)
        currentFeed->clearNews();
    
    currentFeed = feed;
    
    if (!isReady)
        return;
    
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
    
    QString operationName = loader->getMode() == LoadNews::Initial ? "initial" : 
                            loader->getMode() == LoadNews::Append ? "append" : "prepend";
    
    emit addInProgress(true, operationName);
    
    // Stuff the new items into our feed.
    if (loader->getAppendList() != NULL)
        foreach(NewsItem* item, *loader->getAppendList())
            addNewsItem(true, item);
    
    if (loader->getPrependList() != NULL)
        foreach(NewsItem* item, *loader->getPrependList())
            addNewsItem(false, item);
    
    // If this is the initial load, draw and jump to the bookmark.
    if (loader->getMode() == LoadNews::Initial && currentFeed->getBookmark() != NULL) {
        jumpToBookmark();
        
        emit drawBookmark(currentFeed->getBookmark()->id());
    }
    
    emit addInProgress(false, operationName);
    
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

void WebInteractor::addNewsItem(bool append, NewsItem *item)
{
    //qDebug() << "Add news: " << item->id();
    emit add(append,
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

FeedItem *WebInteractor::feedForId(const qint64 id)
{
    for (int i = 0; i < feedList->rowCount(); i++)
    {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != NULL);
        
        if (feed->getDbId() == id)
            return feed;
    }
    
    return NULL;
}

