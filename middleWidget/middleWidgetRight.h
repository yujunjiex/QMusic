#ifndef MIDDLEWIDGETRIGHT_H
#define MIDDLEWIDGETRIGHT_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>


#include "myPushButton.h"
#include "baseWidget.h"
#include "PageSearch.h"


class middleSearchWidget;
class LyricLabel;
class myPushButton;
class middleWidgets;


class middleWidgetRight:public baseWidget
{
    Q_OBJECT

public:
   explicit middleWidgetRight(QWidget*parent=0);
   void init();
   void setDrawLine(bool draw=true){m_isdrawline=draw;}

//   middleSearchWidget * getSearWidget(){return &m_searchwid;}
   static QColor bgcolor;   //选中后的颜色(蓝)
public slots:
   //void slot_search(const QString&);  //TODO:设置search对应的stack
   void slot_btnClick();    //用于显示每个button对应的widget
   void slot_curStackChange(int);
protected:
    //void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent *);
signals:
    void sig_requestSong(const QString&);

private:
   bool m_isdrawline;

   QStackedWidget m_stackWid;   //
//   PageSearch m_searchwid;
   myPushButton m_btnArray[3];  //
   baseWidget m_wid;    //

/*   WebWidget *m_web0;
    WebWidget *m_web1;
    WebWidget *m_web2;
    WebWidget *m_web3;
    WebWidget *m_web4;*/
};

#endif // MIDDLEWIDGETRIGHT_H
