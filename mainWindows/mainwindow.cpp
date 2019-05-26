#include "mainwindow.h"
#include <QLayout>
#include <QApplication>
#include <QDir>
#include <QPainter>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QDebug>

MainWindow *MainWindow::s_pMainWnd=NULL;

MainWindow *MainWindow::InitInstance()
{
    if(!s_pMainWnd)
        s_pMainWnd=new MainWindow;
    return s_pMainWnd;
}

MainWindow::MainWindow(QWidget *parent)
    : baseWindow(parent)
    ,m_player(this)
    ,m_topwid(this)
    //,m_middwid(this)
    ,m_sertipswid(this)
    ,m_volwid(this)
    ,m_bottomwid(this)
    ,m_middlewid(this)
    ,m_pLefStack0(NULL)
{
    m_mainwid.setStyleSheet("QLabel{color:white;}"
                            "QWidget{background:transparent;}"
                            );
//    m_mainwid.setSkin("C:/Users/xh/Desktop/KuGouDemo/image/skin/默认.jpg");
    m_middlewid.onSetMusicLyricPath("F:/CloudMusic/说散就散 - 袁娅维.lrc");
    m_mainwid.setSkin("E:/QtProject/QMusic/images/background/壁纸02.jpg");

    m_pLefStack0=m_middlewid.GetStackWid0();
    init();
    initConn();
    initMusic();
    UpdateListConn();
}


void MainWindow::init()
{

    QVBoxLayout *vlyout=new QVBoxLayout;
    vlyout->addWidget(&m_topwid);
    vlyout->addWidget(&m_middlewid);
    vlyout->addWidget(&m_bottomwid);
    vlyout->setSpacing(0);
    vlyout->setContentsMargins(0,0,0,0);
    m_mainwid.setLayout(vlyout);

}

void MainWindow::initConn()
{
    /*init connect*/
    m_sertipswid.hide();
    m_topwid.m_lineEdit.installEventFilter(this);
    connect(&m_sertipswid,SIGNAL(itemClicked(QListWidgetItem*)),&m_topwid,SLOT(slot_serTipsClick(QListWidgetItem*)));
    connect(&m_topwid.m_btnmini,SIGNAL(clicked(bool)),SLOT(showMinimized()));
    connect(&m_topwid.m_btnexit,SIGNAL(clicked(bool)),SLOT(close()));
    connect(&m_topwid.m_lineEdit,SIGNAL(textChanged(QString)),&m_sertipswid,SLOT(slot_textchanged(QString)));

    connect(m_volwid.m_slider,SIGNAL(valueChanged(int)),&m_player,SLOT(setVolume(int)));
//    connect(&m_traymenu.m_volWid.m_slider_vol,SIGNAL(valueChanged(int)),m_volwid.m_slider,SLOT(setValue(int)));
//    connect(&m_traymenu.m_volWid.m_slider_vol,SIGNAL(sliderMoved(int)),m_volwid.m_slider,SLOT(setValue(int)));
//    connect(m_volwid.m_slider,SIGNAL(valueChanged(int)),&m_traymenu.m_volWid.m_slider_vol,SLOT(setValue(int)));


    //connect(m_volwid.m_slider,SIGNAL(valueChanged(int)),&m_bottomwid.m_btnvol,SLOT(setButtonPixmap(int)));
}

void MainWindow::initMusic()
{
    m_bottomwid.m_btnvol.setPartnerSlider(m_volwid.m_slider);
    m_volwid.hide();
    m_bottomwid.m_btnvol.installEventFilter(this);
    m_volwid.installEventFilter(this);
    connect(m_volwid.m_slider,SIGNAL(valueChanged(int)),&m_bottomwid.m_btnvol,SLOT(setButtonPixmap(int)));

    connect(&m_bottomwid.m_btnvol,SIGNAL(setMute(int)),m_volwid.m_slider,SLOT(setValue(int)));
    connect(&m_bottomwid.m_btnvol,SIGNAL(sig_hideVolWidget()),&m_volwid,SLOT(hide()));
    m_volwid.m_slider->setValue(80);

    connect(&m_bottomwid.m_btnplaymode,SIGNAL(clicked(bool)),this,SLOT(slot_setPlayMode()));

    connect(&m_bottomwid.m_btnPlay,SIGNAL(clicked(bool)),this,SLOT(slot_setPlayerPlayOrPause()));
    connect(&m_bottomwid.m_btnnext,SIGNAL(clicked(bool)),m_pLefStack0,SLOT(slot_btnnextSong()));
    connect(&m_bottomwid.m_btnprevious,SIGNAL(clicked(bool)),m_pLefStack0,SLOT(slot_btnpreSong()));

    connect(&m_bottomwid,SIGNAL(sig_showPlayingPanel()),this,SLOT(slot_showPlayingPanel()));

    connect(&m_player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(slot_playerStatusChanged(QMediaPlayer::State)));
    connect(&m_player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(slot_mediaStatusChanged(QMediaPlayer::MediaStatus)));

    connect(&m_player,SIGNAL(metaDataChanged()),this,SLOT(slot_updateInfo()));
    connect(&m_player,SIGNAL(positionChanged(qint64)),&m_bottomwid,SLOT(updatePosition(qint64)));//播放的位置改变->更新进度条播放位置
    connect(&m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条
    connect(&m_bottomwid.m_mainslider,SIGNAL(sliderPressed()),this,SLOT(slot_apdaterSlider()));//拖动进度条时->断开部分连接适应拖动操作
    connect(&m_bottomwid.m_mainslider,SIGNAL(sliderReleased()),this,SLOT(slot_setPosition()));//进度条移动->更新音乐的播放位置

}

void MainWindow::UpdateListConn()
{
    QVector<playListWidget*> &vec=m_pLefStack0->playListWidgetVector();
    for(int i=0;i<vec.count();i++)
    {
        disconnect(&vec.at(i)->m_Btntable,SIGNAL(sig_addPlayList()),m_pLefStack0,SLOT(slot_addPlayListWithRename()));//添加播放列表
        connect(&vec.at(i)->m_Btntable,SIGNAL(sig_addPlayList()),m_pLefStack0,SLOT(slot_addPlayListWithRename()));

        disconnect(&vec.at(i)->m_Btntable,SIGNAL(sig_delPlayList()),m_pLefStack0,SLOT(slot_removePlayList()));//移除播放列表
        connect(&vec.at(i)->m_Btntable,SIGNAL(sig_delPlayList()),m_pLefStack0,SLOT(slot_removePlayList()));

        disconnect(&vec.at(i)->m_table,SIGNAL(sig_play(int)),m_pLefStack0,SLOT(slot_play(int)));//播放triggered
        connect(&vec.at(i)->m_table,SIGNAL(sig_play(int)),m_pLefStack0,SLOT(slot_play(int)));

    }
}

void MainWindow::setOriginalStatus()
{
   // m_bottomwid.slot_setLoveState(false);

    //m_traymenu.setCurrentSongName("暂无歌曲");
    m_bottomwid.setSongName("");
    m_bottomwid.m_mainslider.setValue(0);
}

int MainWindow::curVol()
{
    return  m_volwid.m_slider->value();
}

void MainWindow::setCurVol(int value)
{
    m_volwid.m_slider->setValue(value);
    m_player.setVolume(value);
}

void MainWindow::slot_setPlayerPlayOrPause()
{
    playListWidget *finalwid=playListWidget::getCurrentList();

    if(!finalwid)
        return;
    if(m_player.state()==QMediaPlayer::PlayingState)
    {
        m_player.pause();
    }
    else if(m_player.state()==QMediaPlayer::PausedState||m_player.state()==QMediaPlayer::StoppedState)
    {
        m_player.play();
    }
}

void MainWindow::slot_playerStatusChanged(QMediaPlayer::State status)
{
    if(status==QMediaPlayer::PlayingState)
    {
        m_bottomwid.setPlayStyle();
        //m_traymenu.setPlayStyle();
    }
    else
    {
        m_bottomwid.setPauseStyle();
        //m_traymenu.setPauseStyle();
    }
}

void MainWindow::slot_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        m_pLefStack0->slot_endOfMedia();

    }
}

void MainWindow::slot_updateInfo()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
    {
        m_bottomwid.setSongName("");
         return;
    }

    QString songname=finalwid->currentMusicName();
    m_bottomwid.setSongName(songname);
    //m_traymenu.setCurrentSongName(songname);
}

void MainWindow::slot_setPlayMode()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
        return;

    //qDebug()<<"playmode="<<m_player.playlist()->playbackMode();

    if(m_player.playlist()->playbackMode()==QMediaPlaylist::Loop ||m_player.playlist()->playbackMode()==QMediaPlaylist::Sequential)
    {
        m_bottomwid.setRandomStyle();
        updatePlayMode(QMediaPlaylist::Random);
    }
    else if(m_player.playlist()->playbackMode()==QMediaPlaylist::Random)
    {
        m_bottomwid.setOneCycleStyle();
        updatePlayMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(m_player.playlist()->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        m_bottomwid.setInOrderStyle();
        updatePlayMode(QMediaPlaylist::Loop);
    }

}

void MainWindow::slot_setPosition()
{
    m_player.setPosition(m_bottomwid.m_mainslider.value());
    connect(&m_player,SIGNAL(positionChanged(qint64)),&m_bottomwid,SLOT(updatePosition(qint64)));//播放的位置改变->更新进度条播放位置
    connect(&m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条
}

void MainWindow::slot_apdaterSlider()
{
    disconnect(&m_player,SIGNAL(positionChanged(qint64)),&m_bottomwid,SLOT(updatePosition(qint64)));//播放的位置改变->更新进度条播放位置
    disconnect(&m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条
}

void MainWindow::updatePlayMode(QMediaPlaylist::PlaybackMode mode)
{
        foreach(playListWidget *f,m_pLefStack0->playListWidgetVector())//for midleft0
        {
                f->setPlayMode(mode);
        }

        /*TODO:for other leftWidget*/

}

void MainWindow::slot_showPlayingPanel()
{
    m_middlewid.switchPage(0,1);
}

//void MainWindow::slot_setPosition()
//{

//}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o==&m_topwid.m_lineEdit)
    {
        if(e->type()==QEvent::FocusOut)
        {
            m_sertipswid.hide();
        }
        if(e->type()==QEvent::FocusIn)
        {
            m_sertipswid.show();
            m_sertipswid.setGeometry(m_topwid.m_lineEdit.x()+4,m_topwid.m_lineEdit.height()+m_topwid.m_lineEdit.y()+6,m_topwid.m_lineEdit.width(),160);
            //qDebug()<<m_topwid.m_lineEdit.x()<<" "<<m_topwid.m_lineEdit.height()<<" "<<m_topwid.m_lineEdit.y()<<" "<<m_topwid.m_lineEdit.width();

        }
    }
    if(o==&m_volwid)//music volumn widget
    {
        if(e->type()==QEvent::Enter)
        {
           m_bottomwid.m_btnvol.stopTimer();
        }
        if(e->type()==QEvent::Leave)
        {
            m_bottomwid.m_btnvol.startTimer(500);
        }
    }
    if(o==&m_bottomwid.m_btnvol)//music volumn button
    {
        if(e->type()==QEvent::Enter)
        {
            m_volwid.setGeometry(m_bottomwid.m_btnvol.pos().x(),
                                  m_topwid.height()+m_middlewid.height()-m_volwid.height()+m_bottomwid.m_btnvol.pos().y(),
                                  30,
                                  310);
            m_volwid.show();
            m_volwid.raise();
        }
    }
    return QObject::eventFilter(o,e);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    if(!isMaximized())
    {
        showMaximized();
        setGeometry(-4,-4,width()+8,height()+8);//最大显示
    }
    else
        showNormal();
}



