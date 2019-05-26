#include "bottomWidgets.h"
#include <QLayout>
#include <QTime>
#include <mainwindow.h>


bottomWidgets::bottomWidgets(QWidget *parent): baseWidget(parent)
  , m_btnprevious(this)
  , m_btnPlay(this)
  , m_btnnext(this) 
  , m_btnvol(":/bottomwidget/images/bottomwidget/btn_vol (1).png",":/bottomwidget/images/bottomwidget/btn_vol (2).png",":/bottomwidget/images/bottomwidget/btn_vol (3).png",this)
  , m_btnplaylist(this)
  , m_btnfavorite(this)
  , m_btnplaymode(this)
  , m_btndownload(":/bottomwidget/images/bottomwidget/btn_download (1).png",":/bottomwidget/images/bottomwidget/btn_download (2).png",":/bottomwidget/images/bottomwidget/btn_download (3).png",this)
  , m_btnpicture(this)
  , m_mainslider(Qt::Horizontal,this)
  , m_labposition("00:00/00:00",this)
  , m_labnowPlayname("正在播放:",this)
{
    init();
    initConnect();

    /*测试*/
    setPicture(":/playingwidget/images/playingwidget/AlbumCover1.jpg");
}

void bottomWidgets::init()
{
    setStyleSheet("bottomWidgets{background:transparent;}");
    setMinimumSize(1250,90);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QHBoxLayout *mainlyout=new QHBoxLayout;
////////////////////////////////////////////////////////////////////firstlayout
    QHBoxLayout *layout=new QHBoxLayout;


    m_btnnext.setFixedSize(55,55);
    m_btnprevious.setFixedSize(55,55);
    m_btnPlay.setFixedSize(55,55);

    m_btnnext.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_next (1).png);}"
                             "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_next (2).png);}"
                             "QPushButton::pressed{border-image:url(:/bottomwidget/images/bottomwidget/btn_next (3).png);}");
    m_btnprevious.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_previous (1).png);}"
                                 "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_previous (2).png);}"
                                 "QPushButton::pressed{border-image:url(:/bottomwidget/images/bottomwidget/btn_previous (3).png);}");
    m_btnPlay.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_pause (1).png);}"
                             "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_pause (2).png);}"
                             "QPushButton::pressed{border-image:url(:/bottomwidget/images/bottomwidget/btn_pasue (3).png);}");

    layout->addWidget(&m_btnprevious);
    layout->addWidget(&m_btnPlay);
    layout->addWidget(&m_btnnext);
    layout->setSpacing(15);
    layout->setContentsMargins(0,0,0,0);

    m_btnpicture.setFixedSize(90,90);
    /////////////////////////////////////////////////////////////////////////secondlayout
    QHBoxLayout *layout2=new QHBoxLayout;

    m_mainslider.installEventFilter(this);
    m_mainslider.setRange(0,1000);
    m_mainslider.setMinimumSize(500,18);
    m_mainslider.setMaximumHeight(18);
    m_mainslider.setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:3px;}"
                               "QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
                               "QSlider::add-page:horizontal{background:rgb(200,200,209);}"
                               "QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");

    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(16);
    font.setBold(true);

    QHBoxLayout *layout2_1=new QHBoxLayout;

    m_labnowPlayname.setMinimumWidth(250);
    m_labnowPlayname.setFixedHeight(40);
    m_labnowPlayname.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_labnowPlayname.setFont(font);

    m_labposition.setAlignment(Qt::AlignRight|Qt::AlignBottom);
    m_labposition.setFixedSize(110,20);
    //m_labposition.setContentsMargins(0,0,5,0);//for italic's right not show
    m_labposition.setStyleSheet(QLatin1String("font: 25 italic 9.8pt \"Comic Sans MS\";\n"
                                              "color: rgb(255, 255, 255);"));

    layout2_1->addWidget(&m_labnowPlayname);
    layout2_1->addWidget(&m_labposition);

    QVBoxLayout *vlayout=new QVBoxLayout;
    vlayout->addLayout(layout2_1);
    vlayout->addWidget(&m_mainslider);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,0,10);
    layout2->addLayout(vlayout);

    //////////////////////////////////////////////////////////////////////////////////////thirdlayout
    QHBoxLayout *layout3=new QHBoxLayout;



     m_btnplaylist.setFixedSize(60,20);
     m_btnvol.setFixedSize(20,20);
     m_btnplaymode.setFixedSize(20,20);
     m_btndownload.setFixedSize(20,20);
     m_btnfavorite.setFixedSize(20,20);


     m_btnplaylist.setStyleSheet("QPushButton{border:NULL;background-image:url(:/bottomwidget/images/bottomwidget/btn_miniplaylist (1).png);}"
                            "QPushButton::hover{background-image:url(:/bottomwidget/images/bottomwidget/btn_miniplaylist (2).png);}"
                            "QPushButton::pressed{background-image:url(:/bottomwidget/images/bottomwidget/btn_miniplaylist (3).png);}");

     m_btnplaymode.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_listcircle (1).png);}"
                            "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_listcircle (2).png);}"
                            );

     m_btnfavorite.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_favorite_no (1).png);}"
                            "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_favorite_no (2).png);}"
                            "QPushButton::pressed{border-image:url(:/bottomwidget/images/bottomwidget/btn_favorite_no (3).png);}");


    layout3->addWidget(&m_btnfavorite);
    layout3->addWidget(&m_btndownload);
    layout3->addWidget(&m_btnplaymode);
    layout3->addWidget(&m_btnvol);
    layout3->addWidget(&m_btnplaylist);

    layout3->setSpacing(18);
    layout3->setContentsMargins(0,0,0,0);
    ////////////////////////////////////////
    mainlyout->addLayout(layout);
    mainlyout->addWidget(&m_btnpicture);
    mainlyout->addLayout(layout2);
    mainlyout->addLayout(layout3);
    mainlyout->setSpacing(30);
    mainlyout->setContentsMargins(12,0,0,0);
    setLayout(mainlyout);
}

void bottomWidgets::initConnect()
{
    connect(&m_mainslider,SIGNAL(sliderMoved(int)),this,SLOT(updateText(int)));
//    connect(&m_btnpicture, SIGNAL(clicked(bool)),this,[=](){emit sig_showPlayingPanel(bool);});
    connect(&m_btnpicture,&myPushButton::clicked,[=](){emit sig_showPlayingPanel();});
}

void bottomWidgets::setPauseStyle()
{
    m_btnPlay.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_pause (1).png);}"
                           "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_pause (2).png);}"
                           "QPushButton::pressed{border-image:url(:/bottomwidget/images/bottomwidget/btn_pause (3).png);}");
    //m_labnowPlayname.setText(m_labnowPlayname.Text().remove("正在播放: "));
}

void bottomWidgets::setPlayStyle()
{
    m_btnPlay.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_play (1).png);}"
                             "QPushButton::hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_play (2).png);}"
                             "QPushButton::pressed{border-image:url(:/bottomwidget/images/bottomwidget/btn_play (3).png);}");
    //m_labnowPlayname.setText(m_labnowPlayname.Text().remove("正在播放: "));
}

void bottomWidgets::setBufferStyle()
{
    m_labnowPlayname.setText(QString("缓冲中>> ")+m_labnowPlayname.Text());
}

void bottomWidgets::setRandomStyle()
{
    m_btnplaymode.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_listrandom (1).png);}"
                                 "QPushButton:hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_listrandom (2).png);}");
}

void bottomWidgets::setInOrderStyle()
{
    m_btnplaymode.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_listcircle (1).png);}"
                                 "QPushButton:hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_listcircle (2).png);}");
}

void bottomWidgets::setOneCycleStyle()
{
    m_btnplaymode.setStyleSheet("QPushButton{border-image:url(:/bottomwidget/images/bottomwidget/btn_listscircle_single (1).png);}"
                                 "QPushButton:hover{border-image:url(:/bottomwidget/images/bottomwidget/btn_listscircle_single (2).png);}");
}

void bottomWidgets::setPicture(const QString &url)
{
    m_btnpicture.setIcon(QIcon(url));
    m_btnpicture.setIconSize(QSize(90,90));
}

void bottomWidgets::updateText(int position)
{
    m_mainslider.setValue(position);

    qint64 time = MainWindow::GetInstance()->player()->duration();
    m_labposition.setText(Time(position)+"/"+Time(time));
}

void bottomWidgets::updatePosition(qint64 position)
{
    m_mainslider.setValue(position);

    qint64 time = MainWindow::GetInstance()->player()->duration();
    m_labposition.setText(Time(position)+"/"+Time(time));
}

void bottomWidgets::updateDuration(qint64 duration)
{
    m_mainslider.setRange(0, duration);
    m_mainslider.setEnabled(duration > 0);
    m_mainslider.setPageStep(duration / 10);
}

QString bottomWidgets::Time(qint64 time)
{

    qint64 seconds=time/1000;
    const qint64 minutes=seconds/60;
    seconds-=minutes*60;
    return QStringLiteral("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));

}
