#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPixmap>
#include "printscreen.h"

namespace Ui{
    class  MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
private:
    Ui::MainMenu *ui;
    PrintScreen  *printScreen;

private slots:
    void slot_pbtn_PrintScreen();
    void slot_pbtn_save();
    void slot_DisplyPixmap(QPixmap);
};

#endif // MAINMENU_H
