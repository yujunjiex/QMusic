#include "NetEase.h"
#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QDebug>
#include"pythonutil.h"
#include"typeconvertutil.h"

NetEase::NetEase(QObject *parent) : QObject(parent)
{

   m_offset=0;
   m_songname="";
}

void NetEase::requestTopSongs(int index)
{

     PythonUtil::init();
     PyObject *  obj=  PythonUtil::open("NeteaseAPI","get_top_songlist",index);
     QList<ItemResult> list;
     if(obj)
     {
         if(PyList_Check(obj))
         {

             int size=PyList_Size(obj);
             for(int i=0;i<size;i++)
             {
                 ItemResult result;
                 PyObject *ListItem = PyList_GetItem(obj, i);
                 if(PyDict_Check(ListItem))
                 {

                     PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                      QString   songID=QString::number(TypeConvertUtil::toInt(song_id));
                      result.songID=songID;
                      PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                      QString  songName=TypeConvertUtil::toString(song_name);
                      result.songName=songName;
                      PyObject * artist=PyDict_GetItemString(ListItem,"artist");
                      QString  singer=TypeConvertUtil::toString(artist);
                      result.singer=singer;
                      PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                      QString albumID=QString::number( TypeConvertUtil::toInt(album_id))  ;
                      result.albumID=albumID;
                      PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                      QString  albumName=TypeConvertUtil::toString(album_name);
                      result.albumName=albumName;
                      PyObject * Long =PyDict_GetItemString(ListItem,"long");
                      QString  durtion=TypeConvertUtil::toString(Long);
                      result.durtion=durtion;
                      PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                      QString coverUrl=TypeConvertUtil::toString(cover_url);
                      result.coverUrl=coverUrl;
                      list.append(result);

                 }

             }
             qDebug()<<list.size();

             emit sig_reqTopSongs(list);

         }
     }

      PythonUtil ::close();
}

void NetEase::requestArtists()
{
    PythonUtil::init();

    PyObject * obj=PythonUtil::open("NeteaseAPI","get_artists");

    if(obj)
    {
         QList<Artists> list;
         if(PyList_Check(obj))
         {

             int size=PyList_Size(obj);
             for(int i=0;i<size;i++)
             {
                   Artists artists;
                   PyObject *ListItem = PyList_GetItem(obj, i);
                   if(PyDict_Check(ListItem))
                   {
                         PyObject * artists_id=PyDict_GetItemString(ListItem,"artists_id");
                         QString  id=QString::number( TypeConvertUtil::toInt(artists_id)) ;
                         artists.id=id;
                         PyObject * artists_name=PyDict_GetItemString(ListItem,"artists_name");
                         QString  name=TypeConvertUtil::toString(artists_name);
                         artists.name=name;
                         PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                         QString  coverUrl=TypeConvertUtil::toString(cover_url);
                         artists.coverUrl=coverUrl;
                         list.append(artists);
                        // qDebug()<<coverUrl;
                   }

             }

             emit sig_reqArtists(list);
         }

          //qDebug()<<list.size();
    }

    PythonUtil::close();

}

void NetEase::requestArtistSongs(const QString &artistID)
{
     PythonUtil::init();

    int id=artistID.toInt();

    PyObject *  obj=  PythonUtil::open("NeteaseAPI","get_artists_songs",id);
    QList<ItemResult> list;
    if(obj)
    {
        if(PyList_Check(obj))
        {

            int size=PyList_Size(obj);
            for(int i=0;i<size;i++)
            {
                ItemResult result;
                PyObject *ListItem = PyList_GetItem(obj, i);
                if(PyDict_Check(ListItem))
                {

                    PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                     QString   songID= QString::number(TypeConvertUtil::toInt(song_id));
                     result.songID=songID;
                     PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                     QString  songName=TypeConvertUtil::toString(song_name);
                     result.songName=songName;
                     PyObject * artist=PyDict_GetItemString(ListItem,"artist");
                     QString  singer=TypeConvertUtil::toString(artist);
                     result.singer=singer;
                     PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                     QString   albumID=QString::number(TypeConvertUtil::toInt(album_id));
                     result.albumID=albumID;
                     PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                     QString  albumName=TypeConvertUtil::toString(album_name);
                     result.albumName=albumName;
                     PyObject * Long =PyDict_GetItemString(ListItem,"long");
                     QString  durtion=TypeConvertUtil::toString(Long);
                     result.durtion=durtion;
                     PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                     QString coverUrl=TypeConvertUtil::toString(cover_url);
                     result.coverUrl=coverUrl;
                     list.append(result);

                }

            }
            //qDebug()<<list.size();

            emit sig_reqTopSongs(list);

        }
    }

          PythonUtil ::close();

}

void NetEase::requestSong(const QString &keywords, int offset)
{

    m_offset=0;
    m_songname=keywords;
    PythonUtil::init();
    PyObject * obj =PythonUtil::open("NeteaseAPI","get_search_result",keywords);
    QList<ItemResult> list;
    if(obj)
    {
        if(PyList_Check(obj))
        {

            int size=PyList_Size(obj);
            for(int i=0;i<size;i++)
            {
                ItemResult result;
                PyObject *ListItem = PyList_GetItem(obj, i);
                if(PyDict_Check(ListItem))
                {

                     PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                     QString   songID= QString::number(TypeConvertUtil::toInt(song_id));
                     result.songID=songID;
                     PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                     QString  songName=TypeConvertUtil::toString(song_name);
                     result.songName=songName;
                     PyObject * artist=PyDict_GetItemString(ListItem,"artist");
                     QString  singer=TypeConvertUtil::toString(artist);
                     result.singer=singer;
                     PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                     QString   albumID=QString::number(TypeConvertUtil::toInt(album_id));
                     result.albumID=albumID;
                     PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                     QString  albumName=TypeConvertUtil::toString(album_name);
                     result.albumName=albumName;
                     PyObject * Long =PyDict_GetItemString(ListItem,"long");
                     QString  durtion=TypeConvertUtil::toString(Long);
                     result.durtion=durtion;
                     PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                     QString coverUrl=TypeConvertUtil::toString(cover_url);
                     result.coverUrl=coverUrl;
                    // qDebug()<<result.songName<<" "<<result.singer<<" "<<result.durtion;
                     list.append(result);

                }

            }
            //qDebug()<<list.size();

            emit sig_reqSong(list);

        }
    }

    PythonUtil::close();


}

void NetEase::requestSongNextPage()
{

       m_offset+=50;

       PythonUtil::init();
       PyObject * obj =PythonUtil::open("NeteaseAPI","get_search_result",m_songname,m_offset);
       QList<ItemResult> list;
       if(obj)
       {
           if(PyList_Check(obj))
           {

               int size=PyList_Size(obj);
               for(int i=0;i<size;i++)
               {
                   ItemResult result;
                   PyObject *ListItem = PyList_GetItem(obj, i);
                   if(PyDict_Check(ListItem))
                   {

                        PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                        QString   songID= QString::number(TypeConvertUtil::toInt(song_id));
                        result.songID=songID;
                        PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                        QString  songName=TypeConvertUtil::toString(song_name);
                        result.songName=songName;
                        PyObject * artist=PyDict_GetItemString(ListItem,"artist");
                        QString  singer=TypeConvertUtil::toString(artist);
                        result.singer=singer;
                        PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                        QString   albumID=QString::number(TypeConvertUtil::toInt(album_id));
                        result.albumID=albumID;
                        PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                        QString  albumName=TypeConvertUtil::toString(album_name);
                        result.albumName=albumName;
                        PyObject * Long =PyDict_GetItemString(ListItem,"long");
                        QString  durtion=TypeConvertUtil::toString(Long);
                        result.durtion=durtion;
                        PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                        QString coverUrl=TypeConvertUtil::toString(cover_url);
                        result.coverUrl=coverUrl;
                        //qDebug()<<result.songName<<" "<<result.singer<<" "<<result.durtion;
                        list.append(result);

                   }

               }
               //qDebug()<<list.size();

               emit sig_reqSong(list);

           }
       }



}

void NetEase::requestLogin(const QString &username, const QString &passwd)
{

       PythonUtil::init();

      PyObject * obj= PythonUtil::open("NeteaseAPI","login",username,passwd);
      LoginStatus status=LoginStatus::Failed;
      if(obj)
      {
         if(PyBool_Check(obj))
         {

             int s=TypeConvertUtil::toInt(obj);
              if(s==1)
              {
                  //qDebug()<<"登录成功";
                  status=LoginStatus::Successed;
              }

         }
         emit sig_reqlogin(status);
      }

      PythonUtil::close();

}

void NetEase::requestLogout()
{
     PythonUtil::init();

    PyObject * obj= PythonUtil::open("NeteaseAPI","logout");
    if(obj)
    {
         if(PyBool_Check(obj))
         {
             LogoutStatus status=LogoutStatus::Failed;
            int s=TypeConvertUtil::toInt(obj);
            if(s==1)
            {
                 //qDebug()<<"注销成功";
                 status=LogoutStatus::Successed;
            }

            emit sig_reqlogout(status);
         }
    }
    PythonUtil::close();

}

void NetEase::requestUserPlayList()
{
    PythonUtil::init();

    PyObject * obj= PythonUtil::open("NeteaseAPI","get_user_playlist");
    if(obj)
    {
        if(PyList_Check(obj))
        {
            // qDebug()<<"list";
             int size=PyList_Size(obj);
             for(int i=0;i<size;i++)
             {

               PyObject * ListItem=PyList_GetItem(obj,i);
               if(PyDict_Check(ListItem))
               {
                   PyObject * playlist_name=PyDict_GetItemString(ListItem,"playlist_name");
                   QString  playlistName=TypeConvertUtil::toString(playlist_name);
                  // qDebug()<<playlistName;
                   PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                   QString coverUrl=TypeConvertUtil::toString(cover_url);
                  // qDebug()<<coverUrl;
                   PyObject * playlist_id=PyDict_GetItemString(ListItem,"playlist_id");
                   QString playlistID=QString::number(TypeConvertUtil::toInt(playlist_id));
                  // qDebug()<<playlistID;
                   int id=playlistID.toInt();
                   // start 获取歌单中的歌曲
                   PyObject * sub_obj=PythonUtil::open("NeteaseAPI","get_songs_from_playlist_id",id);


                   QList<SongItem> list;
                   if(sub_obj)
                   {

                       if(PyList_Check(sub_obj))
                       {
                            int size=PyList_Size(sub_obj);

                            PyObject * song_name;
                            PyObject * artist;
                            PyObject * song_id;
                            PyObject * Long;
                            PyObject *  cover_url;

                            for(int i=0;i<size;i++)
                            {
                                SongItem item;
                                PyObject *ListItem = PyList_GetItem(sub_obj, i);
                                if(PyDict_Check(ListItem))
                                {
                                     song_name=PyDict_GetItemString(ListItem,"song_name");
                                     QString  songName=TypeConvertUtil::toString(song_name);
                                     artist=PyDict_GetItemString(ListItem,"artist");
                                     QString  singer=TypeConvertUtil::toString(artist);
                                     item.name=songName.append("-").append(singer);
                                     //qDebug()<<item.name;
                                     item.url="";
                                     song_id=PyDict_GetItemString(ListItem,"song_id");  //song_id
                                     QString id=QString::number(TypeConvertUtil::toInt(song_id));
                                     item.id=id;
                                     Long=PyDict_GetItemString(ListItem,"long");
                                     QString  durtion=TypeConvertUtil::toString(Long);
                                     item.durtion=durtion;  //TODO:add coverURL
                                     cover_url=PyDict_GetItemString(ListItem,"cover_url");
                                     QString  coverUrl=TypeConvertUtil::toString(cover_url);
                                      item.coverUrl=coverUrl;
                                      qDebug()<<item.url<<" "<<item.coverUrl;
                                     list.append(item);


                                }


                            }

                   }

               } //end 获取歌单中的歌曲


                   emit sig_reqUserPlayList(playlistName,coverUrl,list);

             }
        }

    }
          PythonUtil::close();

    }
}

void NetEase::requestRecommendPlaylist()
{
    PythonUtil::init();

    PyObject * obj= PythonUtil::open("NeteaseAPI","get_recommend_playlist");
    QList<ItemResult> list;
    if(obj)
    {
        if(PyList_Check(obj))
        {
             int size=PyList_Size(obj);
             for(int i=0;i<size;i++)
             {
                 ItemResult result;
                 PyObject *ListItem = PyList_GetItem(obj, i);
                 if(PyDict_Check(ListItem))
                 {

                     PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                      QString   songID=QString::number(TypeConvertUtil::toInt(song_id));

                      result.songID=songID;
                      PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                      QString  songName=TypeConvertUtil::toString(song_name);
                      qDebug()<<songName;
                      result.songName=songName;
                      PyObject * artist=PyDict_GetItemString(ListItem,"artist");
                      QString  singer=TypeConvertUtil::toString(artist);
                      result.singer=singer;
                      PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                      QString   albumID=QString::number( TypeConvertUtil::toInt(album_id));

                      result.albumID=albumID;
                      PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                      QString  albumName=TypeConvertUtil::toString(album_name);
                      result.albumName=albumName;
                      PyObject * Long =PyDict_GetItemString(ListItem,"long");
                      QString  durtion=TypeConvertUtil::toString(Long);
                      result.durtion=durtion;
                      PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                      QString coverUrl=TypeConvertUtil::toString(cover_url);
                      result.coverUrl=coverUrl;
                      list.append(result);
             }


        }

    }

        emit  sig_reqRecommendPlaylist(list);

    }
     PythonUtil::close();

}

void NetEase::requestRecommendResource()
{
     PythonUtil::init();

     PyObject * obj=PythonUtil::open("NeteaseAPI","get_recommend_resource");
     QList<PlayList>  list;
     if(obj)
     {
         if(PyList_Check(obj))
         {
              int size=PyList_Size(obj);
              for(int i=0;i<size;i++)
              {
                  PlayList  play;
                  PyObject * ListItem=PyList_GetItem(obj,i);
                  if(PyDict_Check(ListItem))
                  {
                      PyObject *  playlist_id=PyDict_GetItemString(ListItem,"playlist_id");
                      QString   id=QString::number(TypeConvertUtil::toInt(playlist_id));
                      play.id=id;
                      qDebug()<<id;

                      PyObject * playlist_name=PyDict_GetItemString(ListItem,"playlist_name");
                      QString name=TypeConvertUtil::toString(playlist_name);
                      play.name=name;
                      PyObject *  cover_url=PyDict_GetItemString(ListItem,"cover_url");
                      QString  coverUrl=TypeConvertUtil::toString(cover_url);
                      play.coverUrl=coverUrl;
                      list.append(play);
                     // qDebug()<<coverUrl;
                  }
              }

               emit sig_reqRecommendResource(list);
         }
     }

      PythonUtil::close();

}

void NetEase::requestlrc(const QString &songID, const QString &name, const QString &saveloaction)
{
    //TODO:调用python中的get_song_lyric()，example:get_song_lyric(424264505)
    //通过python代码中的结果可知，返回值为str则成功，空list则失败
     PythonUtil::init();
     int id=songID.toInt();
     PyObject * object= PythonUtil::open("NeteaseAPI","get_song_lyric",id);
     QString str=TypeConvertUtil::toString(object);
     qDebug()<<str;

    if(!str.isEmpty()){   //如果成功
        QString location="";
       location+=saveloaction;
        location+=name;
       location+=".lrc";

       //把python中的str结果转换成QString，放到下面的yourstr中

      QFile file(location);
      if(file.exists())
      {

      }else
       {

        file.resize(0);
        if(file.open(QIODevice::WriteOnly))//如果打开失败
        {
            QTextStream out(&file);
           out << ""+ str +"\n"; //write the lrc
            file.close();

       }
      }

       emit sig_reqSongLrc(location);
   }
     PythonUtil::close();
}

void NetEase::requestSongsUrl(const QList<QString> & songsID)
{

       PythonUtil::init();
       PyObject * obj=PythonUtil::open("NeteaseAPI","get_song_url",songsID);

       if(obj)
       {

             if(PyList_Check(obj))
             {
                 QList<QString> list;
                 int size=PyList_Size(obj);
                 for(int i=0;i<size;i++)
                 {
                      PyObject *ListItem = PyList_GetItem(obj, i);
                      if(PyDict_Check(ListItem))
                      {
                          PyObject * url=PyDict_GetItemString(ListItem,"url");
                          QString Url=TypeConvertUtil::toString(url);
                          //qDebug()<<Url;
                          list.append(Url);
                      }
                 }

                 emit sig_reqSongsUrl(list);
             }
       }
        PythonUtil::close();
}

void NetEase::requestSongsFromPlayList(const QString &playlistID)
{
      PythonUtil::init();
      int id=playlistID.toInt();
      PyObject * obj=PythonUtil::open("NeteaseAPI","get_songs_from_playlist_id",id);
      QList<ItemResult> list;
      if(obj)
      {

          if(PyList_Check(obj))
          {
               int size=PyList_Size(obj);
               for(int i=0;i<size;i++)
               {
                   ItemResult result;
                   PyObject *ListItem = PyList_GetItem(obj, i);
                   if(PyDict_Check(ListItem))
                   {

                       PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                        QString   songID=QString::number(TypeConvertUtil::toInt(song_id));
                         qDebug()<<songID;
                        result.songID=songID;
                        PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                        QString  songName=TypeConvertUtil::toString(song_name);
                        qDebug()<<songName;
                        result.songName=songName;
                        PyObject * artist=PyDict_GetItemString(ListItem,"artist");
                        QString  singer=TypeConvertUtil::toString(artist);
                        result.singer=singer;
                        PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                        QString   albumID=QString::number( TypeConvertUtil::toInt(album_id));

                        result.albumID=albumID;
                        PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                        QString  albumName=TypeConvertUtil::toString(album_name);
                        result.albumName=albumName;
                        PyObject * Long =PyDict_GetItemString(ListItem,"long");
                        QString  durtion=TypeConvertUtil::toString(Long);
                        result.durtion=durtion;
                        PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                        QString coverUrl=TypeConvertUtil::toString(cover_url);
                        result.coverUrl=coverUrl;
                        list.append(result);
               }


          }
               emit sig_reqSongsFromPlayList(list);

      }

      }

      PythonUtil::close();

}

void NetEase::requestSongsFromAlbum(const QString &albumID)
{


}
