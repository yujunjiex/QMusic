#include "addTipWidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>


addTipWidget::addTipWidget(QWidget *parent):baseWidget(parent)
  ,m_add("点击添加本地歌曲",this)
  ,m_labadd(this)
{
    init();
    setFixedSize(310,80);
    connect(&m_labadd,SIGNAL(clicked(bool)),&m_add,SIGNAL(clicked(bool)));
}

void addTipWidget::init()
{
    QHBoxLayout *hlyout=new QHBoxLayout;


   m_labadd.setFixedSize(20,20);

   m_labadd.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/lab_add.png);}");

   m_add.adjustSize();

   m_add.setStyleSheet("QPushButton{color: rgb(58,58,58);text-decoration: underline;}");


   hlyout->addStretch(20);
   hlyout->addWidget(&m_labadd);
   hlyout->addWidget(&m_add);
   hlyout->addStretch(20);
   hlyout->setSpacing(5);
   hlyout->setContentsMargins(0,0,0,0);


   setLayout(hlyout);

}
