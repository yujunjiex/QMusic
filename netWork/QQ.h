#ifndef QQ_H
#define QQ_H

#include <QObject>
#include <Qimage>
#include <QPixmap>
#include <QList>
#include <QMetaType>
#include "structs.h"
#include<QJsonArray>

//注册自定义类
//qRegisterMetaType<QList<ItemResult>>("QList<ItemResult>");
//qRegisterMetaType<QList<Artists>>("QList<Artists>");
//qRegisterMetaType<QList<SongItem>>("QList<SongItem>");

//qRegisterMetaType<QList<PlayList>>("QList<PlayList>");
//qRegisterMetaType<QList<QString>>("QList<QString>");
//qRegisterMetaType<QList<PlayList>>("QList<PlayList>");
//qRegisterMetaType<PlayList>("PlayList");

class QQ : public QObject
{
    Q_OBJECT

public:
    explicit QQ(QObject *parent = 0);
    ~QQ(){}
signals:
    //导入歌单
    void sig_reqPlayList(const PlayList &playlist, const QList<SongItem> &items);

    //搜索
    void sig_reqSong(const QList<ItemResult> &items);
    void sig_reqNextPageSong(const QList<ItemResult> &items);

    //歌曲链接
    void sig_reqSongsUrl(const QList<QString> &songsUrl);
    //歌词
     void sig_reqSongLrc(const QString &location);
     //
     void sig_reqSong(const QJsonArray array);

public Q_SLOTS:
    //导入歌单
    void requestPlayList(const QString &playlistID);

    //搜索
    void requestSong(const QString &keywords, int page=1);
    void requestSongNextPage();

    //获得歌曲链接
    void requestSongsUrl(const QList<QString> &songsID);
    //获取歌词
    void requestlrc(const QString &songID, const QString &name, const QString &saveloaction);

private:
    int m_page;   //页数
    QString m_songname; //上一次搜索的信息
};

#endif // QQ_H
