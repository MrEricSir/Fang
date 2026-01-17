#ifndef BATCHWEBPAGEGRABBER_H
#define BATCHWEBPAGEGRABBER_H

#include <QMap>
#include <QUrl>

#include "../FangObject.h"
#include "WebPageGrabber.h"

class BatchWebPageGrabber : public FangObject
{
    Q_OBJECT
public:
    explicit BatchWebPageGrabber(QObject *parent = nullptr);

    // Fetches the webpages and emits ready() with the XHTML document data.
    virtual void load(const QList<QUrl> &urls);

    virtual QMap<QUrl, QString> getResults() { return results; }

signals:
    void ready();

private:
    // Called whenever a grabber is ready or had an error.
    void onWebGrabberReady(WebPageGrabber* grabber, QString *document);

    // WebPage grabbers that are in flight.
    QMap<QUrl, WebPageGrabber*> grabbers;

    // Results of documents found per-URL. Can be empty.
    QMap<QUrl, QString> results;
};

#endif // BATCHWEBPAGEGRABBER_H
