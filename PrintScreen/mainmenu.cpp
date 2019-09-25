#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>
MainMenu::MainMenu(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("截图工具");
    connect(ui->pbtn_PrintScreen,SIGNAL(clicked()),this,SLOT(slot_pbtn_PrintScreen()));
}

MainMenu::~MainMenu()
{
    delete printScreen;
    delete ui;
}


void MainMenu::slot_pbtn_PrintScreen()
{
    this->showMinimized();
    printScreen = new PrintScreen();
    connect(printScreen,SIGNAL(signalCompleteCature(QPixmap)),this,SLOT(slot_DisplyPixmap(QPixmap)));
    printScreen->show();


}


void MainMenu::slot_DisplyPixmap(QPixmap pixmap)
{
    ui->lbl_disp->setPixmap(pixmap);
    showNormal();
}
