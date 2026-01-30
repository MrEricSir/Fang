#ifndef EXPIRENEWSOPERATION_H
#define EXPIRENEWSOPERATION_H

#include "DBOperation.h"
#include <QObject>
#include <QDateTime>

#include "../models/ListModel.h"

/*!
    \brief Deletes old news.  Unread and pinned items are spared.
 */
class ExpireNewsOperation : public DBOperation
{
    Q_OBJECT
public:
    explicit ExpireNewsOperation(OperationManager *parent, ListModel* feedList, QDateTime olderThan, qint32 saveLast);

public slots:
    virtual void execute();

private:
    ListModel* feedList;
    QDateTime olderThan;
    qint32 saveLast;
};

#endif // EXPIRENEWSOPERATION_H
