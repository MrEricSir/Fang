#include "OperationManager.h"

#include "../utilities/Utilities.h"
#include "../utilities/ErrorHandling.h"
#include "../utilities/FangLogging.h"

OperationManager::OperationManager(QObject *parent) :
    FangObject(parent),
    queue(),
    pending(),
    operationTimer()
{
    operationTimer.setSingleShot(true);
    connect(&operationTimer, &QTimer::timeout, this, &OperationManager::runNextOperations);
}

OperationManager::~OperationManager()
{
}

void OperationManager::enqueue(AsyncOperation *operation)
{
    switch (operation->getPriority()) {
    case AsyncOperation::BACKGROUND:
        // Queue for the future.
        queue.enqueue(operation);
        executeOperations();

        break;

    case AsyncOperation::IMMEDIATE:
        // Let's do it!
        runNow(operation);

        break;

    default:
        FANG_UNREACHABLE("Invalid operation priority");
        // Treat as background operation to avoid crashes
        queue.enqueue(operation);
        executeOperations();
        break;
    }
}

void OperationManager::run(SyncOperation *operation)
{
    // Runs the operation.
    operation->execute();
}

void OperationManager::onOperationFinished(AsyncOperation* operation)
{
    pending.remove(operation);
    operation->deleteLater(); // Trigger safe deletion.
}

void OperationManager::executeOperations()
{
    // Run the next operation at 300ms+ in the future.
    operationTimer.start(300);
}

void OperationManager::runNow(AsyncOperation *operation)
{
    // Double check that we're in the right thread.
    FANG_CHECK(Utilities::isInMainThread(), "OperationManager::runNow called from non-main thread");

    pending.insert(operation);
    QObject::connect(operation, &AsyncOperation::finished, this, &OperationManager::onOperationFinished);
    operation->execute();
}

void OperationManager::runNextOperations()
{
    if (queue.isEmpty()) {
        return; // Nothing to do.
    }

    // Don't do too much at once.  Schedule another call in the future if we're still busy.
    if (pending.size() >= 2) {
        executeOperations();

        return;
    }

    // Pop the next 2 ops off the queue and run 'em.
    int i = 0;
    while(!queue.isEmpty()) {
        if (i >= 2) {
            break;
        }

        i++;
        AsyncOperation* operation = queue.dequeue();
        if (operation == nullptr) {
            qCDebug(logOperation) << "Op null";
            continue;
        }

        // And awaaaaay we go!
        runNow(operation);
    }

    // Schedule the next call.
    executeOperations();
}
