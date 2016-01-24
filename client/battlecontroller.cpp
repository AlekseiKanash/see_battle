#include "battlecontroller.h"

#include "battlescene.h"

BattleController::BattleController(QObject *parent)
    : QObject(parent)
{
    remoteScene = new BattleScene();
    remoteScene->hide();
}

void BattleController::registerMyScene(BattleScene * myScene)
{
    this->myScene = myScene;
}

void BattleController::registerOpponentScene(BattleScene * opponentScene)
{
    this->opponentScene = opponentScene;
    opponentScene->setIsMine(false);
}

void BattleController::doTest()
{
    remoteScene->addSheep(QPoint(1,1), 3, Qt::Orientation::Vertical);
    remoteScene->addSheep(QPoint(3,1), 3, Qt::Orientation::Horizontal);

    myScene->addSheep(QPoint(3,1), 3, Qt::Orientation::Horizontal);

    for (qint32 i = 0; i < 10; ++i)
    {
        if (remoteScene->shot(QPoint(1,i)))
        {
            opponentScene->addSheep(QPoint(1,i), 1, Qt::Orientation::Vertical);
            opponentScene->shot(QPoint(1,i));
        }
    }

    myScene->shot(QPoint(3,1));
}
