#include "OperationManager.h"

OperationManager::OperationManager(QObject *parent) :
    FangObject(parent),
    queue(),
    pending(),
    operationTimer()
{
    operationTimer.setSingleShot(true);
    connect(&operationTimer, SIGNAL(timeout()), this, SLOT(runNextOperations()));
}

void OperationManager::add(Operation *operation)
{
    switch (operation->getPriority()) {
    case Operation::BACKGROUND:
        // Queue for the future.
        queue.enqueue(operation);
        executeOperations();
        
        break;
        
    case Operation::IMMEDIATE:
        // Let's do it!
        runNow(operation);
        
        break;
        
    default:
        Q_ASSERT(false); // Not a valid priority level. :(
    }
}

void OperationManager::onOperationFinished(Operation* operation)
{
    pending.remove(operation);
    emit(operationFinished(operation));
    
    //qDebug() << "Operation finished";
    operation->deleteLater(); // Trigger safe deletion.
}

void OperationManager::executeOperations()
{
    // Run the next operation at 300ms+ in the future.
    operationTimer.start(300);
}

void OperationManager::runNow(Operation *operation)
{
    pending.insert(operation);
    QObject::connect(operation, SIGNAL(finished(Operation*)),
                     this, SLOT(onOperationFinished(Operation*)));
    operation->execute();
}

void OperationManager::runNextOperations()
{
    if (queue.isEmpty())
        return; // Nothing to do.
    
    // Don't do too much at once.  Schedule another call in the future if we're still busy.
    if (pending.size() >= 2) {
        executeOperations();
        
        return; 
    }
    
    // Pop the next 2 ops off the queue and run 'em.
    int i = 0;
    while(!queue.isEmpty()) {
        if (i >= 2)
            break;
        
        i++;
        Operation* operation = queue.dequeue();
        if (operation == NULL) {
            qDebug() << "Op null";
            continue;
        }
        
        // And awaaaaay we go!
        runNow(operation);
    }
    
    // Schedule the next call.
    executeOperations();
}
