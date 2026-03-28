#ifndef FEEDSOURCE_H
#define FEEDSOURCE_H

#include <memory>

#include <QObject>
#include <QUrl>

#include "FeedFetchResult.h"
#include "RawFeed.h"

/*!
    \brief Abstract interface for async feed fetch + parse.
 */
class FeedSource : public QObject
{
    Q_OBJECT

public:
    explicit FeedSource(QObject *parent = nullptr);
    virtual ~FeedSource() {}

signals:
    // Call getResult() and getFeed() now, yo!
    void done();

public slots:

    /*!
        \brief Contacts URL and parses the RSS/Atom feed, if it exists.
        \param url               The URL
     */
    virtual void parse(const QUrl& url,
                       const QString& ifNoneMatch = QString(),
                       const QString& ifModifiedSince = QString()) =0;

    virtual FeedFetchResult getResult() =0;
    virtual std::shared_ptr<RawFeed> getFeed() =0;
    virtual QUrl getURL() =0;

    // Conditional request response headers.
    virtual QString responseEtag() { return QString(); }
    virtual QString responseLastModified() { return QString(); }

};

#endif // FEEDSOURCE_H
