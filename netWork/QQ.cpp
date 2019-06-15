#include "QQ.h"
#include <QFile>
#include <QDebug>
#include "pythonutil.h"
#include "typeconvertutil.h"


QQ::QQ(QObject *parent) : QObject(parent)
{
   m_page=1;
   m_songname="";
}

void QQ::requestPlayList(const QString &playlistID)
{


     PythonUtil::init();
     PyObject * obj=  PythonUtil::open("QQMusicAPI","get_playlist",playlistID);
     QList<SongItem> list;
     PlayList playlist;
     if(obj)
     {
           if(PyDict_Check(obj))
           {
//                qDebug()<<"DICT";
                playlist.id=playlistID;
                PyObject * p_name=PyDict_GetItemString(obj,"playlist_name");
                playlist.name=TypeConvertUtil::toString(p_name);
                PyObject * p_url=PyDict_GetItemString(obj,"logo");
                playlist.coverUrl=TypeConvertUtil::toString(p_url);
                PyObject * sub=PyDict_GetItemString(obj,"songs");
                if(PyList_Check(sub))
                {
//                     qDebug()<<"List";
                     int size=PyList_Size(sub);
//                     qDebug()<<size;
                     for(int i=0;i<size;i++)
                     {
                         SongItem song;;
                         PyObject *ListItem = PyList_GetItem(sub, i);
                          if(PyDict_Check(ListItem))
                         {

                             PyObject *  song_name=PyDict_GetItemString(ListItem,"name");
                             QString  songName=TypeConvertUtil::toString(song_name);
                             PyObject * artist=PyDict_GetItemString(ListItem,"singer");
                             QString  singer=TypeConvertUtil::toString(artist);
                             song.name=songName.append(" - ").append(singer);
                             PyObject * url=PyDict_GetItemString(ListItem,"url");

                              song.url=TypeConvertUtil::toString(url);
                              PyObject * song_id=PyDict_GetItemString(ListItem,"id");  //song_id
                              QString id=TypeConvertUtil::toString(song_id);
                              song.id=id;
                              PyObject *  Long=PyDict_GetItemString(ListItem,"time");
                              QString  durtion=TypeConvertUtil::toString(Long);
                              song.durtion=durtion;
                              PyObject * pic=PyDict_GetItemString(ListItem,"pic");
                              QString  coverUrl=TypeConvertUtil::toString(pic);
                              song.coverUrl=coverUrl;
                              qDebug()<<song.id<<" "<<song.url;
                              list.append(song);

                         }
                     }
                }

                emit sig_reqPlayList(playlist,list);
           }

     }

     PythonUtil::close();

}

void QQ::requestSong(const QString &keywords, int page)
{
      m_page=0;
      m_songname;
      PythonUtil::init();
      PyObject * obj=PythonUtil::open("QQMusicAPI","get_search_result",keywords);
      QList<ItemResult> list;
      if(obj)
      {
          if(PyList_Check(obj))
          {
               int size=PyList_Size(obj);

               for(int i=0;i<size;i++)
               {
               PyObject * ListItem=PyList_GetItem(obj,i);
               ItemResult result;
               if(PyDict_Check(ListItem))
                   {

                       PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                       QString   songID= QString::number(TypeConvertUtil::toInt(song_id));
                       result.songID=songID;
                       PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                       QString  songName=TypeConvertUtil::toString(song_name);
                       result.songName=songName;
                       PyObject * artist=PyDict_GetItemString(ListItem,"singer");
                       QString  singer=TypeConvertUtil::toString(artist);
                       result.singer=singer;
                       PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                       QString   albumID=QString::number(TypeConvertUtil::toInt(album_id));
                       result.albumID=albumID;
                       PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                       QString  albumName=TypeConvertUtil::toString(album_name);
                       result.albumName=albumName;
                       PyObject * Long =PyDict_GetItemString(ListItem,"durtion");
                       QString  durtion=TypeConvertUtil::toString(Long);
                       result.durtion=durtion;
                       PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                       QString coverUrl=TypeConvertUtil::toString(cover_url);
                       result.coverUrl=coverUrl;
                      // qDebug()<<result.songName<<" "<<result.singer<<" "<<result.durtion;
                       list.append(result);
                   }
               }
          }

          emit sig_reqSong(list);
    }
      PythonUtil::close();

}

void QQ::requestSongNextPage()
{
      m_page+=1;
      PythonUtil::init();
      PyObject * obj=PythonUtil::open("QQMusicAPI","get_search_result",m_songname,m_page);
      QList<ItemResult> list;
      if(obj)
      {
          if(PyList_Check(obj))
          {
               int size=PyList_Size(obj);
               for(int i=0;i<size;i++)
               {
               PyObject * ListItem=PyList_GetItem(obj,i);
               ItemResult result;
               if(PyDict_Check(ListItem))
                   {

                       PyObject *  song_id=   PyDict_GetItemString(ListItem,"song_id");
                       QString   songID= QString::number(TypeConvertUtil::toInt(song_id));
                       result.songID=songID;
                       PyObject *  song_name=PyDict_GetItemString(ListItem,"song_name");
                       QString  songName=TypeConvertUtil::toString(song_name);
                       result.songName=songName;
                       PyObject * artist=PyDict_GetItemString(ListItem,"singer");
                       QString  singer=TypeConvertUtil::toString(artist);
                       result.singer=singer;
                       PyObject * album_id=PyDict_GetItemString(ListItem,"album_id");
                       QString   albumID=QString::number(TypeConvertUtil::toInt(album_id));
                       result.albumID=albumID;
                       PyObject * album_name=PyDict_GetItemString(ListItem,"album_name");
                       QString  albumName=TypeConvertUtil::toString(album_name);
                       result.albumName=albumName;
                       PyObject * Long =PyDict_GetItemString(ListItem,"durtion");
                       QString  durtion=TypeConvertUtil::toString(Long);
                       result.durtion=durtion;
                       PyObject * cover_url=PyDict_GetItemString(ListItem,"cover_url");
                       QString coverUrl=TypeConvertUtil::toString(cover_url);
                       result.coverUrl=coverUrl;
                       qDebug()<<result.songName<<" "<<result.singer<<" "<<result.durtion;
                       list.append(result);
                   }
               }
          }

          emit sig_reqSong(list);
      }

      PythonUtil::close();


}

void QQ::requestSongsUrl(const QList<QString> &songsID)
{

      PythonUtil::init();

      PyObject * obj=  PythonUtil::open("QQMusicAPI","get_song_url",songsID);

      QList<QString> list;
      if(obj)
      {
          if(PyList_Check(obj))
          {
              int size=PyList_Size(obj);
              for(int i=0;i<size;i++)
              {
                  PyObject * ListItem=PyList_GetItem(obj,i);
                  QString url=TypeConvertUtil::toString(ListItem);
                  list.append(url);
                  qDebug()<<url;
              }
          }

          emit sig_reqSongsUrl(list);
      }
      PythonUtil::close();

}

void QQ::requestlrc(const QString &songID, const QString &name, const QString &saveloaction)
{
    PythonUtil::init();
    //int id=songID.toInt();
    PyObject * object= PythonUtil::open("QQMusicAPI","get_song_lyric",songID);
    QString str=TypeConvertUtil::toString(object);
    qDebug()<<str;

    if(!str.isEmpty()){   //如果成功
        QRegExp exp("[/*?]"); // fixme 无法包括\\，不得不单独处理
        QString newName = name;
        newName = newName.replace(exp, "_");

        QString location="";
        location+=saveloaction;
        location+=newName;
        location+=".lrc";

      QFile file(location);
      if(!file.exists())
      {
         file.resize(0);
         if(file.open(QIODevice::WriteOnly))//如果打开失败
         {
             QTextStream out(&file);
             out.setCodec("utf-8");
             out << ""+ str +"\n"; //write the lrc
             file.close();
        }

      }

      emit sig_reqSongLrc(location);
  }
    PythonUtil::close();

}




