#ifndef FEEDSOURCE_H
#define FEEDSOURCE_H

#include <QObject>
#include <QUrl>

#include "RawFeed.h"

#include "../FangObject.h"

/*!
    \brief Abstract interface for async feed fetch + parse.
 */
class FeedSource : public FangObject
{
    Q_OBJECT

public:
    enum ParseResult { OK, NETWORK_ERROR, FILE_ERROR, PARSE_ERROR, EMPTY_DOCUMENT, IN_PROGRESS, NOT_MODIFIED };
    Q_ENUM(ParseResult)

    explicit FeedSource(QObject *parent = nullptr);
    virtual ~FeedSource() {}

signals:
    // Call getResult() and getFeed() now, yo!
    void done();

public slots:

    /*!
        \brief Contacts URL and parses the RSS/Atom feed, if it exists.
        \param url               The URL
        \param noParseIfCached   If true, this won't bother with the
                                 parse if the content was cached.
     */
    virtual void parse(const QUrl& url, bool noParseIfCached = false,
                       const QString& ifNoneMatch = QString(),
                       const QString& ifModifiedSince = QString()) =0;

    virtual FeedSource::ParseResult getResult() =0;
    virtual RawFeed* getFeed() =0;
    virtual QUrl getURL() =0;

    // Whether or not the response was cached.
    virtual bool isFromCache() =0;

    // Conditional request response headers.
    virtual QString responseEtag() { return QString(); }
    virtual QString responseLastModified() { return QString(); }

};

#endif // FEEDSOURCE_H
