#ifndef VOLSLIDERWIDGET_H
#define VOLSLIDERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QToolTip>
#include "mySlider.h"
#include"baseWidget.h"

class volSliderWidget:public baseWidget
{
    Q_OBJECT
public:
    volSliderWidget(QWidget*parent=0);
    mySlider *m_slider;
public slots:
    void slot_sliderMove(int va){QToolTip::showText(QCursor::pos(),QString::number(va));}
protected:
    void mousePressEvent(QMouseEvent*){}
    void mouseMoveEvent(QMouseEvent*){}
    void mouseReleaseEvent(QMouseEvent*){}

    bool eventFilter(QObject *, QEvent *);

};

#endif // VOLSLIDERWIDGET_H
