#include "RawFeed.h"
#include <QString>
#include <QTextStream>
#include <QDebug>

RawFeed::RawFeed(QObject *parent) :
    FangObject(parent),
    title(""),
    subtitle(""),
    url(),
    lastUpdated(),
    minutesToUpdate(0),
    siteURL(),
    imageURL(),
    items()
{
}

RawFeed::~RawFeed()
{
}

QString RawFeed::toString()
{
    QString ret;
    QTextStream output(&ret);
    output << "Title: " << title << Qt::endl;
    output << "Subtitle: " << subtitle << Qt::endl;
    output << "url: " << url.url() << Qt::endl;
    output << "lastUpdated: " << lastUpdated.toString() << Qt::endl;
    output << "minutesToUpdate: " << minutesToUpdate << Qt::endl;
    output << Qt::endl;

    for (RawNews* item : items) {
        output << "title: " << item->title << Qt::endl;
        output << "author: " << item->author << Qt::endl;
        output << "description: " << item->description << Qt::endl;
        output << "url: " << item->url.toString() << Qt::endl;
        output << Qt::endl;
    }
    
    return ret;
}
