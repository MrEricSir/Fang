#ifndef RAWNEWS_H
#define RAWNEWS_H

#include <QDateTime>
#include <QUrl>
#include <QString>

class RawNews
{
public:
    RawNews() = default;

    QString title;
    QString author;
    QString description;
    QString content;
    QDateTime timestamp;
    QUrl url;
    QString guid;
    QString mediaImageURL;

    // Sorting
    bool operator<(const RawNews& right);
    static bool LessThan(const RawNews* left, const RawNews* right);
    static bool GreaterThan(const RawNews* left, const RawNews* right);
};

#endif // RAWNEWS_H
