#ifndef MIDDLEWIDGETS_H
#define MIDDLEWIDGETS_H

#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "middlewidgetleft.h"
#include "middleWidgetRight.h"

class middleWidgetLeft;
class middleWidgetRight;
class MainWindow;
class myPushButton;

class middleWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit middleWidgets(QWidget *parent = 0);
    void initLayout();

    middleWidgetLeft m_leftWid;
    middleWidgetRight m_rightWid;
protected:
    void mousePressEvent(QMouseEvent *){setFocus();}
    void mouseReleaseEvent(QMouseEvent *){}


};

#endif // MIDDLEWIDGETS_H
