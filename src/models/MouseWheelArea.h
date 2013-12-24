#ifndef MOUSEWHEELAREA_H
#define MOUSEWHEELAREA_H

#include <QQuickItem>
#include <QGraphicsSceneWheelEvent>

class MouseWheelArea : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MouseWheelArea)

public:
    MouseWheelArea(QQuickItem *parent = 0);
    
    virtual ~MouseWheelArea();
    
    inline void wheelEvent(QGraphicsSceneWheelEvent* event)
    {
        emit wheel(event->delta(), event->pos().x(), event->pos().y());
    }

signals:
    void wheel(int delta, qreal mouseX, qreal mouseY);
};

QML_DECLARE_TYPE(MouseWheelArea)



#endif // MOUSEWHEELAREA_H
