#ifndef BACKGROUNDPARSERTHREAD_H
#define BACKGROUNDPARSERTHREAD_H

#include <QThread>
#include "Parser.h"

class BackgroundParserThread : public QThread
{
    Q_OBJECT
public:
    explicit BackgroundParserThread(QObject *parent = 0);
    
    void setUrl(const QUrl& url);
    
    void run() Q_DECL_OVERRIDE;
    
    inline Parser* getParser() { return parser; }
    
signals:
    void parserDone();
    
protected slots:
    void onDone();
    
private:
    Parser* parser;
    QUrl url;
    
};

#endif // BACKGROUNDPARSERTHREAD_H
