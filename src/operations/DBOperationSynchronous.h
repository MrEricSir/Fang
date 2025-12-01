#ifndef DBOPERATIONSYNCHRONOUS_H
#define DBOPERATIONSYNCHRONOUS_H

#include "DBOperation.h"

/**
 * @brief Runs a DB operation that doesn't wait for signal completion (network requests, etc.)
 *        before it can be completed.
 */
class DBOperationSynchronous : public DBOperation
{
    Q_OBJECT
public:
    explicit DBOperationSynchronous(OperationManager *parent);
    virtual ~DBOperationSynchronous() = default;

public slots:

    /**
     * @brief Executes the underlying operation with executeSynchronous() and then emit the
     *        finished() signal.
     */
    virtual void execute() final;

    /**
     * @brief Executes an operation that can be run without waiting for completion, for example
     *        a simple DB query.
     */
    virtual void executeSynchronous() = 0;

};

#endif // DBOPERATIONSYNCHRONOUS_H
