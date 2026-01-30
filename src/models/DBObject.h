#ifndef DBOBJECT_H
#define DBOBJECT_H

#include <QtCore/qtypes.h>

/*!
    \brief Represents an object that is or can be stored as a database row.
 */
class DBObject
{
public:
    virtual qint64 getDbID() const =0;
};

#endif // DBOBJECT_H
