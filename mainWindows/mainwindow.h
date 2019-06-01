#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bottomWidgets.h"
#include "topwidgets.h"
#include "topSearchTipsWidget.h"
#include "middleLeftStackWidget0.h"
#include "middleWidgets.h"
#include "volsliderwidget.h"
#include "basewindow.h"
#include "PagePreviewLyric.h"
#include "musicPlayer/musicPlayer.h"
#include "musicPlayer/playControl.h"

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

    MusicPlayer* player(){return m_player;}
    void setOriginalStatus();

    int curVol();
    void setCurVol(int value);

    QPushButton* getBottomButton(){return &(m_bottomwid.m_btnpicture);}


public slots:
    void onAudioPlay();
    void onAudioPause();
    void onAudioFinish(bool);
    void musicPositionChanged(int pos); //更新歌词滚动
    void slot_setPlayerPlayOrPause();

    void slot_updateInfo();//更新底部buttom
    void slot_setPlayMode();
    void slot_setPosition(); //中间槽，桥接一下player和slider
    void slot_apdaterSlider(); //slider的拖动优化
    void updatePlayMode(PlayMode mode);
   // void slot_setPosition();

    void slot_showPlayingPanel();//底部封面点击
    void slot_favoriteclicked();//底部love点击
    void slot_loveStateChanged();//通知底部love更新

    void slot_SetMusicTitle(QString);
    void slot_SetMusicArtist(QString);
    void slot_SetMusicAlbum(QString);
    void slot_SetMusicPicture(QPixmap);

protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    static MainWindow *s_pMainWnd;

private:

    MusicPlayer *m_player;
    TopWidgets m_topwid;
    topSearchTipsWidget m_sertipswid;

    volSliderWidget m_volwid;

    bottomWidgets m_bottomwid;
    middleWidgets m_middlewid;

    middleWidgetLeft* m_leftWidget;

    PlayControl playcontrol;
};

#endif // MAINWINDOW_H
