#include "NewsFeedInteractor.h"
#include <QDebug>
#include <QList>
#include <QJsonDocument>

#include "../FangApp.h"
#include "NewsWebSocketServer.h"
#include "../operations/UpdateOrdinalsOperation.h"

NewsFeedInteractor::NewsFeedInteractor(QQuickItem *parent) :
    QQuickItem(parent)
{
    manager = FangApp::instance()->getOperationManager();
    feedList = FangApp::instance()->getFeedList();

    connect(FangApp::instance(), &FangApp::specialFeedCountChanged,
            this, &NewsFeedInteractor::specialFeedCountChanged);
    connect(FangApp::instance()->getNewsServer(), &NewsWebSocketServer::isLoadInProgressChanged,
            this, &NewsFeedInteractor::onIsLoadInProgressChanged);
    connect(FangApp::instance(), &FangApp::windowHeightChanged,
            this, &NewsFeedInteractor::windowHeightChanged);
}

qint32 NewsFeedInteractor::specialFeedCount()
{
    return FangApp::instance()->specialFeedCount();
}

bool NewsFeedInteractor::loadInProgress()
{
    return FangApp::instance()->getNewsServer()->isLoadInProgress();
}

int NewsFeedInteractor::getWindowHeight()
{
    return FangApp::instance()->getWindowHeight();
}

void NewsFeedInteractor::setWindowHeight(int windowHeight)
{
    FangApp::instance()->setWindowHeight(windowHeight);
}

void NewsFeedInteractor::removeFeed(FeedItem *feed)
{
    FangApp::instance()->removeFeed(feed);
}

int NewsFeedInteractor::insertFolder(int newIndex)
{
    // qDebug() << "FeedValidator::insertFolder at: " << newIndex;
    return FangApp::instance()->insertFolder(newIndex);
}

void NewsFeedInteractor::orderChanged()
{
    // TODO: Is this code still required?
//    for (int i = 0; i < feedList->rowCount(); i++)
//    {
//        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
//        Q_ASSERT(feed != nullptr);
        
//        if (feed->isSpecialFeed())
//            continue; // Skip special feeds.
        
//        // Set the new ordinal.
//        feed->setOrdinal(i);
//        //qDebug() << "Feed " << feed->getTitle() << " #" << feed->getOrdinal();
//    }
    
    // Update orinals based on the new list order.
    UpdateOrdinalsOperation* updateOp = new UpdateOrdinalsOperation(manager, feedList);
    manager->add(updateOp);
}

void NewsFeedInteractor::refreshCurrentFeed()
{
    FangApp::instance()->refreshCurrentFeed();
}

void NewsFeedInteractor::refreshFeed(FeedItem* feed)
{
    FangApp::instance()->refreshFeed(feed);
}

void NewsFeedInteractor::refreshAllFeeds()
{
    FangApp::instance()->refreshAllFeeds();
}

void NewsFeedInteractor::markAllAsRead(FeedItem *feed)
{
    FangApp::instance()->markAllAsRead(feed);
}

void NewsFeedInteractor::markAllAsUnread(FeedItem *feed)
{
    FangApp::instance()->markAllAsUnread(feed);
}

void NewsFeedInteractor::jumpToBookmark()
{
    FangApp::instance()->jumpToBookmark();
}

void NewsFeedInteractor::jumpNext()
{
    FangApp::instance()->jumpNext();
}

void NewsFeedInteractor::jumpPrevious()
{
    FangApp::instance()->jumpPrevious();
}

void NewsFeedInteractor::showNews()
{
    FangApp::instance()->showNews();
}

void NewsFeedInteractor::showWelcome()
{
    FangApp::instance()->showWelcome();
}
