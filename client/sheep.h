#ifndef SHEEP_H
#define SHEEP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPoint>
#include <QDebug>

class SheepPart;
class Sheep : public QGraphicsRectItem
{
public:
    explicit Sheep(bool isMine, qint32 _len, Qt::Orientation _orientation);
    void setPos(QPoint pos);
    QPoint getPos() const {return position;}
    void partHadShooted();

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    static QRectF getSheepRect(qint32 _len, Qt::Orientation _orientation);

private:
    QPoint position = QPoint(0,0);
    qint32 length = 1;
    Qt::Orientation orientation = Qt::Orientation::Horizontal;
    QList<QPoint> takenCells;
    QList<SheepPart *> parts;
    bool isAlive = true;
    qint32 partsAlive;
};

#endif // SHEEP_H
