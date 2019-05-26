#include "baseWidget.h"
#include <QStyleOption>
#include <QPainter>

#include "AbsFrameLessAutoSize.h"
#include "mainwindow.h"

baseWidget::baseWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background:transparent;}");
    setMouseTracking(true);
}
void baseWidget::paintEvent(QPaintEvent *e)
{
    /*解决setStyleSheet无效--setbackground*/
    Q_UNUSED(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void baseWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void baseWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(MainWindow::GetInstance())
        MainWindow::GetInstance()->mouseMoveEvent(e);
    QWidget::mouseMoveEvent(e);
}

void baseWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
}
