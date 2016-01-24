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
        Sheep * sheep = new Sheep(len, orientation);
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

    qint32 len = 3;
    QPoint pos = QPoint(0,0);
    Qt::Orientation orientation = Qt::Orientation::Horizontal;
    bool isVisible = true;
};

#endif // GHOSTSHEEP_H
