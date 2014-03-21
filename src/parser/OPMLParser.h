#ifndef OPMLPARSER_H
#define OPMLPARSER_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QXmlStreamReader>

#include "ParserInterface.h"
#include "RawFeed.h"

class OPMLParser : public QObject
{
    Q_OBJECT
public:
    explicit OPMLParser(QObject *parent = 0);
    virtual ~OPMLParser();
signals:
    // Call getResult() and getFeed() now, yo!
    void done();
    
public slots:
    void parseFile(QString filename);
    
    QList<RawFeed*> getResult() { return feedList; }
    QFile* getFile() { return &file; }
    
private:
    QFile file;
    QList<RawFeed*> feedList;
    ParserInterface::ParseResult result;
    
    QXmlStreamReader xml;
};


#endif // OPMLPARSER_H
