#include "SearchIndexHelper.h"

#include <QSearchableIndex.h>
#include <QSearchableItem.h>

void SearchIndexHelper::indexNewsItems(const QList<RawNews*>& items, FeedItem* feed)
{
    if (items.isEmpty()) {
        return;
    }

    QList<QSearchableItem> searchItems;
    QString domain = QStringLiteral("feed-") + QString::number(feed->getDbID());

    for (const RawNews* rawNews : items) {
        QSearchableItem item(QStringLiteral("news-") + QString::number(rawNews->dbId));
        item.setDomainIdentifier(domain);
        item.setTitle(rawNews->title);
        item.setContentDescription(rawNews->description);
        item.setUrl(rawNews->url);
        item.setTimestamp(rawNews->timestamp);
        searchItems.append(item);
    }

    QSearchableIndex::Get()->indexItems(searchItems);
}

void SearchIndexHelper::indexFeed(FeedItem* feed)
{
    QSearchableItem item(QStringLiteral("feed-") + QString::number(feed->getDbID()));
    item.setDomainIdentifier(QStringLiteral("feeds"));
    item.setTitle(feed->getTitle());
    item.setContentDescription(feed->getSubtitle());
    item.setUrl(feed->getSiteURL());

    QSearchableIndex::Get()->indexItems({item});
}

void SearchIndexHelper::indexAllFeeds(ListModel* feedList)
{
    QList<QSearchableItem> searchItems;

    for (int i = 0; i < feedList->rowCount(); i++) {
        FeedItem* feed = qobject_cast<FeedItem*>(feedList->row(i));
        if (!feed || feed->isSpecialFeed() || feed->isFolder()) {
            continue;
        }

        QSearchableItem item(QStringLiteral("feed-") + QString::number(feed->getDbID()));
        item.setDomainIdentifier(QStringLiteral("feeds"));
        item.setTitle(feed->getTitle());
        item.setContentDescription(feed->getSubtitle());
        item.setUrl(feed->getSiteURL());
        searchItems.append(item);
    }

    if (!searchItems.isEmpty()) {
        QSearchableIndex::Get()->indexItems(searchItems);
    }
}

void SearchIndexHelper::removeNewsItems(const QList<qint64>& dbIds)
{
    if (dbIds.isEmpty()) {
        return;
    }

    QStringList identifiers;
    for (qint64 id : dbIds) {
        identifiers.append(QStringLiteral("news-") + QString::number(id));
    }

    QSearchableIndex::Get()->removeItems(identifiers);
}

void SearchIndexHelper::removeFeed(qint64 feedId)
{
    QString feedDomain = QStringLiteral("feed-") + QString::number(feedId);

    auto* index = QSearchableIndex::Get();
    index->removeItemsInDomains({feedDomain});
    index->removeItems({feedDomain});
}
