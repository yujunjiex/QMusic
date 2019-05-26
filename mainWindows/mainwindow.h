#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "bottomWidgets.h"
#include "topwidgets.h"
#include "topSearchTipsWidget.h"
#include "middleLeftStackWidget0.h"
#include "middleWidgets.h"
#include "volsliderwidget.h"
#include "basewindow.h"
#include "PagePreviewLyric.h"

class MainWindow : public baseWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow(){}
    static MainWindow *GetInstance(){return s_pMainWnd;}
    static MainWindow *InitInstance();

    void init();
    void initConn();
    void initMusic();

    void UpdateListConn();

    QMediaPlayer* player(){return &m_player;}
    void setOriginalStatus();

    int curVol();
    void setCurVol(int value);

    QPushButton* getBottomButton(){return &(m_bottomwid.m_btnpicture);}


public slots:
    void slot_setPlayerPlayOrPause();
    void slot_playerStatusChanged(QMediaPlayer::State status);
    void slot_mediaStatusChanged(QMediaPlayer::MediaStatus  status);
    void slot_updateInfo();//更新底部buttom
    void slot_setPlayMode();
    void slot_setPosition(); //中间槽，桥接一下player和slider
    void slot_apdaterSlider(); //slider的拖动优化
    void updatePlayMode(QMediaPlaylist::PlaybackMode mode);
   // void slot_setPosition();

    void slot_showPlayingPanel();

protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    static MainWindow *s_pMainWnd;

private:

    QMediaPlayer m_player;
    TopWidgets m_topwid;
    topSearchTipsWidget m_sertipswid;

    volSliderWidget m_volwid;

    bottomWidgets m_bottomwid;
    middleWidgets m_middlewid;

    middleLeftStackWidget0* m_pLefStack0;
};

#endif // MAINWINDOW_H
