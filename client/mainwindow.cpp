#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "battlescene.h"
#include "battlecontroller.h"

#include <QHBoxLayout>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget * centralWidget = ui->centralWidget;

    BattleScene * myScene = new BattleScene(centralWidget);
    myScene->setIsMine(true);

    BattleScene * opponentScene = new BattleScene(centralWidget);

    QHBoxLayout * battleScenesLayout = new QHBoxLayout(centralWidget);

    centralWidget->setLayout(battleScenesLayout);

    battleScenesLayout->addWidget(myScene);
    battleScenesLayout->addSpacerItem(new QSpacerItem(1,1));
    battleScenesLayout->addWidget(opponentScene);


    BattleController * battleController = new BattleController(this);
    battleController->registerMyScene(myScene);
    battleController->registerOpponentScene(opponentScene);
    battleController->doTest();

}

MainWindow::~MainWindow()
{
    delete ui;
}
