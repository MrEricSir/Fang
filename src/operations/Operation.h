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
    enum PriorityLevel {
        BACKGROUND,  // Will get queued up in the background
        IMMEDIATE    // It's gotta happen now; or else!
    };
    
    // OperationManager is parent.
    explicit Operation(PriorityLevel priority, QObject *parent = 0);
    
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
    
    inline PriorityLevel getPriority() { return priority; }
    
private:
    PriorityLevel priority;
};

#endif // OPERATION_H
