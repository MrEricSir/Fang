#include "OperationManager.h"

OperationManager::OperationManager(QObject *parent) :
    QObject(parent),
    queue()
{
}

void OperationManager::add(Operation *operation)
{
    queue.enqueue(operation);
    runPending(); // TODO: add a timer so we don't run 'em one at a time
}

void OperationManager::onOperationFinished(Operation* operation)
{
    // TODO: come up with real memory management system.
    //qDebug() << "Operation finished";
    //delete operation; // Signal is auto-disconnected.
    //qDebug() << "operation FREEd";
}

void OperationManager::runPending()
{
    // Throw any and all operations on to the queue.
    // TODO: only run a small batch at a time to keep the UI responsive.
    while(!queue.isEmpty()) {
        Operation* operation = queue.dequeue();
        if (operation == NULL) {
            qDebug() << "Op null";
            return;
        }
        
        QObject::connect(operation, SIGNAL(finished(Operation*)),
                         this, SLOT(onOperationFinished(Operation*)));
        operation->execute();
    }
}
