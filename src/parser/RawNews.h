#ifndef RAWNEWS_H
#define RAWNEWS_H

#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QString>

#include <QDebug>

class RawNews : public QObject
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
    
    bool operator<(const RawNews& rhs);
    
};

#endif // RAWNEWS_H
