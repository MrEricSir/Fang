#ifndef FAVICONUPDATEOPERATION_H
#define FAVICONUPDATEOPERATION_H

#include "DBOperation.h"
#include <QObject>
#include <QUrl>
#include <QImage>

#include "../models/FeedItem.h"
#include "../utilities/FaviconGrabber.h"

class FaviconUpdateOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit FaviconUpdateOperation(OperationManager *parent, FeedItem* feed);
    virtual ~FaviconUpdateOperation();
    
signals:
    
public slots:
    virtual void execute();
    
private slots:
    /**
     * @brief Grabber found a favicon, maybe.
     */
    void onGrabberFinished(const QString& faviconDataUri);
    
private:
    FeedItem* feed;
    FaviconGrabber grabber;
};

#endif // FAVICONUPDATEOPERATION_H
