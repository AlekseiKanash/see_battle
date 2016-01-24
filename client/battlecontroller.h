#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

#include <QObject>

class BattleScene;
class BattleController : public QObject
{
    Q_OBJECT
public:
    BattleController(QObject * parent);
    void registerMyScene(BattleScene * myScene);
    void registerOpponentScene(BattleScene * opponentScene);

    void doTest();

private:
    BattleScene * myScene = nullptr;
    BattleScene * opponentScene = nullptr;
    BattleScene * remoteScene = nullptr;
};

#endif // BATTLECONTROLLER_H
