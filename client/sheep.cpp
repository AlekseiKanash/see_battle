#include "sheep.h"

#include <QVector2D>
#include <QPainter>

#include "sceneparameters.h"

Sheep::Sheep(qint32 _len, Qt::Orientation _orientation)
    : length(_len)
    , orientation(_orientation)
{
    Q_ASSERT(length >= 1 && length <= 5);
    Q_ASSERT(Qt::Orientation::Vertical == orientation
             || Qt::Orientation::Horizontal == orientation);

    QRect itemRect;
    if (Qt::Orientation::Vertical == orientation)
    {
        itemRect.setHeight(length * SceneParams::cellSize);
        itemRect.setWidth(SceneParams::cellSize);
    }
    else
    {
        itemRect.setHeight(SceneParams::cellSize);
        itemRect.setWidth(length * SceneParams::cellSize);
    }

    setRect(itemRect);
}

void Sheep::setPos(QVector2D pos)
{
    position = pos;

    qint32 x = position.x() * SceneParams::cellSize;
    qint32 y = position.y() * SceneParams::cellSize;

    moveBy(x, y);
}

void Sheep::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setWidth(SceneParams::sheepBorderWidth);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(Qt::blue));

    painter->save();
    painter->setPen(pen);
    painter->drawRect(rect());
    painter->end();
    painter->restore();
}
