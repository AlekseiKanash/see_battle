#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "sheep.h"

#include <QList>
#include <QWidget>
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>

#include "ghostsheep.h"
#include "sceneparameters.h"

class QGraphicsScene;
class QGraphicsView;

class BattleScene : public QWidget
{

Q_OBJECT    

private:
    BattleScene(QWidget *parent = NULL);

public:
    static BattleScene * create(QWidget *parent);
    static QPoint getCellPos(QPointF pos);
    void setIsMine(bool mine) {isMine = mine;}
    void shot(QPoint pos); // inCells
    void shotToScene(QPointF pos);
    bool isSheepUnderPos(QPointF pos);

public slots:
    void addEnemySheep(QPoint pos, qint32 len, Qt::Orientation orientation);

private:
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void wheelEvent(QWheelEvent * event);

    void drawGrid();

private:
    class View : public QGraphicsView
    {
    public:
        View(QWidget * parent)
            : QGraphicsView(parent)
        {
            setMouseTracking(true);
        }

        virtual void mouseMoveEvent(QMouseEvent * event)
        {
            QGraphicsView::mouseMoveEvent(event);
            static_cast<Scene *>(scene())->moveGhostSheep(event->pos());
        }
    };

    class Scene : public QGraphicsScene
    {
    public:
        Scene(QObject * parent)
            : QGraphicsScene(parent)
        {
        }

        virtual void drawBackground(QPainter * painter, const QRectF & rect)
        {
            QGraphicsScene::drawBackground(painter, rect);

            painter->save();
            for (qint32 i = 0; i < SceneParams::sceneSize; ++i)
            {
                QPen pen;
                pen.setWidth(SceneParams::sheetLinesWidth);
                painter->setPen(pen);
                painter->drawLine(0, i * SceneParams::cellSize, rect.width(), i * SceneParams::cellSize);
                painter->drawLine(i * SceneParams::cellSize, 0, i * SceneParams::cellSize, rect.height());
            }
            painter->restore();

            if (ghostSheep.isVisible)
            {
                ghostSheep.paint(painter);
            }
        }

        void incGhostLen()
        {
            ghostSheep.incLen();
            update();
        }

        void decGhostLen()
        {
            ghostSheep.decLen();
            update();
        }

        void moveGhostSheep(QPointF pos)
        {
            if (ghostSheep.isVisible)
            {
                QPoint curPos(BattleScene::getCellPos(pos));
                if (curPos != prevGhostSheepPos)
                {
                    prevGhostSheepPos = curPos;
                    ghostSheep.pos = prevGhostSheepPos;
                    update();
                }
            }
        }

        void rotateGhostSheep()
        {
            ghostSheep.rotate();
        }

        void setGhostSheepVisible(bool hasGhost)
        {
            ghostSheep.isVisible = hasGhost;
        }

        QPoint getNewSheepPos()
        {
            return ghostSheep.pos;
        }

        void addSheep()
        {
            addItem(ghostSheep.createSheep());
        }

        void removeSheep()
        {
            float x = ghostSheep.pos.x()*SceneParams::cellSize;
            float y = ghostSheep.pos.y()*SceneParams::cellSize;

            QList<QGraphicsItem *> sceneItems = items(QPointF(x,y));
            for (QGraphicsItem * item : sceneItems)
            {
                Sheep * sheep = dynamic_cast<Sheep *>(item);
                if (sheep)
                {
                    removeItem(sheep);
                }
            }
        }

    private:
        GhostSheep ghostSheep;
        QPoint prevGhostSheepPos;
    };

private:
    bool isMine = true;
    qint32 newSheepLen = 1;
    Scene * battleScene;
    View * battleView;

    QList<QPoint> cellsToAddSheep;
};

#endif // BATTLESCENE_H
