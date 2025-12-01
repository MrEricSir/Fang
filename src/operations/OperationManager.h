#ifndef OPERATIONMANAGER_H
#define OPERATIONMANAGER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QQueue>
#include <QTimer>
#include <QSet>

#include "Operation.h"
#include "DBOperationSynchronous.h"
#include "../FangObject.h"

class OperationManager : public FangObject
{
    Q_OBJECT
public:
    explicit OperationManager(QObject *parent = nullptr);
    virtual ~OperationManager();
    
public slots:
    
    /**
     * @brief Adds an operation.  Depending on the priority level, it may or may not start immediately.
     *        Note: The operation WILL be deleted when finished.
     * @param operation
     */
    void add(Operation* operation);

    /**
     * @brief Runs an operation without adding it to the queue. It will always be run immediately.
     *        Note: The operation will NOT be deleted.
     * @param operation
     */
    void runSynchronously(DBOperationSynchronous* operation);
    
private slots:
    
    /**
     * @brief Called by an operation when it completes.
     * @param operation
     */
    void onOperationFinished(Operation* operation);
    
    /** 
     * @brief Executes queued operations.
     * Never call this directly; it's invoked by the timer. Call executeOperations() instead.
     */
    void runNextOperations();
    
private:
    
    // Executes the operation queue (at some point in the future.)
    void executeOperations();
    
    // Immediately runs an operation.
    void runNow(Operation* operation);
    
    // Our queue.
    QQueue<Operation*> queue;
    
    // Pending operations.
    QSet<Operation*> pending;
    
    // Timer to queue future operations.
    QTimer operationTimer;
};

#endif // OPERATIONMANAGER_H
