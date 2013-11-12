#include "WebInteractor.h"
#include <QDebug>
#include <QList>

WebInteractor::WebInteractor(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    currentFeed(NULL),
    manager(NULL)
{
    
}

void WebInteractor::init(OperationManager *manager)
{
    this->manager = manager;
}

void WebInteractor::loadNext()
{
    qDebug() << "Load next!";
}

void WebInteractor::loadPrevious()
{
    qDebug() << "Load prev!";
}

void WebInteractor::setFeed(FeedItem *feed)
{
    if (feed == NULL)
        return;
    
    // To save memory, clean up the old feed before continuing.
    if (currentFeed != NULL)
        currentFeed->clearNews();
    
    currentFeed = feed;
    
    // Okay, now LOAD the damn feed, y'all.
    LoadNews* loader = new LoadNews(manager, currentFeed);
    connect(loader, SIGNAL(finished(Operation*)), this, SLOT(onLoadNewsFinished(Operation*)));
    manager->add(loader);
}

void WebInteractor::onLoadNewsFinished(Operation* operation)
{
    LoadNews* loader = qobject_cast<LoadNews*>(operation);
    Q_ASSERT(loader != NULL); // If this ever happens, we're fucked.
    
    // TODO: right now we're only handling the initial load.
    QList<NewsItem*>* newsList = loader->getFeedItem()->getNewsList();
    foreach(NewsItem* item, *newsList)
        emit add(true,
                 escapeCharacters(item->getTitle()),
                 escapeCharacters(item->getURL().toString()),
                 escapeCharacters(item->getFeed()->getTitle()),
                 escapeCharacters(item->getTimestamp().toString()),
                 escapeCharacters( item->getContent() != "" ? item->getContent() : item->getSummary()) );
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
