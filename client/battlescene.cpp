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

void BattleScene::addEnemySheep(QPoint pos, qint32 len, Qt::Orientation orientation)
{
    Sheep * sheepToAdd = new Sheep(false, len, orientation);
    sheepToAdd->setPos(pos);
    battleScene->addItem(sheepToAdd);

    sheepToAdd->setPos(pos);//battleScene->getNewSheepPos());
    sheepToAdd->setVisible(true);
}

void BattleScene::shotToScene(QPointF pos)
{
    qDebug() << "shot from scene to pos " << pos.x() << " : " << pos.y();
    QPoint shotPos = BattleScene::getCellPos(pos);
    shot(shotPos);
}

bool BattleScene::isSheepUnderPos(QPointF pos)
{
    QGraphicsItem * item = battleScene->itemAt(pos, QTransform());

    const qint32 maxPos = SceneParams::cellSize*SceneParams::sceneSize;
    bool isInWidth = pos.x() < maxPos;
    bool isInHeight = pos.y() < maxPos;

    return nullptr != item || !isInWidth || !isInHeight;
}

void BattleScene::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (!isMine)
        {
            shotToScene(event->pos());
            return;
        }

        if (isSheepUnderPos(event->pos()))
            battleScene->removeSheep();
        else
            battleScene->addSheep();
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        if (isMine)
            battleScene->rotateGhostSheep();
    }

    QWidget::mousePressEvent(event);
}

void BattleScene::wheelEvent(QWheelEvent * event)
{
    if (!isMine)
        return;

    if (0 < event->delta())
        battleScene->incGhostLen();
    else
        battleScene->decGhostLen();
}

void BattleScene::shot(QPoint pos)
{
    qDebug() << "shot to " << pos.x() << " : " << pos.y();

    // проходим по всем элементам модели
    for (QGraphicsItem * item : battleScene->items())
    {
        // находим те, которые являются палубами
        SheepPart * part = dynamic_cast<SheepPart *>(item);
        if (part)
        {
            qDebug() << "------";
            qDebug() << "partFound";
            // получаем координаты палубы на сцене
            QPoint itemPos = part->getScenePos();
            qDebug() << "at pos " << itemPos.x() << " : " << itemPos.y();
            // если палуба под мышью - стреляем в нее
            if (itemPos == pos)
            {
                part->shot();
                break;
            }
        }
    }
}

QList<QPoint> getCellsTakenBySheep(Sheep * sheep)
{
    QList<QPoint> sheepCells;
    //qint32 start = sheep->get
}

