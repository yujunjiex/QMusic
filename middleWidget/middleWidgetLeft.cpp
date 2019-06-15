#include "middleWidgetLeft.h"
#include"mainwindow.h"

#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>


QString middleWidgetLeft::currentPlayingStack = "";
QMap<QString,AbstractMiddleLeftStackWidget*> middleWidgetLeft::stackMap;

middleWidgetLeft::middleWidgetLeft(QWidget *parent)
    : baseWidget(parent)
    , m_Swidget0(this)
    , m_Swidget1(this)
    , m_Swidget2(this)
    , m_widget2(nullptr)
    , m_Swidget3(this)
    , m_animation(this,"m_x")
    , m_Widanimation(this,"geometry")
{

    m_isDrawVerticalLine=true;
    setMinimumWidth(310);
    setMaximumWidth(380);
    setMinimumHeight(570);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);

    init();
    initLayout();
    initAnimation();
    m_btn[0]->setStyleSheet("QPushButton{border-image: url(:/middlewidget/images/middlewidget/btn_mask.png);}");
}

void middleWidgetLeft::init()
{
    m_widget2 = m_Swidget2.getStackWid();

    //init map
    stackMap.insert("localMusic",&m_Swidget0);
//    stackMap.insert("neteaseMusic",&m_Swidget1);
    stackMap.insert("qqMusic",m_widget2);
    stackMap.insert("loveMusic",&m_Swidget3);

    //init vector
    stackVector.append(&m_Swidget0);
//    stackVector.append(&m_Swidget1);
    stackVector.append(m_widget2);
    stackVector.append(&m_Swidget3);

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

void middleWidgetLeft::setCurrentPlayingStack(const QString &string)
{
    if(string!=currentPlayingStack)
    {
//        emit sig_stackChanged();
        currentPlayingStack=string;
        releaseCrossWid();
    }
}

void middleWidgetLeft::releaseCrossWid()
{
    //根据QMap和currentPlayingStack去调用其他stack的releaseAllCrossWid
    QMapIterator<QString, AbstractMiddleLeftStackWidget*> i(stackMap);
    while (i.hasNext()) {
        i.next();

        if(i.key()!=currentPlayingStack)
        {
//            qDebug() << i.key() <<"被release了"<< endl;
            i.value()->releaseAllCrossWid();
        }
    }

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


    m_btn[0]=new stackButton(":/middlewidget/images/middlewidget/localmusic_gray.png",":/middlewidget/images/middlewidget/localmusic.png",":/middlewidget/images/middlewidget/localmusic.png",this);
    m_btn[1]=new stackButton(":/middlewidget/images/middlewidget/netease_gray.png",":/middlewidget/images/middlewidget/netease.png",":/middlewidget/images/middlewidget/netease.png",this);
    m_btn[2]=new stackButton(":/middlewidget/images/middlewidget/QQmusic_gray.png",":/middlewidget/images/middlewidget/QQmusic.png",":/middlewidget/images/middlewidget/QQmusic.png",this);
    m_btn[3]=new stackButton(":/middlewidget/images/middlewidget/lovemusic_gray.png",":/middlewidget/images/middlewidget/lovemusic.png",":/middlewidget/images/middlewidget/lovemusic.png",this);

    m_btn[0]->setFixedHeight(40);
    m_btn[1]->setFixedHeight(40);
    m_btn[2]->setFixedHeight(40);
    m_btn[3]->setFixedHeight(40);

    m_btn[0]->setToolTip("本地音乐");
    m_btn[1]->setToolTip("网易云音乐");
    m_btn[2]->setToolTip("QQ音乐");
    m_btn[3]->setToolTip("我的最爱");

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
    currentPlayingStack = "localmusic";
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
