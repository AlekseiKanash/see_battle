#include "battlescene.h"

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

#include "sheep.h"
#include "sheeppart.h"
#include "sceneparameters.h"

BattleScene::BattleScene(QWidget * parent)
    : QWidget(parent)
{
    battleView = new View(this);
    battleScene = new Scene(this);
    battleView->setScene(battleScene);

    qint32 size = SceneParams::sceneSize*SceneParams::cellSize;
    battleView->setSceneRect(0,0, size ,size);
    battleView->scale(1,1);

    battleScene->setGhostSheepVisible(true);

    setMouseTracking(true);
}

BattleScene *BattleScene::create(QWidget * parent)
{
    BattleScene * scene = new BattleScene(parent);
    return scene;
}

QPoint BattleScene::getCellPos(QPointF pos)
{
    QPoint ret(pos.x() / SceneParams::cellSize,
                  pos.y() / SceneParams::cellSize);

    return ret;
}

void BattleScene::addSheep(QPoint pos, qint32 len, Qt::Orientation orientation)
{
    Sheep * sheepToAdd = new Sheep(len, orientation);
    sheepToAdd->setPos(pos);
    sheeps << sheepToAdd;
    battleScene->addItem(sheepToAdd);

    sheepToAdd->setPos(battleScene->getNewSheepPos());
    sheepToAdd->setVisible(true);
}

void BattleScene::mousePressEvent(QMouseEvent * event)
{
    if (!isMine)
    {
        //shot(event->pos());
       // event->accept();
        //return;
    }

    QGraphicsItem * item = battleScene->itemAt(event->pos(), QTransform());

    const qint32 maxPos = SceneParams::cellSize*SceneParams::sceneSize;
    bool isInWidth = event->pos().x() < maxPos;
    bool isInHeight = event->pos().y() < maxPos;
    if (nullptr != item || !isInWidth || !isInHeight)
        return;

    if (isMine)
        battleScene->addSheep();

    QWidget::mousePressEvent(event);
}

void BattleScene::shot(QPointF pos)
{
    qDebug() << "shot from scene!";
    for (QGraphicsItem * item : battleScene->items())
    {
        if (item)
        {
            SheepPart * part = dynamic_cast<SheepPart *>(item);
            if (part)
            {
               // part->shot();
            }
        }
    }
}

QList<QPoint> getCellsTakenBySheep(Sheep * sheep)
{
    QList<QPoint> sheepCells;
    //qint32 start = sheep->get
}

