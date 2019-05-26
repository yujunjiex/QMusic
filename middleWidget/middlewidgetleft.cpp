#include "middlewidgetleft.h"
#include"mainwindow.h"

#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>


middleWidgetLeft::middleWidgetLeft(QWidget *parent)
    : baseWidget(parent)
    , m_Swidget0(this)
    , m_Swidget1(this)
    , m_Swidget2(this)
    , m_Swidget3(this)
    , m_animation(this,"m_x")
    , m_Widanimation(this,"geometry")
{

    m_isDrawVerticalLine=true;
    setMinimumWidth(310);
    setMaximumWidth(380);
    setMinimumHeight(570);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);

    initLayout();
    initAnimation();
    m_btn[0]->setStyleSheet("QPushButton{border-image: url(:/middlewidget/images/middlewidget/btn_mask.png);}");
}
void middleWidgetLeft::initAnimation()
{
    m_preindex=-1;
    m_preItem=0;
    m_x=0;
    m_isAnima=false;

    m_animation.setDuration(200);
    m_stackwid.setCurrentIndex(0);
    connect(&m_animation,SIGNAL(finished()),this,SLOT(slot_finished()));


    m_Widanimation.setTargetObject(&m_stackwid);
    m_Widanimation.setDuration(200);
}


void middleWidgetLeft::initLayout()
{
    QVBoxLayout *vlyout=new QVBoxLayout;
    m_stackwid.setFrameShadow(QFrame::Plain);
    m_stackwid.setFrameShape(QFrame::NoFrame);

    m_stackwid.addWidget(&m_Swidget0);
    m_stackwid.addWidget(&m_Swidget1);
    m_stackwid.addWidget(&m_Swidget2);
    m_stackwid.addWidget(&m_Swidget3);

    m_stackwid.setContentsMargins(0,0,0,0);


    m_btn[0]=new stackButton(":/middlewidget/images/middlewidget/btn_music (1).png",":/middlewidget/images/middlewidget/btn_music (2).png",":/middlewidget/images/middlewidget/btn_music (3).png",this);
    m_btn[1]=new stackButton(":/middlewidget/images/middlewidget/btn_cloud (1).png",":/middlewidget/images/middlewidget/btn_cloud (2).png",":/middlewidget/images/middlewidget/btn_cloud (3).png",this);
    m_btn[2]=new stackButton(":/middlewidget/images/middlewidget/btn_download (1).png",":/middlewidget/images/middlewidget/btn_download (2).png",":/middlewidget/images/middlewidget/btn_download (3).png",this);
    m_btn[3]=new stackButton(":/middlewidget/images/middlewidget/btn_phone (1).png",":/middlewidget/images/middlewidget/btn_phone (2).png",":/middlewidget/images/middlewidget/btn_phone (3).png",this);

    m_btn[0]->setFixedHeight(40);
    m_btn[1]->setFixedHeight(40);
    m_btn[2]->setFixedHeight(40);
    m_btn[3]->setFixedHeight(40);

    QHBoxLayout *hlyout=new QHBoxLayout;
    hlyout->addWidget(m_btn[0]);
    hlyout->addWidget(m_btn[1]);
    hlyout->addWidget(m_btn[2]);
    hlyout->addWidget(m_btn[3]);
    hlyout->setContentsMargins(0,0,0,0);
    hlyout->setSpacing(0);

    vlyout->addLayout(hlyout);
    vlyout->addWidget(&m_stackwid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);
    setLayout(vlyout);

    for(int i=0;i<4;i++)
    {
        m_btn[i]->setObjectName(QString::number(i));
        connect(m_btn[i],SIGNAL(pressed()),this,SLOT(slot_btn()));
    }

    connect(&m_stackwid,SIGNAL(currentChanged(int)),this,SLOT(slot_changeButtonSelected(int)));

    m_stackwid.setCurrentIndex(0);//选中第一个stackwidget
    m_btn[0]->setselected(true); //设置
}
void middleWidgetLeft::slot_changeButtonSelected(int index)
{
//    m_isAnima=true;
//    m_animation.setStartValue(m_preindex*m_btn[0]->width());
//    m_animation.setEndValue(index*m_btn[0]->width());
//    m_animation.start();

    for(int i=0;i<4;i++)
    {
        if(i==index)
        {
           m_btn[index]->setselected(true);
           m_btn[index]->setStyleSheet("QPushButton{border-image: url(:/middlewidget/images/middlewidget/btn_mask.png);}");
        }
        else
        {
          m_btn[i]->setselected(false);
          m_btn[i]->setStyleSheet("QPushButton{color:rgb(68,68,68);}"); //重置mask
        }
    }

    if(index>m_preItem)
    {
        m_Widanimation.setTargetObject(&m_stackwid);
        m_Widanimation.setStartValue(QRect(m_stackwid.width(),40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.setEndValue(QRect(0,40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.start();
    }
    if(index<m_preItem)
    {
        m_Widanimation.setTargetObject(&m_stackwid);
        m_Widanimation.setStartValue(QRect(-m_stackwid.width(),40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.setEndValue(QRect(0,40,m_stackwid.width(),m_stackwid.height()));
        m_Widanimation.start();
    }
    m_preItem=index;
}
void middleWidgetLeft::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(230,230,230));
       if(m_isDrawVerticalLine)
         p.drawLine(width()-1,0,width()-1,height());
}
void middleWidgetLeft::slot_btn()
{
    m_preindex=m_stackwid.currentIndex();
    m_stackwid.setCurrentIndex(sender()->objectName().toInt());
}
void middleWidgetLeft::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}
