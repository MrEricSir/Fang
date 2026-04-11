#ifndef OPMLPARSER_H
#define OPMLPARSER_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QXmlStreamReader>

#include "FeedFetchResult.h"
#include "RawFeed.h"
#include <QObject>

/*!
    \brief Parses an OPML document containing an RSS list.  The feeds are
           validated and can be added immediately.
 */
class OPMLParser : public QObject
{
    Q_OBJECT
public:
    explicit OPMLParser(QObject *parent = nullptr);
    virtual ~OPMLParser();
    
signals:
    // Call getResult() and getFeedList() now, yo!
    void done();
    
public slots:
    
    // Starts parsing a file.
    void parseFile(QString filename);
    
    // Gets the result status.
    FeedFetchResult getResult() { return result; }
    
    // Returns the feed list, assuming there is one.
    QList<RawFeed*> getFeedList() { return feedList; }
    
    // Returns the file you passed in parseFile()
    QFile* getFile() { return &file; }
    
private:
    QFile file;
    QList<RawFeed*> feedList;
    FeedFetchResult result;
    
    QXmlStreamReader xml;
};


#endif // OPMLPARSER_H
