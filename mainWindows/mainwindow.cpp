#include "mainwindow.h"
#include "abstractmiddleleftstackwidget.h"
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
    ,m_player(nullptr)
    ,m_topwid(this)
    //,m_middwid(this)
    ,m_sertipswid(this)
    ,m_volwid(this)
    ,m_bottomwid(this)
    ,m_middlewid(this)
    ,m_leftWidget(nullptr)
    ,playcontrol(this)
{
    m_mainwid.setStyleSheet("QLabel{color:white;}"
                            "QWidget{background:transparent;}"
                            );

    //test
    m_mainwid.setSkin("C:/Users/xh/Desktop/KuGouDemo/image/skin/默认.jpg");
    m_middlewid.onSetMusicLyricPath("F:/CloudMusic/可乐-赵紫骅.lrc");
//    m_mainwid.setSkin("E:/QtProject/QMusic/images/background/壁纸02.jpg");


    m_leftWidget=m_middlewid.GetLeftWid();
    m_player = new MusicPlayer(this);
    m_player->setNotifyInterval(33);

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

    connect(m_volwid.m_slider,SIGNAL(valueChanged(int)),m_player,SLOT(setVolume(int)));
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

//    AbstractMiddleLeftStackWidget
    connect(&m_bottomwid.m_btnnext,SIGNAL(clicked(bool)),&playcontrol,SLOT(slot_btnnextSong()));
    connect(&m_bottomwid.m_btnprevious,SIGNAL(clicked(bool)),&playcontrol,SLOT(slot_btnpreSong()));

    connect(&m_bottomwid,SIGNAL(sig_showPlayingPanel()),this,SLOT(slot_showPlayingPanel()));
    connect(&m_bottomwid,SIGNAL(sig_favoriteClicked()),this,SLOT(slot_favoriteclicked()));

    connect(m_player,SIGNAL(audioPlay()),this,SLOT(onAudioPlay())); //TODO：改写slot_playerStatusChanged
    connect(m_player,SIGNAL(audioPause()),this,SLOT(onAudioPause()));
    connect(m_player,SIGNAL(audioFinish(bool)),this,SLOT(onAudioFinish(bool)));//TODO:改写slot_mediaStatusChanged

    connect(m_player,SIGNAL(metaDataChanged()),this,SLOT(slot_updateInfo()));
    connect(m_player,SIGNAL(positionChanged(int)),&m_bottomwid,SLOT(updatePosition(int)));//播放的位置改变->更新进度条播放位置
    connect(m_player,SIGNAL(positionChanged(int)),this,SLOT(musicPositionChanged(int)));
    connect(m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条

    connect(m_player,SIGNAL(titleFound(QString)),this,SLOT(slot_SetMusicTitle(QString)));
    connect(m_player,SIGNAL(artistFound(QString)),this,SLOT(slot_SetMusicArtist(QString)));
    connect(m_player,SIGNAL(albumFound(QString)),this,SLOT(slot_SetMusicAlbum(QString)));
    connect(m_player,SIGNAL(pictureFound(QPixmap)),this,SLOT(slot_SetMusicPicture(QPixmap)));

    connect(m_player, SIGNAL(audioPlay()), &m_middlewid, SLOT(playPhonagraph()));
    connect(m_player, SIGNAL(audioPause()), &m_middlewid, SLOT(stopPhonagraph()));
    connect(m_player, SIGNAL(audioFinish(bool)), &m_middlewid, SLOT(stopPhonagraph()));

    connect(&m_bottomwid.m_mainslider,SIGNAL(sliderPressed()),this,SLOT(slot_apdaterSlider()));//拖动进度条时->断开部分连接适应拖动操作
    connect(&m_bottomwid.m_mainslider,SIGNAL(sliderReleased()),this,SLOT(slot_setPosition()));//进度条移动->更新音乐的播放位置

}

void MainWindow::UpdateListConn()
{
    //TODO:获取所有的stack
    QVector<AbstractMiddleLeftStackWidget*> &stackVec=m_leftWidget->stackWidgetVector();
    for (int i = 0; i < stackVec.size(); ++i) {
        AbstractMiddleLeftStackWidget* leftStack=stackVec.at(i);
        QVector<playListWidget*> &vec=leftStack->playListWidgetVector();
        for(int i=0;i<vec.count();i++)
        {
            disconnect(&vec.at(i)->m_Btntable,SIGNAL(sig_addPlayList()),leftStack,SLOT(slot_addPlayListWithRename()));//添加播放列表
            connect(&vec.at(i)->m_Btntable,SIGNAL(sig_addPlayList()),leftStack,SLOT(slot_addPlayListWithRename()));

            disconnect(&vec.at(i)->m_Btntable,SIGNAL(sig_delPlayList()),leftStack,SLOT(slot_removePlayList()));//移除播放列表
            connect(&vec.at(i)->m_Btntable,SIGNAL(sig_delPlayList()),leftStack,SLOT(slot_removePlayList()));

            disconnect(&vec.at(i)->m_table,SIGNAL(sig_play(int)),&playcontrol,SLOT(slot_play(int)));//播放triggered
            connect(&vec.at(i)->m_table,SIGNAL(sig_play(int)),&playcontrol,SLOT(slot_play(int)));

            disconnect(&vec.at(i)->m_table,SIGNAL(sig_loveStatusChanged()),this,SLOT(slot_loveStateChanged()));//love状态更新通知底部
            connect(&vec.at(i)->m_table,SIGNAL(sig_loveStatusChanged()),this,SLOT(slot_loveStateChanged()));
        }
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
    m_player->setVolume(value);
}

void MainWindow::onAudioPlay()
{
    m_bottomwid.setPlayStyle();
    //m_traymenu.setPlayStyle();
}

void MainWindow::onAudioPause()
{
     m_bottomwid.setPauseStyle();
     //m_traymenu.setPauseStyle();
}

void MainWindow::onAudioFinish(bool isstop)
{
    if(isstop==true)
    {
        m_bottomwid.setPauseStyle();
    }
    else
    {
        playcontrol.slot_endOfMedia();
    }
}

void MainWindow::musicPositionChanged(int pos)
{
    //改变预览歌词时的滚动状态
    if( m_middlewid.pagePreviewLyric->lyricViewer->isLyricValid()
            && m_middlewid.currentPage == 1)
        m_middlewid.pagePreviewLyric->lyricViewer->scrollLyricPanel->lyricPanel->higthLineLyricAtPos(pos);

}

void MainWindow::slot_setPlayerPlayOrPause()
{
    playListWidget *finalwid=playListWidget::getCurrentList();

    if(!finalwid)
        return;
    if(m_player->state()==MusicPlayer::PlayingState)
    {
            m_player->pause();
    }
    else if(m_player->state() == MusicPlayer::PausedState)
    {
        m_player->play();
    }
}

void MainWindow::slot_updateInfo()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
    {
        m_bottomwid.setOriginStyle();
        m_middlewid.onSetPagePreviewOriginStyle();
         return;
    }

    m_bottomwid.setFavorite(finalwid->m_table.isLoved(-1));//正在播放的行的love状态
    QString songname=finalwid->currentMusicName();
    m_bottomwid.setSongName(songname);
    m_middlewid.onSetMusicTitle(songname);
    //m_traymenu.setCurrentSongName(songname);
}

void MainWindow::slot_setPlayMode()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
        return;

    //qDebug()<<"playmode="<<m_player.playlist()->playbackMode();

    if(m_bottomwid.getPlayMode()==PlayMode::playInOrder)
    {
        m_bottomwid.setRandomStyle();
        updatePlayMode(PlayMode::playRandom);
    }
    else if(m_bottomwid.getPlayMode()==PlayMode::playRandom)
    {
        m_bottomwid.setOneCycleStyle();
        updatePlayMode(PlayMode::playOneCircle);
    }
    else if(m_bottomwid.getPlayMode()==PlayMode::playOneCircle)
    {
        m_bottomwid.setInOrderStyle();
        updatePlayMode(PlayMode::playInOrder);
    }

}

void MainWindow::slot_setPosition()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
    {
        connect(m_player,SIGNAL(positionChanged(int)),&m_bottomwid,SLOT(updatePosition(int)));//播放的位置改变->更新进度条播放位置
        connect(m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条
        return;
    }
    m_player->seek(m_bottomwid.m_mainslider.value());
    connect(m_player,SIGNAL(positionChanged(int)),&m_bottomwid,SLOT(updatePosition(int)));//播放的位置改变->更新进度条播放位置
    connect(m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条

}

void MainWindow::slot_apdaterSlider()
{
    disconnect(m_player,SIGNAL(positionChanged(int)),&m_bottomwid,SLOT(updatePosition(int)));//播放的位置改变->更新进度条播放位置
    disconnect(m_player,SIGNAL(durationChanged(qint64)),&m_bottomwid,SLOT(updateDuration(qint64)));//播放歌曲改变->更新进度条
}

void MainWindow::updatePlayMode(PlayMode mode)
{
//        foreach(playListWidget *f,m_pLefStack0->playListWidgetVector())//for midleft0
//        {
//                f->setPlayMode(mode);
//        }
        //更新所有的stack
        QVector<AbstractMiddleLeftStackWidget*> &stackVec=m_leftWidget->stackWidgetVector();
        for (int i = 0; i < stackVec.size(); ++i) {
            AbstractMiddleLeftStackWidget* leftStack=stackVec.at(i);
            foreach(playListWidget *f,leftStack->playListWidgetVector())//for midleft0
            {
                    f->setPlayMode(mode);
            }
        }

}

void MainWindow::slot_showPlayingPanel()
{
    m_middlewid.switchPage(0,1);
}

void MainWindow::slot_favoriteclicked()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
    {
         return;
    }
    else
    {
        finalwid->m_table.slot_currentlovetrigger();
        m_bottomwid.setFavorite(finalwid->m_table.isLoved(-1));
    }
}

void MainWindow::slot_loveStateChanged()
{
    playListWidget *finalwid=playListWidget::getCurrentList();
    if(!finalwid)//如果为空
         return;
    else
        m_bottomwid.setFavorite(finalwid->m_table.isLoved(-1));
}

void MainWindow::slot_SetMusicTitle(QString title)
{
    m_bottomwid.setSongName(title);
    m_middlewid.onSetMusicTitle(title);
}

void MainWindow::slot_SetMusicArtist(QString artist)
{
    m_middlewid.onSetMusicArtist(artist);
}

void MainWindow::slot_SetMusicAlbum(QString album)
{
    m_middlewid.onSetMusicAlbum(album);
}

void MainWindow::slot_SetMusicPicture(QPixmap pixmap)
{
    m_bottomwid.setPicturePixmap(pixmap);
    m_middlewid.onSetAlbumImage(pixmap);
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



