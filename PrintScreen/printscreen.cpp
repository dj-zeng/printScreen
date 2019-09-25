#include "printscreen.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>

#include <QPointF>

PrintScreen::PrintScreen(QWidget *parent):
    QWidget (parent),
    m_isMousePress(false)
{
    this->setMouseTracking(true);
//    setAttribute(Qt::WA_TranslucentBackground,true);   //背景是否透明
    this->setWindowFlag(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
    m_cursor.setShape(Qt::CrossCursor);
    this->setCursor(m_cursor);
    loadBackgroundPixmp();
}

PrintScreen::~PrintScreen()
{
}

void PrintScreen::mouseMoveEvent(QMouseEvent* event)
{
    if(m_isMousePress)
    {
        m_endPoint = event->pos();
        update();
    }
}

void PrintScreen::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_isMousePress = true;
        m_beginPoint = event->pos();
    }
}

void PrintScreen::mouseReleaseEvent(QMouseEvent *event)
{
    m_endPoint = event->pos();
    m_isMousePress = false;
    emit signalCompleteCature(m_printPixmap);
    close();
}
void PrintScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        emit signalCompleteCature(m_printPixmap);
        close();
    }
    return QWidget::keyPressEvent(event);
}


void PrintScreen::loadBackgroundPixmp()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    m_loadPixmap = screen->grabWindow(0);
    m_screenWidth = m_loadPixmap.width();
    m_screenHight = m_loadPixmap.height();

}


void PrintScreen::paintEvent(QPaintEvent *event)
{
    //setAttribute(Qt::WA_TranslucentBackground,false);   //背景是否透明
    m_painter.begin(this);
    QColor shadowColor = QColor(63,63,63,140);
    m_painter.setPen(Qt::red);
    m_painter.drawPixmap(0,0,m_loadPixmap);
    m_painter.fillRect(m_loadPixmap.rect(),shadowColor);

    if(m_isMousePress)
    {
        QRect selectedRect = getRect(&m_beginPoint,&m_endPoint);
        m_printPixmap = m_loadPixmap.copy(selectedRect);
        m_painter.drawPixmap(selectedRect.topLeft(),m_printPixmap);
        m_painter.drawRect(selectedRect);
        m_painter.drawText(selectedRect.topLeft(),QString::number(selectedRect.x()));
    }
    m_painter.end();
    return QWidget::paintEvent(event);

}

QRect PrintScreen::getRect(QPoint *begin,QPoint *end)
{
    int x,y,width,height;

    width = qAbs(begin->x()-end->x());
    height = qAbs(begin->y()-end->y());

    x = begin->x() < end->x()? begin->x():end->x();
    y = begin->y() < end->y()? begin->y():end->y();

    QRect selectedRect = QRect(x,y,width,height);

    if(selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if(selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}
