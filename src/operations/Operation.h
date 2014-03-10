#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>

#define FANG_BACKGROUND_CHECK do { if (shouldTerminate()) return; } while(0)

class OperationManager;

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
    explicit Operation(PriorityLevel priority, OperationManager* parent);
    
    /**
     * @brief All operations must clean up their memory.
     */
    virtual ~Operation();
    
protected slots:
    
    /**
     * @brief Call this to report an error.  Automatically emits finished()
     * @param errorString The text that will be logged along with the error.
     */
    void reportError(const QString& errorString);
    
    /**
     * @brief Pass any QObjects that might be deleted during the run into this method.
     * It will cause the operation to be canceled gracefully, emitting done().
     * See also: FANG_BACKGROUND_CHECK macro.
     * @param object
     */
    void requireObject(QObject* object);
    
    /**
     * @brief Used by the FANG_BACKGROUND_CHECK macro.
     * @return 
     */
    bool shouldTerminate() { return terminate; }
    
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
    
    /**
     * @return Priority level of this operation type.
     */
    inline PriorityLevel getPriority() { return priority; }
    
    /**
     * @return Returns true if there was an error, else false. 
     */
    inline bool isError() { return error; }
    
    /**
     * @brief If your operation needs to invoke other operations (yo dawg, I heard you like
     * operations) then you'll want to use this.
     * @return The operation manager used for getting/setting operations.
     */
    OperationManager* getOperationManager() { return operationManager; }
    
private slots:
    
    // Called when a required object is destroyed.
    void onRequiredQObjectDestroyed(QObject* object);
    
private:
    OperationManager* operationManager;
    PriorityLevel priority;
    bool error;
    bool terminate;
};

#endif // OPERATION_H
