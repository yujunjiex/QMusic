#ifndef MIDDLEWIDGETLEFT_H
#define MIDDLEWIDGETLEFT_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QMap>

#include "baseWidget.h"
#include "myPushButton.h"
#include "middleLeftStackWidget0.h"
#include "middleLeftStackWidget1.h"
#include "middleLeftStackWidget2.h"
#include "middleLeftStackWidget3.h"
#include "abstractmiddleleftstackwidget.h"


class middleWidgetLeft : public baseWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_x READ getValue WRITE animation)
public:
    explicit middleWidgetLeft(QWidget *parent = 0);

    QVector<AbstractMiddleLeftStackWidget*> & stackWidgetVector(){return stackVector;}

    void init();
    void initLayout();
    void initAnimation();

    int getValue(){return m_x;}
    void animation(int i){m_x=i;update();}
    void setDrawVerticalLine(bool is=true){m_isDrawVerticalLine=is;}

    static QString getCurrentPlayingStack(){return currentPlayingStack;}
    static void setCurrentPlayingStack(const QString&string);

    static void releaseCrossWid(); //释放其他stack的cell

protected:
    void paintEvent(QPaintEvent *);

    void resizeEvent(QResizeEvent*);

signals:
    void sig_stackChanged();

private slots:
    void slot_btn();
    void slot_changeButtonSelected(int i);//改变选中图片
    void slot_finished(){m_isAnima=false;}
private:

    stackButton *m_btn[4];

    QStackedWidget  m_stackwid;
    middleLeftStackWidget0 m_Swidget0;
    middleLeftStackWidget1 m_Swidget1;
    middleLeftStackWidget2 m_Swidget2;
    middleLeftStackWidgetScrollArea2 *m_widget2; //
    middleLeftStackWidget3 m_Swidget3;

    int m_preindex;
    bool m_isDrawVerticalLine;
    bool m_isAnima;
    int m_x;
    int m_preItem;
    QPropertyAnimation m_animation;
    QPropertyAnimation m_Widanimation;

    static QString currentPlayingStack;

    //创建一个QMap<QString,abstractMiddleLeftStackWidget>
    static QMap<QString,AbstractMiddleLeftStackWidget*> stackMap;
    QVector<AbstractMiddleLeftStackWidget*> stackVector;
};


#endif // MIDDLEWIDGETLEFT_H
