#ifndef SCROLLREADER_H
#define SCROLLREADER_H

#include <QDeclarativeItem>

class ScrollReader : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(ScrollReader)
    
    Q_PROPERTY(qreal contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
    
public:
    explicit ScrollReader(QDeclarativeItem *parent = 0);
    virtual ~ScrollReader() {}
    
    inline qreal contentY() { return _contentY; }
    void setContentY(qreal y);
    
signals:
    void contentYChanged(qreal);
    
private:
    qreal _contentY;
};

QML_DECLARE_TYPE(ScrollReader)

#endif // SCROLLREADER_H
