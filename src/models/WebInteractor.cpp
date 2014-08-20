#include "WebInteractor.h"
#include <QDebug>
#include <QList>
#include <QDesktopServices>
#include <QJsonDocument>
#include "../FangApp.h"

WebInteractor::WebInteractor(QQuickItem *parent) :
    QQuickItem(parent),
    currentFeed(NULL),
    manager(NULL),
    isLoading(false),
    isSettingBookmark(false),
    isReady(false),
    feedList(NULL),
    fangSettings(NULL)
{
    
}

void WebInteractor::init(OperationManager *manager, ListModel *feedList, FangSettings *fangSettings)
{
    this->manager = manager;
    this->feedList = feedList;
    this->fangSettings = fangSettings;
    
    connect(feedList, SIGNAL(removed(ListItem*)), this, SLOT(onFeedRemoved(ListItem*)));
    connect(fangSettings, SIGNAL(styleChanged(QString)), this, SLOT(onStyleChanged(QString)));
    connect(fangSettings, SIGNAL(fontSizeChanged(QString)), this, SLOT(onFontSizeChanged(QString)));
}

void WebInteractor::loadNext()
{
    if (isLoading && !isReady)
        return;
    
    //qDebug() << "Load next!";
    
    // Load MOAR
    doLoadNews(LoadNews::Append);
}

void WebInteractor::loadPrevious()
{
    if (isLoading && !isReady)
        return;
    
    //qDebug() << "Load prev!";
    
    // Load the PREVIOUS
    doLoadNews(LoadNews::Prepend);
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

void WebInteractor::setBookmark(QString sId, bool allowBackward)
{
    qDebug() << "Set bookmarK; " << sId << ", " << allowBackward;
    
    if (isSettingBookmark || NULL == currentFeed) {
        return;
    }
    
    // qDebug() << "Setting bookmark to: " << sId;
    
    qint64 id = sId.replace(NEWS_ITEM_ID_PREIX, "").toLongLong();
    
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
    
    if (!currentFeed->canBookmark(bookmarkItem, allowBackward)) {
        isSettingBookmark = false;
        qDebug() << "Cannot set bookmark to: " << bookmarkItem->getTitle();
        
        return;
    }
    
    // I bookmark you!
    SetBookmarkOperation* bookmarkOp = new SetBookmarkOperation(manager, currentFeed, bookmarkItem, allowBackward);
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

void WebInteractor::refreshCurrentFeed()
{
    FangApp::instance()->refreshCurrentFeed();
}

void WebInteractor::removeNews(bool fromTop, int numberToRemove)
{
    if (!currentFeed)
        return;
    
    // Remove from list, free memory.
    for (int i = 0; i < numberToRemove; i++) {
        if (fromTop) {
            currentFeed->getNewsList()->takeFirst()->deleteLater();
        } else {
            currentFeed->getNewsList()->takeLast()->deleteLater();
        }
    }
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
    if (currentFeed != NULL) {
        currentFeed->clearNews();
    }
    
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
    if (NULL == currentFeed) {
        return;
    }
    
    LoadNews* loader = qobject_cast<LoadNews*>(operation);
    Q_ASSERT(loader != NULL); // If this ever happens, we're fucked.
    
    if (currentFeed != loader->getFeedItem()) {
        isLoading = false;
        
        return; // Throw this away, it's from a previous load attempt.
    }
    
    if (!loader->getAppendList() && !loader->getPrependList()) {
        isLoading = false;
        
        if (loader->getMode() == LoadNews::Initial) {
            emit nothingToAdd();
            emit drawBookmarkAndJumpTo("");
        }
        
        return; // Nothing to do.
    }
    
    QString operationName = loader->getMode() == LoadNews::Initial ? "initial" : 
                            loader->getMode() == LoadNews::Append ? "append" : "prepend";
    
    emit addInProgress(true, operationName);
    
    // Stuff the new items into our feed.
    if (loader->getAppendList() != NULL) {
        QVariantList appendList;
        foreach(NewsItem* item, *loader->getAppendList()) {
            addNewsItem(item, &appendList);
        }
        
        // Emmit append signal.
        emit add(true, escapeCharacters(QJsonDocument::fromVariant(appendList).toJson()));
    }
    
    if (loader->getPrependList() != NULL) {
        QVariantList prependList;
        foreach(NewsItem* item, *loader->getPrependList()) {
            addNewsItem(item, &prependList);
        }
        
        // Emmit prepend signal.
        emit add(false, escapeCharacters(QJsonDocument::fromVariant(prependList).toJson()));
    }
    
    // If this is the initial load, draw and jump to the bookmark.
    QString idOfBookmark = "";
    if (loader->getMode() == LoadNews::Initial && currentFeed->getBookmark() != NULL) {
        idOfBookmark = currentFeed->getBookmark()->id();
    }
    emit drawBookmarkAndJumpTo(idOfBookmark);
    
    emit addInProgress(false, operationName);
    
    isLoading = false;
}

void WebInteractor::onSetBookmarkFinished(Operation *operation)
{
    if (NULL == currentFeed) {
        return;
    }
    
    SetBookmarkOperation* bookmarkOp = qobject_cast<SetBookmarkOperation*>(operation);
    Q_ASSERT(bookmarkOp != NULL);
    
    isSettingBookmark = false;
    
    if (bookmarkOp->getBookmarkItem() == NULL) {
        // NOPE NOPE NOPE
        return;
    }
    
    if (bookmarkOp->getFeed() != currentFeed) {
        // Too slow, no go, bro.
        return;
    }
    
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
    
    // Replace slash n with ASCII code 0x18, "cancel"
    rValue = rValue.replace('\n', QChar(0x18));
    
    return rValue;
}

void WebInteractor::addNewsItem(NewsItem *item, QVariantList* newsList)
{
    //qDebug() << "Add news: " << item->id();
    
    // Make sure we get the real feed title for All News.
    QString feedTitle = !item->getFeed()->isAllNews() ? 
                            item->getFeed()->getTitle() :
                            FangApp::instance()->getFeedForID(item->getFeedId())->getTitle();
    
    QVariantMap itemMap;
    itemMap["id"] = item->id();
    itemMap["title"] = item->getTitle();
    itemMap["url"] = item->getURL().toString();
    itemMap["feedTitle"] = feedTitle;
    itemMap["timestamp"] = item->getTimestamp().toMSecsSinceEpoch();
    itemMap["content"] = item->getContent() != "" ? item->getContent() : item->getSummary();
    
    // Add to the list.
    *newsList << itemMap;
}

void WebInteractor::doLoadNews(LoadNews::LoadMode mode)
{
    if (currentFeed == NULL) {
        return;
    }
    
    LoadNews* loader = (currentFeed->getDbId() < 0) ? 
                           new LoadAllNewsOperation(manager, currentFeed, mode) :
                           new LoadNews(manager, currentFeed, mode);
    isLoading =  true;
    connect(loader, SIGNAL(finished(Operation*)), this, SLOT(onLoadNewsFinished(Operation*)));
    manager->add(loader);
}

void WebInteractor::onFeedRemoved(ListItem *listItem)
{
    if (listItem == currentFeed) {
        // Feed is being removed, don't try to use this pointer.  I mean, duh.
        currentFeed = NULL;
    }
}

void WebInteractor::onStyleChanged(QString style)
{
    Q_UNUSED(style);
    emit styleChanged();
}

void WebInteractor::onFontSizeChanged(QString font)
{
    Q_UNUSED(font);
    emit fontSizeChanged();
}

