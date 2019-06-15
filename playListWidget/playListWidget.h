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
#include "musicPlayer/myMediaList.h"

class AbstractMiddleLeftStackWidget;
class middleWidgetLeft;
class middleLeftStackWidget3;

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
    void setMiddleStackWidget(AbstractMiddleLeftStackWidget*p){m_midleft=p;m_table.setMiddleStackWidget(p);}

/*other functions*/
    void setShowButtonName(QString strListName="新建列表"){m_Btntable.setListName(strListName);}

    void setPlayMode(PlayMode mode){m_playList.setPlayMode(mode);}

    void setCurrentSongAlbumPic(const QPixmap &pixmap); //更换ablum图片

    void setCurrentSongAlbumPic(const QString &path);

    void setAutoLayout();
//////////////////////////////[0]playing widget operation

    /*for底部widget的love点击，改写为正在播放item的love click
     *
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

    void addToPlayList(const QString &name, const QString &url,
                       const QString &dur, const QString &coverUrl="", const QString &songID="", bool bAddtoDB=true);


    void updateCount(){m_Btntable.slot_updateSongCount();}


////////////////////////////////[2]playList operation
    myMediaList *mediaList(){return &m_playList;}

    bool isContainUrl(const QString&strUrl){return m_playList.GetList().contains(strUrl);}

    QString getUrlByIndex(int index){return m_playList.GetList().value(index);}

    int getIndexByUrl(const QString &strUrl){return m_playList.GetList().indexOf(strUrl);}

//    QString getHashByUrl(const QString &strUrl){return m_playList.GetHashMap().value(strUrl);}
//////////////////////////////////////[3]

    showTableButton m_Btntable;
    tableWidget m_table;
    myMediaList m_playList;
    AbstractMiddleLeftStackWidget *m_midleft;

public slots:
    void slot_emptyList();

    void slot_showHideTable();

    void slot_addSong();

    void slot_releaseCrossWid();//释放除了本身m_table的其他playListWidget的cell

    /*TODO:after finished SearchTable*/
//    void slot_addSongFromSearchTable(const QStringList& name,const QStringList &url,const QStringList &dur);

//    void slot_playSongFromSearchTable(const QStringList &name,const QStringList &url,const QStringList &dur);
signals:

protected:
    static playListWidget *s_pCurList;

    virtual void wheelEvent(QWheelEvent *e);

    virtual void paintEvent(QPaintEvent *e);
};

#endif
