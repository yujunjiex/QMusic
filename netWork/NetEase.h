#ifndef NETEASE_H
#define NETEASE_H

#include <QObject>
#include <QtNetwork//QNetworkAccessManager>
#include <QtNetwork//QNetworkReply>
#include <QtNetwork//QNetworkRequest>
#include <Qimage>
#include <QPixmap>
#include <QList>
#include <QMetaType>
#include "structs.h"


class NetEase : public QObject
{
    Q_OBJECT

public:
    explicit NetEase(QObject *parent = 0);
    ~NetEase(){}
signals:
    //排行榜
    void sig_reqTopSongs(const QList<ItemResult> &items);

    //歌手
    void sig_reqArtists(const QList<Artists> &items);
    void sig_reqArtistSongs(const QList<ItemResult> &items);

    //搜索
    void sig_reqSong(const QList<ItemResult> &items);
    void sig_reqNextPageSong(const QList<ItemResult> &items);

    //用户登录，每日歌单，每日推荐
    void sig_reqlogin(LoginStatus status);
    void sig_reqlogout(LogoutStatus status);

    //TODO:改成PlayList
    void sig_reqUserPlayList(const QString& playlistName, const QString& coverUrl, const QList<SongItem> &items); //每次发送一个歌单名,歌单封面及歌单内容

    void sig_reqRecommendPlaylist(const QList<ItemResult> &items);    //返回每日推荐歌曲信息
    void sig_reqRecommendResource(const QList<PlayList> &items);    //返回每日推荐歌单信息

    //歌词
    void sig_reqSongLrc(const QString &location);

    //其他
    void sig_reqSongsUrl(const QList<QString> &songsUrl);
    void sig_reqSongsFromPlayList(const QList<ItemResult> &items);


public Q_SLOTS:
    //排行榜
    void requestTopSongs(int index);    //获取对应榜单的歌曲信息

    //歌手
    void requestArtists();  //获取当前热门歌手信息
    void requestArtistSongs(const QString &artistID);  //获取id对应歌手的歌曲

    //搜索
    //TODO:requestSong中要将m_offset置为0，requestSongNextPage中根据m_offset去获得结果
    void requestSong(const QString &keywords, int offset=0);
    void requestSongNextPage();

    //用户登录，用户歌单，每日推荐
    void requestLogin(const QString &username="", const QString &passwd="");  //每次启动程序时调用，这里需要发送登录状态
    void requestLogout();
    void requestUserPlayList(); //用户歌单(每次启动程序要调用更新)

    void requestRecommendPlaylist();    //每日推荐歌曲(每次启动程序要调用更新)
    void requestRecommendResource();    //每日推荐歌单(每次启动程序要调用更新)

    //歌词
    void requestlrc(const QString &songID, const QString &name, const QString &saveloaction);   //歌曲id,lrcName,存储的位置

    //其他
    void requestSongsUrl(const QList<QString> &songsID);
    void requestSongsFromPlayList(const QString &playlistID);
    void requestSongsFromAlbum(const QString &albumID); //可先不写

private:

    int m_offset;   //搜索的偏移量
    QString m_songname; //上一次搜索的信息
};

#endif // NETEASE_H
