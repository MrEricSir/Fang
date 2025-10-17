#include "Utilities.h"

#include <QDebug>

Utilities::Utilities()
{
}

FeedItem *Utilities::feedItemFromRaw(const RawFeed *raw, qint64 dbId, QObject* parent)
{
    return new FeedItem(dbId,
                        0,
                        raw->title,
                        raw->subtitle,
                        raw->lastUpdated,
                        raw->minutesToUpdate,
                        raw->url,
                        raw->siteURL,
                        raw->imageURL,
                        QDateTime(),
                        -1,
                        true,
                        parent
                        );
}

QString Utilities::commaSeparatedStringList(const QVector<qint64> input)
{
    QString output;
    int size = input.size();
    for(int i = 0; i < size; i++) {
        output += QString::number(input.at(i));

        if (i != size - 1) {
            output += ", ";
        }
    }

    return output;
}
