#include "WebInteractor.h"
#include <QDebug>
#include <QList>
#include <QJsonDocument>
#include "../FangApp.h"
#include "NewsWebSocketServer.h"

WebInteractor::WebInteractor(QQuickItem *parent) :
    QQuickItem(parent),
    manager(NULL),
    feedList(NULL),
    windowHeight(0)
{
    
}

void WebInteractor::init(OperationManager *manager, ListModel *feedList)
{
    this->manager = manager;
    this->feedList = feedList;

    connect(FangApp::instance(), &FangApp::specialFeedCountChanged,
            this, &WebInteractor::specialFeedCountChanged);
    connect(FangApp::instance()->getNewsServer(), &NewsWebSocketServer::isLoadInProgressChanged,
            this, &WebInteractor::onIsLoadInProgressChanged);
}

qint32 WebInteractor::specialFeedCount()
{
    return FangApp::instance()->specialFeedCount();
}

bool WebInteractor::loadInProgress()
{
    return FangApp::instance()->getNewsServer()->isLoadInProgress();
}

void WebInteractor::setWindowHeight(int windowHeight)
{
    if (windowHeight == this->windowHeight) {
        return;
    }

    this->windowHeight = windowHeight;
    emit windowHeightChanged();
}

void WebInteractor::orderChanged()
{
    for (int i = 0; i < feedList->rowCount(); i++)
    {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        Q_ASSERT(feed != NULL);
        
        if (feed->isSpecialFeed())
            continue; // Skip special feeds.
        
        // Set the new ordinal.
        feed->setOrdinal(i);
        //qDebug() << "Feed " << feed->getTitle() << " #" << feed->getOrdinal();
    }
    
    // Write to DB.
    UpdateOrdinalsOperation* updateOp = new UpdateOrdinalsOperation(manager, feedList);
    manager->add(updateOp);
}

void WebInteractor::refreshCurrentFeed()
{
    FangApp::instance()->refreshCurrentFeed();
}
