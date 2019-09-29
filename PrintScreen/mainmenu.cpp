#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
MainMenu::MainMenu(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("截图工具");
    ui->pbtn_save->hide();
    connect(ui->pbtn_PrintScreen,SIGNAL(clicked()),this,SLOT(slot_pbtn_PrintScreen()));
    connect(ui->pbtn_save,SIGNAL(clicked()),this,SLOT(slot_pbtn_save()));
}

MainMenu::~MainMenu()
{
    delete printScreen;
    delete ui;
}


void MainMenu::slot_pbtn_PrintScreen()
{
    this->showMinimized();
    this->hide();
    printScreen = new PrintScreen();
    connect(printScreen,SIGNAL(signalCompleteCature(QPixmap)),this,SLOT(slot_DisplyPixmap(QPixmap)));
    printScreen->show();

}


void MainMenu::slot_DisplyPixmap(QPixmap pixmap)
{
    ui->pbtn_PrintScreen->hide();
    ui->pbtn_save->show();
    ui->lbl_disp->setPixmap(pixmap);
    this->show();
    showNormal();
}

void MainMenu::slot_pbtn_save()
{
    QPixmap  const *pixmap = new QPixmap();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),  "/home",
                                                       QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    QString fileName="/"+ QDateTime::currentDateTime().toString("yyyy-MM-ddHH-mm-ss")  + ".png";
    pixmap = ui->lbl_disp->pixmap();
    qDebug()<<dir+fileName;
    pixmap->save( dir+fileName,"png");

    this->close();
}
