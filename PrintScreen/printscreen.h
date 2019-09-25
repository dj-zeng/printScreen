#ifndef PRINTSCREEN_H
#define PRINTSCREEN_H

#include <QWidget>
#include <QMouseEvent>
#include <QScreen>
#include <QKeyEvent>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QCursor>

class PrintScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PrintScreen(QWidget *parent = nullptr);
    ~PrintScreen();
    void loadBackgroundPixmp();
    QRect getRect(QPoint*,QPoint*);
private:
    QCursor m_cursor;
    QPixmap m_loadPixmap,m_printPixmap;
    int m_screenWidth,m_screenHight;
    QPainter m_painter;
    bool m_isMousePress;
    QPoint m_beginPoint,m_endPoint;
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void paintEvent(QPaintEvent*);

signals:
    void signalCompleteCature(QPixmap);
};

#endif // PRINTSCREEN_H
