#include "ScrollReader.h"

ScrollReader::ScrollReader(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    _contentY(0)
{
}

void ScrollReader::setContentY(qreal y)
{
    if (y == _contentY)
        return;
    
    _contentY = y;
    emit contentYChanged(_contentY);
}
