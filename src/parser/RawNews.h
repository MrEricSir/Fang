#ifndef RAWNEWS_H
#define RAWNEWS_H

#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QString>

class RawNews : public QObject
{
    Q_OBJECT
public:
    explicit RawNews(QObject *parent = 0);
    
    QString title;
    QString author;
    QString description;
    QDateTime timestamp;
    QUrl url;
    
    bool operator<(const RawNews& rhs);
    
};

#endif // RAWNEWS_H
