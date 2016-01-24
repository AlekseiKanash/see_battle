#ifndef GHOSTSHEEP_H
#define GHOSTSHEEP_H

#include <QBrush>

#include "sceneparameters.h"
#include "sheep.h"

class GhostSheep
{
public:
    Sheep * createSheep()
    {
        Sheep * sheep = new Sheep(true, len, orientation);
        sheep->setPos(pos);
        return sheep;
    }

    void paint(QPainter * painter)
    {
        QRectF itemRect = Sheep::getSheepRect(len, orientation);

        qint32 x = pos.x() * SceneParams::cellSize;
        qint32 y = pos.y() * SceneParams::cellSize;

        itemRect.moveTo(x, y);

        painter->save();
        painter->setBrush(QColor(0, 0, 255, 20));
        painter->setPen(Qt::blue);
        painter->drawRect(itemRect);
        painter->restore();
    }

    void incLen()
    {
        if (len < SceneParams::maxLen)
            len++;
    }

    void decLen()
    {
        if (len > SceneParams::minLen)
            len--;
    }

    void rotate()
    {
        if (Qt::Orientation::Vertical == orientation)
            orientation = Qt::Orientation::Horizontal;
        else
            orientation = Qt::Orientation::Vertical;
    }

    qint32 len = 1;
    QPoint pos = QPoint(-2,-2); // hide
    Qt::Orientation orientation = Qt::Orientation::Vertical;
    bool isVisible = true;
};

#endif // GHOSTSHEEP_H
