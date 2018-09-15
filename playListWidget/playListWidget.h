#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H


#include <QWidget>
#include <QScrollArea>
#include <QWheelEvent>
#include <QMediaPlaylist>
#include "addTipWidget.h"
#include "pushButtonWidget.h"
#include "showTableButton.h"
#include "tableWidget.h"

class middleLeftStackWidget0;
class middleWidgetLeft;

class playListWidget:public baseWidget
{
    Q_OBJECT
public:
   explicit playListWidget(QWidget*parent=0);
    ~playListWidget(){}
/*static functions*/
    static playListWidget* getCurrentList(){return s_pCurList;}

    static void setCurrentList(playListWidget*pList){s_pCurList=pList;}

/*pass the pointer*/
    void setMiddleStackWidget0(middleLeftStackWidget0*p){m_midleft0=p;m_table.setMiddleStackWidget0(p);}

/*other functions*/
    void setShowButtonName(QString strListName="新建列表"){m_Btntable.setListName(strListName);}

    void setPlayMode(QMediaPlaylist::PlaybackMode mode){m_playList.setPlaybackMode(mode);}

    void setCurrentSongAlbumPic(const QString &strPath);

    void setAutoLayout();
//////////////////////////////[0]playing widget operation

    /*for底部widget的love点击，改写为正在播放item的love click
     * //模拟鼠标移动到播放中的item，
     */
    //playingWidget *getPlayingWidget(){return &m_table.m_playingWid;}

    QString ShowButtonName(){return m_Btntable.getListName();}

   //const QString currentAuthor(){return m_table.item(m_table.m_playrow,1)->text().split("-").value(0).simplified();}
   const QString currentMusicName(){ return m_table.item(m_table.m_playrow,1)->text().simplified();}
   const QString currentSongDuration();
///////////////////////////[1]

    int currentSongDurationToInt();

    void stopCurrentSong();

    //void getlistfromDateBase();

    void addToPlayList(const QString &name, const QString &url, const QString &dur, bool bAddtoDB=true);

    void updateCount(){m_Btntable.slot_updateSongCount();}


////////////////////////////////[2]playList operation
    QMediaPlaylist *mediaList(){return &m_playList;}

    /*重写*/
    //bool isContainUrl(const QString&strUrl){return m_playList.GetList().contains(strUrl);}

//    int getIndexByUrl(const QString &strUrl){return m_playList.GetList().indexOf(strUrl);}
//    QString getUrlByIndex(int index){return m_playList.GetList().value(index);}
//    QString getHashByUrl(const QString &strUrl){return m_playList.GetHashMap().value(strUrl);}
//////////////////////////////////////[3]

    showTableButton m_Btntable;
    tableWidget m_table;
    QMediaPlaylist m_playList;
    middleLeftStackWidget0 *m_midleft0;

public slots:
    void slot_emptyList();

    void slot_showHideTable();

    void slot_addSong();

    void slot_releaseCrossWid();

    /*TODO:after finished SearchTable*/
//    void slot_addSongFromSearchTable(const QStringList& name,const QStringList &url,const QStringList &dur);

//    void slot_playSongFromSearchTable(const QStringList &name,const QStringList &url,const QStringList &dur);
protected:
    static playListWidget *s_pCurList;

    virtual void wheelEvent(QWheelEvent *e);

    virtual void paintEvent(QPaintEvent *e);
};

#endif
