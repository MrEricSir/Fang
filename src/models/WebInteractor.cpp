#include "WebInteractor.h"
#include <QDebug>
#include <QList>
#include <QJsonDocument>
#include "../FangApp.h"

WebInteractor::WebInteractor(QQuickItem *parent) :
    QQuickItem(parent),
    manager(NULL),
    feedList(NULL),
    fangSettings(NULL)
{
    
}

void WebInteractor::init(OperationManager *manager, ListModel *feedList, FangSettings *fangSettings)
{
    this->manager = manager;
    this->feedList = feedList;
    this->fangSettings = fangSettings;

    connect(fangSettings, SIGNAL(styleChanged(QString)), this, SLOT(onStyleChanged(QString)));
    connect(fangSettings, SIGNAL(fontSizeChanged(QString)), this, SLOT(onFontSizeChanged(QString)));
    connect(FangApp::instance(), SIGNAL(specialFeedCountChanged()), this, SIGNAL(specialFeedCountChanged()));
}

qint32 WebInteractor::specialFeedCount()
{
    return FangApp::instance()->specialFeedCount();
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

