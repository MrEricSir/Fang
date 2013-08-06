#ifndef SCROLLREADER_H
#define SCROLLREADER_H

#include <QDeclarativeItem>

class ScrollReader : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(ScrollReader)
    
    // Used for reading.
    Q_PROPERTY(qreal contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
    
    // Used for jumping to a position.
    Q_PROPERTY(qreal jumpY READ jumpY WRITE setJumpY NOTIFY jumpYChanged)
    
public:
    explicit ScrollReader(QDeclarativeItem *parent = 0);
    virtual ~ScrollReader() {}
    
    inline qreal contentY() { return _contentY; }
    void setContentY(qreal y);
    
    inline qreal jumpY() { return _jumpY; }
    void setJumpY(qreal y);
    
signals:
    void contentYChanged(qreal);
    void jumpYChanged(qreal);
    
private:
    qreal _contentY;
    qreal _jumpY;
};

QML_DECLARE_TYPE(ScrollReader)

#endif // SCROLLREADER_H
