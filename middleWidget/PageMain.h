#ifndef PAGEMAIN_H
#define PAGEMAIN_H

#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "middleWidgetLeft.h"
#include "middleWidgetRight.h"
///包含左右两个主窗体

class PageMain : public baseWidget
{
    Q_OBJECT
public:
    explicit PageMain(QWidget *parent = 0);
    void initLayout();
    //TODO
    void raiseSearchWidget();

    middleWidgetLeft *m_leftWid;
    middleWidgetRight *m_rightWid;
protected:
    void mousePressEvent(QMouseEvent *){setFocus();}
    void mouseReleaseEvent(QMouseEvent *){}


};

#endif // PAGEMAIN_H
