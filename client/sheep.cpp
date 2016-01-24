#include "sheep.h"

#include <QPoint>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "battlescene.h"
#include "sceneparameters.h"
#include "sheeppart.h"

Sheep::Sheep(qint32 _len, Qt::Orientation _orientation)
    : length(_len)
    , orientation(_orientation)
{
    Q_ASSERT(length >= 1 && length <= 5);
    Q_ASSERT(Qt::Orientation::Vertical == orientation
             || Qt::Orientation::Horizontal == orientation);

    QRectF itemRect = Sheep::getSheepRect(length, orientation);

    setRect(itemRect);

    partsAlive = length;
    for (qint32 i = 0; i < length; ++i)
    {
        QPoint pos;

        if (Qt::Orientation::Vertical == orientation)
        {
            pos = QPoint (0, i);
        }
        else
        {
            pos = QPoint (i, 0);
        }

        qDebug() << "adding part " << pos.x() << " : " << pos.y();

        SheepPart * part = new SheepPart(pos, this);
        part->setParentItem(this);
        part->setPos(pos);
    }
}

void Sheep::setPos(QPoint pos)
{
    position = pos;

    qDebug() << "setPos";
    qDebug() << pos.x() << " : " << pos.y();

    qint32 x = position.x() * SceneParams::cellSize;
    qint32 y = position.y() * SceneParams::cellSize;

    QGraphicsItem::setPos(QPointF(x, y));
}

void Sheep::partHadShooted()
{
    partsAlive--;
    if (0 == partsAlive)
    {
        isAlive = false;
        update();
    }
}

QRectF Sheep::getSheepRect(qint32 _len, Qt::Orientation _orientation)
{
    QRectF itemRect;
    if (Qt::Orientation::Vertical == _orientation)
    {
        itemRect.setHeight(_len * SceneParams::cellSize);
        itemRect.setWidth(SceneParams::cellSize);
    }
    else
    {
        itemRect.setHeight(SceneParams::cellSize);
        itemRect.setWidth(_len * SceneParams::cellSize);
    }
    return itemRect;
}

void Sheep::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!isAlive)
    {
        painter->save();
        painter->setBrush(QColor(255,0,0, 70));
        QRectF itemRect = Sheep::getSheepRect(length, orientation);
        painter->drawRect(itemRect);
        painter->restore();
    }
}


