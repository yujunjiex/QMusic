#include "middleWidgetRight.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <middlewidgetleft.h>

#include "myPushButton.h"
#include "mainwindow.h"
#include "middleWidgets.h"

QColor middleWidgetRight::bgcolor= QColor(230,230,230);//初始化

middleWidgetRight::middleWidgetRight(QWidget*parent)
    :baseWidget(parent)
    ,m_wid(this)
{
    m_isdrawline=true;
    init();
    emit m_btnArray[0].click();
    m_btnArray[0].setStyleSheet("QPushButton{border-image: url(:/middlewidget/images/middlewidget/btn_mask.png); color:rgb(40,143,231);font-size:17px;font-family:黑体;}");
}
void middleWidgetRight::init()
{
    setMinimumWidth(940);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QHBoxLayout *hlyout=new QHBoxLayout;
    QVBoxLayout *vlyout=new QVBoxLayout;


    m_stackWid.addWidget(new baseWidget(this));
    m_stackWid.addWidget(new baseWidget(this));
    m_stackWid.addWidget(new baseWidget(this));



    m_btnArray[0].setText("歌单");
    m_btnArray[1].setText("歌手");
    m_btnArray[2].setText("排行");


    m_btnArray[0].setFixedSize(75,50);
    m_btnArray[1].setFixedSize(75,50);
    m_btnArray[2].setFixedSize(75,50);


    m_btnArray[0].setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                         "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[1].setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");
    m_btnArray[2].setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                          "QPushButton:hover{color:rgb(40,143,231);}");

    hlyout->addStretch(60);
    hlyout->addWidget(&m_btnArray[0],0,Qt::AlignHCenter);
    hlyout->addWidget(&m_btnArray[1],0,Qt::AlignHCenter);
    hlyout->addWidget(&m_btnArray[2],0,Qt::AlignHCenter);

    hlyout->addStretch(60);
    hlyout->setSpacing(25);
    hlyout->setContentsMargins(0,0,0,0);
    for(int i=0;i<3;i++)
    {
       m_btnArray[i].setObjectName(QString::number(i));
       connect(&m_btnArray[i],SIGNAL(clicked()),this,SLOT(slot_btnClick()));
    }


    m_wid.setLayout(hlyout);
    vlyout->addWidget(&m_wid);
    vlyout->addWidget(&m_stackWid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);
    setLayout(vlyout);
    connect(&m_stackWid,SIGNAL(currentChanged(int)),this,SLOT(slot_curStackChange(int)));
}

void middleWidgetRight::slot_curStackChange(int index)
{
    for(int i=0;i<3;i++)
    {
        if(i==index)
            m_btnArray[i].setStyleSheet("QPushButton{border-image: url(:/middlewidget/images/middlewidget/btn_mask.png); color:rgb(40,143,231);font-size:17px;font-family:黑体;}");
        else
            m_btnArray[i].setStyleSheet("QPushButton{color:rgb(68,68,68);font-size:17px;font-family:黑体;}"
                                           "QPushButton:hover{color:rgb(40,143,231);}");
    }

}


void middleWidgetRight::slot_btnClick()
{
    int index=sender()->objectName().toInt();
    m_stackWid.setCurrentIndex(index);
}
void middleWidgetRight::paintEvent(QPaintEvent *e)
{
    baseWidget::paintEvent(e);
    if(m_isdrawline)
    {
        QPainter p(this);
        p.setPen(bgcolor);
        p.drawLine(0,50,width(),50);
    }
}
