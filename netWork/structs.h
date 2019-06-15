#ifndef STRUCTUTILS_H
#define STRUCTUTILS_H

struct ItemResult   //搜索的结果
{
   QString songID;
   QString songName;
   QString singer;
   QString albumID;
   QString albumName;
   QString durtion; //时长
   QString coverUrl;
};

struct SongItem  //播放列表中的item
{
    QString name;   //songName - singer
    QString url;    //netease'id is ""
    QString durtion;
    QString coverUrl;
    QString id;
};

struct PlayList // 歌单
{
    QString name;
    QString id;
    QString coverUrl;
};

struct Artists  // 歌手
{
    QString name;
    QString id;
    QString coverUrl;
};


enum class LoginStatus{Failed,Successed};

enum class LogoutStatus{Failed,Successed};

#endif // STRUCTUTILS_H
