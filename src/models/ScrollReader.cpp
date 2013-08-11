#include "ScrollReader.h"

ScrollReader::ScrollReader(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    _contentY(0),
    _jumpY(0),
    _bottomSpacer(0)
{
}

void ScrollReader::setContentY(qreal y)
{
    if (y == _contentY)
        return;
    
    _contentY = y;
    emit contentYChanged(_contentY);
}

void ScrollReader::setJumpY(qreal y)
{
    if (y == _jumpY)
        return;
    
    _jumpY = y;
    emit jumpYChanged(_jumpY);
}

void ScrollReader::setBottomSpacer(qreal spacer)
{
    if (spacer == _bottomSpacer)
        return;
    
    _bottomSpacer = spacer;
    emit bottomSpacerChanged(_bottomSpacer);
}
