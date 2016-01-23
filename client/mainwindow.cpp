#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "battlescene.h"


#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget * centralWidget = ui->centralWidget;

    BattleScene * myScene = BattleScene::create(centralWidget);

    BattleScene * opponentScene = BattleScene::create(centralWidget);


    QHBoxLayout * battleScenesLayout = new QHBoxLayout(centralWidget);

    centralWidget->setLayout(battleScenesLayout);

    battleScenesLayout->addWidget(myScene);
    battleScenesLayout->addSpacerItem(new QSpacerItem(1,1));
    battleScenesLayout->addWidget(opponentScene);

}

MainWindow::~MainWindow()
{
    delete ui;
}