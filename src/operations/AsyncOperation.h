#ifndef ASYNCOPERATION_H
#define ASYNCOPERATION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "../FangObject.h"

#define FANG_BACKGROUND_CHECK do { if (shouldTerminate()) return; } while(0)

class OperationManager;

/*!
    \brief Base class for asynchronous operations. Signals indicate completion.

    Intended to be used for network requests, etc.
 */
class AsyncOperation : public FangObject
{
    Q_OBJECT

public:
    enum Priority {
         BACKGROUND,  // Will get queued up in the background
         IMMEDIATE    // Schedule for the immediate future
    };

    explicit AsyncOperation(Priority priority, OperationManager* parent);
    virtual ~AsyncOperation() = default;

protected slots:

    /*!
        \brief Call this to report an error.  Automatically emits finished()
        \param errorString The text that will be logged along with the error.
     */
    void reportError(const QString& errorString);

    /*!
        \brief Pass any QObjects that might be deleted during the run into this method.
        It will cause the operation to be canceled gracefully, emitting finished().
        See also: FANG_BACKGROUND_CHECK macro.
        \param object
     */
    void requireObject(QObject* object);

    /*!
        \brief Used by the FANG_BACKGROUND_CHECK macro.
        \return
     */
    bool shouldTerminate() { return terminate; }

signals:

    /*!
        \brief Indicates that the operation is complete and may be freed.
     */
    void finished(AsyncOperation* myself);

public slots:

    /*!
        \brief Runs the operation.  When complete, finished() must be emitted.
     */
    virtual void execute() = 0;

    /*!
        \return Priority of this operation.
     */
    inline Priority getPriority() { return priority; }

    /*!
        \return Returns true if there was an error, else false.
     */
    inline bool isError() { return error; }

    /*!
        \brief If your operation needs to invoke other operations (yo dawg, I heard you like
        operations) then you'll want to use this.
        \return The operation manager used for getting/setting operations.
     */
    OperationManager* getOperationManager() { return operationManager; }

    /*!
        \brief Returns the database connection.
     */
    QSqlDatabase db();

protected:

    /*!
        \brief Call this to report a SQL error.  Automatically emits finished()
        \param query
        \param errorString The text that will be logged along with the error.
     */
    void reportSQLError(const QSqlQuery& query, const QString& errorString);

private slots:

    // Called when a required object is destroyed.
    void onRequiredQObjectDestroyed(QObject* object);

private:
    OperationManager* operationManager;
    Priority priority;
    bool error;
    bool terminate;
};

#endif // ASYNCOPERATION_H
