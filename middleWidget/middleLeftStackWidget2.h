#ifndef MIDDLELEFTSTACKWIDGET2_H
#define MIDDLELEFTSTACKWIDGET2_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QThread>
#include "baseWidget.h"
#include "myPushButton.h"
#include "abstractmiddleleftstackwidget.h"
#include "structs.h"
#include "QQ.h"


///QQ音乐
class middleLeftStackWidgetScrollArea2:public AbstractMiddleLeftStackWidget
{
    Q_OBJECT
public:
    explicit middleLeftStackWidgetScrollArea2(QWidget *parent);
    ~middleLeftStackWidgetScrollArea2(){}
    virtual void init();

    virtual void initConnection();

    playListWidget * addPlayList(const QString &plname, const QString &picUrl);//隐藏基类的同名方法


public slots:
    void addUserList(const PlayList &playlist, const QList<SongItem> &items);

private:
};


////////////////////////////////////////////////////////////////////////////////
class middleLeftStackWidget2:public baseWidget
{
    Q_OBJECT
public:
    explicit middleLeftStackWidget2(QWidget *parent);
    ~middleLeftStackWidget2(){thread.quit();thread.wait();}

    void init();
    void initThread();
    void initConn();

    middleLeftStackWidgetScrollArea2 * getStackWid(){return stackwid;}

signals:
    void sig_requestPlayList(const QString &playlistID);
    void sig_reqsongLyricReady(const QString &songID, const QString &name, const QString &saveloaction);

public slots:
    void slot_importUserList(); //导入用户歌单
    void slot_requestSongCover(const QString &coverUrl);
    void slot_requestSongLyric(const QString &songID);
    void slot_setSongLyric(const QString &path);

private:
    QLineEdit* importSongList;
    myPushButton *btn_import;

    middleLeftStackWidgetScrollArea2 *stackwid;
    QQ *qq; //工作线程不能有父对象
    QThread thread;
};


#endif  //for QQMusic
