#ifndef MIDDLECONVIENTTWOBUTTON_H
#define MIDDLECONVIENTTWOBUTTON_H


//引用https://github.com/what951006/KuGouDemo/tree/dev/middleWidget
#include <QObject>
#include <QWidget>
#include <QlineEdit>
#include <myPushButton.h>

#include "baseWidget.h"

class myPushButton;

class middleConvientTwoButton : public baseWidget
{
    Q_OBJECT
public:
  explicit middleConvientTwoButton(QWidget*p=0);

   myPushButton m_btnsearch;
   myPushButton m_btnlocate;


protected:
   void showEvent(QShowEvent *e){baseWidget::showEvent(e);m_timer.start(5000);}

   void enterEvent(QEvent *){m_timer.stop();}

   void leaveEvent(QEvent *){m_timer.start(5000);}


public slots:
   void slot_timerEvent(){hide();}


private:
   QTimer m_timer;
};

class middleListSearch:public baseWidget
{
    Q_OBJECT
public:
    explicit middleListSearch(QWidget*p=0);

    QLineEdit m_lineEdit;
    myPushButton m_btnclose;
private:

public slots:
    void setClear(){m_lineEdit.setText("");}

};



#endif // MIDDLECONVIENTTWOBUTTON_H
