#include "QMLNewsInteractor.h"
#include <QDebug>
#include <QList>
#include <QJsonDocument>
#include "../FangApp.h"
#include "NewsWebSocketServer.h"

QMLNewsInteractor::QMLNewsInteractor(QQuickItem *parent) :
    QQuickItem(parent),
    manager(nullptr),
    feedList(nullptr),
    windowHeight(0)
{
    
}

void QMLNewsInteractor::init(OperationManager *manager, ListModel *feedList)
{
    this->manager = manager;
    this->feedList = feedList;

    connect(FangApp::instance(), &FangApp::specialFeedCountChanged,
            this, &QMLNewsInteractor::specialFeedCountChanged);
    connect(FangApp::instance()->getNewsServer(), &NewsWebSocketServer::isLoadInProgressChanged,
            this, &QMLNewsInteractor::onIsLoadInProgressChanged);
}

qint32 QMLNewsInteractor::specialFeedCount()
{
    return FangApp::instance()->specialFeedCount();
}

bool QMLNewsInteractor::loadInProgress()
{
    return FangApp::instance()->getNewsServer()->isLoadInProgress();
}

void QMLNewsInteractor::setWindowHeight(int windowHeight)
{
    if (windowHeight == this->windowHeight) {
        return;
    }

    this->windowHeight = windowHeight;
    emit windowHeightChanged();
}

void QMLNewsInteractor::orderChanged()
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

void QMLNewsInteractor::refreshCurrentFeed()
{
    FangApp::instance()->refreshCurrentFeed();
}

void QMLNewsInteractor::refreshFeed(FeedItem* feed)
{
    FangApp::instance()->refreshFeed(feed);
}

void QMLNewsInteractor::markAllAsRead(FeedItem *feed)
{
    FangApp::instance()->markAllAsRead(feed);
}

void QMLNewsInteractor::markAllAsUnread(FeedItem *feed)
{
    FangApp::instance()->markAllAsUnread(feed);
}

void QMLNewsInteractor::jumpToBookmark()
{
    FangApp::instance()->jumpToBookmark();
}

void QMLNewsInteractor::jumpNext()
{
    FangApp::instance()->jumpNext();
}

void QMLNewsInteractor::jumpPrevious()
{
    FangApp::instance()->jumpPrevious();
}

void QMLNewsInteractor::showNews()
{
    FangApp::instance()->showNews();
}

void QMLNewsInteractor::showWelcome()
{
    FangApp::instance()->showWelcome();
}
