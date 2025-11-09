#ifndef NEWSLIST_H
#define NEWSLIST_H

#include <QObject>
#include <QList>
#include <QSet>

#include "../FangObject.h"
class NewsItem;

/**
 * @brief The NewsList class contains a custom list type that internally is also stored as a set.
 *
 * Could be a generic list class.
 */
class NewsList : public FangObject
{
public:
    explicit NewsList(QObject *parent = nullptr);

    /**
     * @brief Delete everything in the list and clear it.
     */
    void clear();

    qsizetype size() const;
    bool isEmpty() const;
    NewsItem* first() const;
    NewsItem* last() const;
    NewsItem* at(qsizetype i) const;
    bool contains(NewsItem* value) const;
    qsizetype indexOf(const NewsItem* value, qsizetype from = 0) const;

    void append(const QList<NewsItem*>* value);
    void prepend(const QList<NewsItem*>* value);
    void append(NewsItem* value);
    void prepend(NewsItem* value);

    /**
     * @brief Removes a certain number of items from the start or end of the list and calls deleteLater() on them.
     * @param fromStart True if from start of list, false if from end.
     * @param numberToRemove
     */
    void removeAndDelete(bool fromStart, qsizetype numberToRemove);

    /**
     * @brief If loaded, returns the news item for a given ID.
     * Linear time complexity.
     */
    NewsItem* newsItemForID(const qint64 id) const;

    /**
     * @brief Returns the index of the position in the list if a news item with ID is in it, otherwise -1.
     * Linear time complexity.
     */
    qsizetype indexForItemID(const qint64 id) const;

    // For list iteration.
    inline QList<NewsItem*>::iterator begin() { return list.begin(); }
    inline QList<NewsItem*>::iterator end() { return list.end(); }

private:
    // Ordered list of news items.
    QList<NewsItem*> list;

    // Set of news items for fast "contains" check.
    QSet<NewsItem*> set;
};

#endif // NEWSLIST_H
