#include "MouseWheelArea.h"

MouseWheelArea::MouseWheelArea(QQuickItem *parent) :
    QQuickItem(parent)
{
    // Let touchpad events go through.
    //setAcceptTouchEvents(true);
}

MouseWheelArea::~MouseWheelArea()
{
}
