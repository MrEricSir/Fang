#ifndef SYNCOPERATION_H
#define SYNCOPERATION_H

#include <QObject>
#include <QString>

#include "../FangObject.h"

class OperationManager;

/*!
    \brief Base class for synchronous operations. This is mainly used for operations that
    complete quickly and/or need to happen in a certain order, such as database operations.
 */
class SyncOperation : public FangObject
{
    Q_OBJECT

public:
    explicit SyncOperation(OperationManager* parent);
    virtual ~SyncOperation() = default;

    /*!
        \brief Executes the operation synchronously.
     */
    virtual void execute() = 0;

    /*!
        \return Returns true if there was an error, else false.
     */
    bool hasError() const { return error; }

    /*!
        \return Error message, if any.
     */
    QString errorMessage() const { return errorMsg; }

protected:

    /*!
        \brief Call this to report an error. Logs the error and sets the error flag.
        Unlike AsyncOperation::reportError(), this does NOT emit any signals.
        \param errorString The text that will be logged along with the error.
     */
    void reportError(const QString& errorString);

private:
    OperationManager* operationManager;
    bool error = false;
    QString errorMsg;
};

#endif // SYNCOPERATION_H
