#include "NewsItem.h"
#include "NewsList.h"


//class NewsItem;

NewsList::NewsList(QObject *parent)
    : FangObject{parent}
{}

void NewsList::clear()
{
    // Delete each and every news item.
    while(list.size() > 0) {
        list.takeFirst()->deleteLater();
    }

    set.clear();
}

qsizetype NewsList::size() const
{
    return list.size();
}

bool NewsList::isEmpty() const
{
    return list.isEmpty();
}

NewsItem *NewsList::first() const
{
    return list.first();
}

NewsItem *NewsList::last() const
{
    return list.last();
}

NewsItem *NewsList::at(qsizetype i) const
{
    return list.at(i);
}

bool NewsList::contains(NewsItem* value) const
{
    return set.contains(value);
}

qsizetype NewsList::indexOf(const NewsItem *value, qsizetype from) const
{
    return list.indexOf(value, from);
}

void NewsList::append(const QList<NewsItem *> * value)
{
    NewsItem* n;
    for (int i = 0; i < value->size(); ++i) {
        n = value->at(i);
        if (!set.contains(n)) {
            set.insert(n);
            list.append(n);
        } else {
            Q_ASSERT(false);
        }
    }
}

void NewsList::prepend(const QList<NewsItem *> * value)
{
    NewsItem* n;
    for (int i = 0; i < value->size(); ++i) {
        n = value->at(i);
        if (!set.contains(n)) {
            set.insert(n);
            list.prepend(n);
        } else {
            Q_ASSERT(false);
        }
    }
}

void NewsList::append(NewsItem *value)
{
    if (set.contains(value)) {
        Q_ASSERT(false);
        return;
    }

    set.insert(value);
    list.append(value);
}

void NewsList::prepend(NewsItem *value)
{
    if (set.contains(value)) {
        Q_ASSERT(false);
        return;
    }

    set.insert(value);
    list.prepend(value);
}

void NewsList::removeAndDelete(bool fromStart, qsizetype numberToRemove)
{
    // Remove from list, free memory.
    for (qsizetype i = 0; i < numberToRemove; i++) {
        if (fromStart) {
            NewsItem* n = list.takeFirst();
            set.remove(n);
            n->deleteLater();
        } else {
            NewsItem* n = list.takeLast();
            set.remove(n);
            n->deleteLater();
        }
    }
}

NewsItem *NewsList::newsItemForID(const qint64 id) const
{
    if (id < 0) {
        // Invalid ID.
        qDebug() << "Invalid news ID.";
        Q_ASSERT(false);
        return nullptr;
    }

    qsizetype index = indexForItemID(id);
    return index < 0 ? nullptr : list.at(index);
}

qsizetype NewsList::indexForItemID(const qint64 id) const
{
    for (qsizetype i = 0; i < list.count(); ++i) {
        if (list.at(i)->getDbID() == id) {
            return i;
        }
    }

    return -1;
}
