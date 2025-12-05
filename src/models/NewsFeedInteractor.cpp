#include "NewsFeedInteractor.h"
#include <QDebug>
#include <QList>
#include <QJsonDocument>

#include "../FangApp.h"
#include "../operations/UpdateOrdinalsOperation.h"

NewsFeedInteractor::NewsFeedInteractor(QQuickItem *parent) :
    QQuickItem(parent)
{
    manager = FangApp::instance()->getOperationManager();
    feedList = FangApp::instance()->getFeedList();

    connect(FangApp::instance(), &FangApp::specialFeedCountChanged,
            this, &NewsFeedInteractor::specialFeedCountChanged);
}

qint32 NewsFeedInteractor::specialFeedCount()
{
    return FangApp::instance()->specialFeedCount();
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
    // Update orinals based on the new list order.
    UpdateOrdinalsOperation updateOp(manager, feedList);
    manager->runSynchronously(&updateOp);
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
