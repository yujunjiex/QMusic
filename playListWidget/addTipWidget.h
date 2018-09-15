#ifndef ADDTIPWIDGET_H
#define ADDTIPWIDGET_H

#include <QWidget>
#include "baseWidget.h"
#include "myPushButton.h"

class addTipWidget:public baseWidget
{
    Q_OBJECT
public:
    addTipWidget(QWidget*parent=0);
    void init();

    myPushButton m_add;

private:
    myPushButton m_labadd;
};



#endif
