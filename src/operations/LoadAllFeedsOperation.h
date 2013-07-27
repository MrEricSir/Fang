#ifndef LOADALLFEEDSOPERATION_H
#define LOADALLFEEDSOPERATION_H

#include "Operation.h"

#include <QUrl>
#include <QString>
#include <QDateTime>

#include "../models/FeedItem.h"
#include "../models/ListModel.h"

/**
 * @brief Loads all existing feeds off the disk.
 */
class LoadAllFeedsOperation : public Operation
{
    Q_OBJECT
public:
    explicit LoadAllFeedsOperation(QObject *parent, ListModel *feedList);
    virtual ~LoadAllFeedsOperation();
    
signals:
    
public slots:
    virtual void execute();
    
    
private:
    ListModel *feedList;
};

#endif // LOADALLFEEDSOPERATION_H
