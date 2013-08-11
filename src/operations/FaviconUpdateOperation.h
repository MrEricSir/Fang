#ifndef FAVICONUPDATEOPERATION_H
#define FAVICONUPDATEOPERATION_H

#include "DBOperation.h"
#include <QObject>
#include <QUrl>

#include "../models/FeedItem.h"
#include "../utilities/FaviconGrabber.h"

class FaviconUpdateOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit FaviconUpdateOperation(QObject *parent, FeedItem* feed);
    virtual ~FaviconUpdateOperation();
    
signals:
    
public slots:
    virtual void execute();
    
private slots:
    /**
     * @brief Grabber found a favicon, maybe.
     */
    void onGrabberFinished(const QUrl& faviconUrl);
    
    /**
     * @brief Feed was destroyed before update could complete.
     */
    void onFeedDestroyed();
    
private:
    FeedItem* feed;
    FaviconGrabber grabber;
    bool wasDestroyed;
};

#endif // FAVICONUPDATEOPERATION_H
