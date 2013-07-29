#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>

/**
 * @brief Interface for operations.
 */
class Operation : public QObject
{
    Q_OBJECT
public:
    // OperationManager is parent.
    explicit Operation(QObject *parent = 0);
    
    /**
     * @brief All operations must clean up their memory.
     */
    virtual ~Operation();
    
signals:
    
    /**
     * @brief Indicates that the operation is complete and may be freed.
     */
    void finished(Operation* myself);
    
public slots:
    
    /**
     * @brief Runs the operation.  When complete, finished() must be emitted.
     */
    virtual void execute() {}
};

#endif // OPERATION_H
