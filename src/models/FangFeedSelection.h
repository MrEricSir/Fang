#ifndef FANGFEEDSELECTION_H
#define FANGFEEDSELECTION_H

#include <QObject>
#include <QVariant>
//#include <FeedItem.h>

class FangFeedSelection : public QObject
{
    Q_OBJECT
    
    //Q_PROPERTY(FeedItem* selected READ selected WRITE setSelected NOTIFY selectedChanged)
public:
    explicit FangFeedSelection(QObject *parent = 0);
    
signals:
    
public slots:
    
    
    
private:
  //  FeedItem* _selected;
};

#endif // FANGFEEDSELECTION_H
