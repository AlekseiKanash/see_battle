#ifndef SHEEPPART_H
#define SHEEPPART_H

#include <QGraphicsRectItem>
#include <QObject>

class Sheep;
class SheepPart : public QGraphicsRectItem
{
public:
    SheepPart(QPoint pos, Sheep * parent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    bool shot();
    void setPos(QPoint pos);
    QPoint getScenePos();

private:
    bool isAlive = true;
    QPoint position;
    Sheep *  parentSheep = nullptr;
};

#endif // SHEEPPART_H
