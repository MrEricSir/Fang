#ifndef OPERATIONMANAGER_H
#define OPERATIONMANAGER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QQueue>

#include "Operation.h"

class OperationManager : public QObject
{
    Q_OBJECT
public:
    explicit OperationManager(QObject *parent = 0);
    
signals:
    
public slots:
    
    /**
     * @brief Adds an operation to be performed in FIFO order.  Not guaranteed to be performed
     * immediately.
     * @param operation
     */
    void add(Operation* operation);
    
private slots:
    
    void onOperationFinished(Operation* operation);
    
private:
    
    // Executes pending operations.
    void runPending();
    
    // Our queue.
    QQueue<Operation*> queue;
};

#endif // OPERATIONMANAGER_H
