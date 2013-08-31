#include "MouseWheelArea.h"

MouseWheelArea::MouseWheelArea(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // Let touchpad events go through.
    setAcceptTouchEvents(true);
}

MouseWheelArea::~MouseWheelArea()
{
}
