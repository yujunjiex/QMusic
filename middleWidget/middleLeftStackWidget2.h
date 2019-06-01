#ifndef MIDDLELEFTSTACKWIDGET2_H
#define MIDDLELEFTSTACKWIDGET2_H

#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "downloadstackedwidget.h"

///QQ音乐
class middleLeftStackWidget2:public baseWidget
{
    Q_OBJECT
public:
    explicit middleLeftStackWidget2(QWidget *parent);
    void init();

    //TODO:下载进度条，下载个数角标，动画的平滑滚动

private:
    downloadStackedWidget m_wid;
};


#endif  //for download
