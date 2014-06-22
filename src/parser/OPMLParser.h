#ifndef OPMLPARSER_H
#define OPMLPARSER_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QXmlStreamReader>

#include "ParserInterface.h"
#include "RawFeed.h"
#include "../FangObject.h"

/**
 * @brief Parses an OPML document containing an RSS list.  The feeds are
 *        validated and can be added immediately.
 */
class OPMLParser : public FangObject
{
    Q_OBJECT
public:
    explicit OPMLParser(QObject *parent = 0);
    virtual ~OPMLParser();
    
signals:
    // Call getResult() and getFeedList() now, yo!
    void done();
    
public slots:
    
    // Starts parsing a file.
    void parseFile(QString filename);
    
    // Gets the result status.
    ParserInterface::ParseResult getResult() { return result; }
    
    // Returns the feed list, assuming there is one.
    QList<RawFeed*> getFeedList() { return feedList; }
    
    // Returns the file you passed in parseFile()
    QFile* getFile() { return &file; }
    
private:
    QFile file;
    QList<RawFeed*> feedList;
    ParserInterface::ParseResult result;
    
    QXmlStreamReader xml;
};


#endif // OPMLPARSER_H
