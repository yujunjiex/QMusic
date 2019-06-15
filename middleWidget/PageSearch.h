#ifndef PAGESEARCH_H
#define PAGESEARCH_H

#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "middleWidgetLeft.h"
#include "middleWidgetRight.h"
///查询窗体，放在middleWidgetRight中来控制


class PageSearch : public QWidget
{
    Q_OBJECT
public:
    explicit PageSearch(QWidget *parent = 0);
    void initLayout();

protected:
    //virtual void paintEvent(QPaintEvent *);



};

#endif // PAGESEARCH_H
