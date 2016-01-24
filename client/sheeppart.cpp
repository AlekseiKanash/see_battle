#include "sheeppart.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPoint>
#include <QPainter>

#include "sheep.h"
#include "sceneparameters.h"

SheepPart::SheepPart(QPoint pos, Sheep * parent)
    : position(pos)
    , parentSheep(parent)
{
    setRect(QRectF(0,0, SceneParams::cellSize, SceneParams::cellSize));
}

void SheepPart::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    shot();
    QGraphicsRectItem::mousePressEvent(event);
}

void SheepPart::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setWidth(SceneParams::sheepBorderWidth);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(Qt::blue));

    painter->save();
    painter->setPen(pen);

    QRectF itemRect = rect();

    painter->drawRect(itemRect);

    if (!isAlive)
    {
        painter->setPen(Qt::red);
        painter->drawLine(itemRect.x(), itemRect.y(), itemRect.width(), itemRect.height());
        painter->drawLine(itemRect.width(), itemRect.y(), itemRect.x(), itemRect.height());
    }

    painter->restore();
}

void SheepPart::shot()
{
    qDebug() << "Part Shot";
    if (isAlive)
    {
        isAlive = false;
        parentSheep->partHadShooted();
        update();
    }
}

void SheepPart::setPos(QPoint pos)
{
    position = pos;

    qint32 x = position.x() * SceneParams::cellSize;
    qint32 y = position.y() * SceneParams::cellSize;

    QGraphicsItem::setPos(QPointF(x, y));
}
