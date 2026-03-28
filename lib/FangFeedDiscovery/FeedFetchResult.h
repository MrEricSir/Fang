#ifndef FEEDFETCHRESULT_H
#define FEEDFETCHRESULT_H

#include <QMetaType>

/*!
    \brief Result codes for async feed fetch + parse operations.
 */
enum class FeedFetchResult {
    OK,
    NetworkError,
    FileError,
    ParseError,
    EmptyDocument,
    InProgress,
    NotModified
};

Q_DECLARE_METATYPE(FeedFetchResult)

#endif // FEEDFETCHRESULT_H
