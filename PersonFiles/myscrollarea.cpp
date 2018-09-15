#include "myscrollarea.h"
#include <QScrollBar>

myScrollArea::myScrollArea(QWidget *parent):QScrollArea(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setFrameShadow(QFrame::Plain);//设置平的样式
    setFrameShape(QFrame::NoFrame);//设置无边样式

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width:10px; padding-right: 2px;}"
                                      "QScrollBar::handle{background:rgb(180,180,180,150);border-radius:4px;}"
                                      "QScrollBar::handle:hover{background: rgb(150,150,150,150);}"
                                      "QScrollBar::add-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}"
                                      "QScrollBar::sub-line:vertical{border:1px rgb(230,230,230,150);height: 1px;}"
                                      "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:transparent;}");

}
