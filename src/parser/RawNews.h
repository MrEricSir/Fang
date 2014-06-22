#ifndef RAWNEWS_H
#define RAWNEWS_H

#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QString>

#include <QDebug>

#include "../FangObject.h"

class RawNews : public FangObject
{
    Q_OBJECT
public:
    explicit RawNews(QObject *parent = 0);
    
    virtual ~RawNews() {}
    
    QString title;
    QString author;
    QString description;
    QString content;
    QDateTime timestamp;
    QUrl url;
    
    // For convenience.
    qint64 dbId;
    
    // Sorting
    bool operator<(const RawNews& right);
    static bool LessThan(const RawNews* left, const RawNews* right);
    static bool GreaterThan(const RawNews* left, const RawNews* right);
    
};

#endif // RAWNEWS_H
