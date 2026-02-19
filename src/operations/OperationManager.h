#ifndef OPERATIONMANAGER_H
#define OPERATIONMANAGER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QQueue>
#include <QTimer>
#include <QSet>

#include "AsyncOperation.h"
#include "SyncOperation.h"
#include "../FangObject.h"

class OperationManager : public FangObject
{
    Q_OBJECT
public:
    explicit OperationManager(QObject *parent = nullptr);
    virtual ~OperationManager();

public slots:

    /*!
        \brief Adds an async operation. Depending on the priority, it may or may not start immediately.
               Note: The operation WILL be deleted when finished.
        \param operation
     */
    void enqueue(AsyncOperation* operation);

    /*!
        \brief Runs a synchronous operation immediately without adding it to the queue.
               Note: The operation will NOT be deleted.
        \param operation
     */
    void run(SyncOperation* operation);

private slots:

    /*!
        \brief Called by an async operation when it completes.
        \param operation
     */
    void onOperationFinished(AsyncOperation* operation);

    /*!
        \brief Executes queued operations.
        Never call this directly; it's invoked by the timer. Call executeOperations() instead.
     */
    void runNextOperations();

private:

    // Executes the operation queue (at some point in the future.)
    void executeOperations();

    // Immediately runs an operation.
    void runNow(AsyncOperation* operation);

    // Our queue.
    QQueue<AsyncOperation*> queue;

    // Pending operations.
    QSet<AsyncOperation*> pending;

    // Timer to queue future operations.
    QTimer operationTimer;
};

#endif // OPERATIONMANAGER_H
