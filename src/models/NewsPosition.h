#ifndef NEWSPOSITION_H
#define NEWSPOSITION_H

#include <QDateTime>

/*!
    \brief Represents a position in a news feed using (timestamp, id) tuple.

    This matches the in-memory data with the SQLite database ordering:
        ORDER BY timestamp ASC, id ASC

    Used for bookmark comparisons in Lisvel feeds where items may not appear
    in strictly chronological order.
 */
class NewsPosition
{
public:
    NewsPosition() : _id(-1), _timestamp() {}
    NewsPosition(qint64 id, const QDateTime& timestamp) : _id(id), _timestamp(timestamp) {}

    inline qint64 id() const { return _id; }
    inline const QDateTime& timestamp() const { return _timestamp; }
    inline bool isValid() const { return _id >= 0 && _timestamp.isValid(); }

    /*!
        \brief Compare positions.
        \return true if this position comes AFTER other in reading order.
     */
    inline bool isAfter(const NewsPosition& other) const
    {
        if (!isValid() || !other.isValid()) {
            return false;
        } else if (_timestamp > other._timestamp) {
            return true;
        } else if (_timestamp == other._timestamp) {
            return _id > other._id;
        }

        return false;
    }

    /*!
        \brief Compare positions.
        \return true if this position comes BEFORE other in reading order.
     */
    inline bool isBefore(const NewsPosition& other) const
    {
        if (!isValid() || !other.isValid()) {
            return false;
        } else if (_timestamp < other._timestamp) {
            return true;
        } else if (_timestamp == other._timestamp) {
            return _id < other._id;
        }

        return false;
    }

    inline bool operator==(const NewsPosition& other) const
    {
        return _id == other._id && _timestamp == other._timestamp;
    }

    inline bool operator!=(const NewsPosition& other) const
    {
        return !(*this == other);
    }

private:
    qint64 _id;
    QDateTime _timestamp;
};

#endif // NEWSPOSITION_H
