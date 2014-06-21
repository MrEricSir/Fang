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
    output << "Title: " << title << endl;
    output << "Subtitle: " << subtitle << endl;
    output << "url: " << url.url() << endl;
    output << "lastUpdated: " << lastUpdated.toString() << endl;
    output << "minutesToUpdate: " << minutesToUpdate << endl;
    output << endl;
    
    RawNews* item;
    foreach (item, items) {
        output << "title: " << item->title << endl;
        output << "author: " << item->author << endl;
        output << "description: " << item->description << endl;
        output << "url: " << item->url.toString() << endl;
        output << endl;
    }
    
    return ret;
}
