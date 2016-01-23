#ifndef SHEEP_H
#define SHEEP_H

#include <QGraphicsItem>
#include <QVector2D>

class Sheep : public QGraphicsRectItem
{
public:
    explicit Sheep(qint32 _len, Qt::Orientation _orientation);
    void setPos(QVector2D pos);
    QVector2D getPos() const {return position;}

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:
    QVector2D position;
    qint32 length;
    Qt::Orientation orientation;
    QList<QVector2D> takenCells;
};

#endif // SHEEP_H
