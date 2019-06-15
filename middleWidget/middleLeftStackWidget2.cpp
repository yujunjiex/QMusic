#include "middleLeftStackWidget2.h"
#include "qlabel.h"
#include "mainwindow.h"
#include "scaleUtil.h"
#include "playListWidget/playListWidget.h"
#include <QVBoxLayout>
#include <QDir>

middleLeftStackWidgetScrollArea2::middleLeftStackWidgetScrollArea2(QWidget *parent)
    :AbstractMiddleLeftStackWidget(parent)
{
    setMinimumWidth(310);
    setMaximumWidth(380);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    init();
    initConvientWidget();
    initConnection();
}


void middleLeftStackWidgetScrollArea2::init()
{

    this->setObjectName("qqMusic");
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setWidget(&m_wid);
    QGridLayout *glyout=new QGridLayout();
    glyout->addWidget(&m_wid);
    glyout->setContentsMargins(0,0,0,0);
    setLayout(glyout);

    m_vlyout.addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    m_vlyout.setContentsMargins(0,0,0,0);
    m_vlyout.setSpacing(0);
    m_wid.setLayout(&m_vlyout);

//    QStringList list=myDataBase::loadPlayList();
//    for(int i=0;i<list.count();i++)//加载播放列表
//    {
//        addPlayList(list.value(i));
//    }
    setAutoLayout();
    setOriginalStatus();
}

void middleLeftStackWidgetScrollArea2::initConnection()
{
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(slot_verScrBarChange(int)));
}

playListWidget * middleLeftStackWidgetScrollArea2::addPlayList(const QString &plname, const QString &picUrl)
{
    playListWidget *m_playlist=new playListWidget(this);

    m_playlist->m_table.ShowOrHideTipWid(false);
    m_playlist->m_Btntable.ShowOrHideMenu(false);
    m_playlist->m_Btntable.ShowOrHideCoverMenu(false);
    m_playlist->setMiddleStackWidget(this);//pass the pointer
    m_playlist->m_table.hide();

    m_vlyout.insertWidget(m_vlyout.count()-1,m_playlist);
    m_Vector.insert(m_Vector.count(),m_playlist);
    m_playlist->setShowButtonName(plname);
   // m_table->getlistfromDateBase(); //根据目标名 添加歌曲
    m_playlist->updateCount();//更新一下
    if(MainWindow::GetInstance())
        MainWindow::GetInstance()->UpdateListConn();
    setAutoLayout();
    QNetworkRequest request;
    request.setUrl(QUrl(picUrl));
    QNetworkAccessManager netManager;
    QNetworkReply *reply = netManager.get(request);
    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    //connect(&netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    if(reply->error()==QNetworkReply::NoError)
    {
          QPixmap t_pixmap;
          QByteArray arry=reply->readAll();
          t_pixmap.loadFromData(arry);
          m_playlist->setCurrentSongAlbumPic(t_pixmap);
    }else{

    }
    reply->deleteLater();

    return m_playlist;
}

void middleLeftStackWidgetScrollArea2::addUserList(const PlayList &playlist, const QList<SongItem> &items)
{
    playListWidget * playlistwid = addPlayList(playlist.name, playlist.coverUrl);
    foreach(SongItem item, items)
    {
         playlistwid->addToPlayList(item.name, item.url, item.durtion, item.coverUrl, item.id);
         qDebug()<<item.name<<" "<<item.durtion<<" "<<item.url;
         QApplication::processEvents();
    }

//    qDebug()<<playlist.name<<" "<<playlist.coverUrl<<" "<<playlist.id;
//    foreach(SongItem item, items)
//    {
//        qDebug()<<item.name<<" "<<item.durtion<<" "<<item.url;
//    }
}

/////////////////////////////////////////////////////////////////////////////////////
middleLeftStackWidget2::middleLeftStackWidget2(QWidget *parent)
    :baseWidget(parent),
    importSongList(nullptr),
    btn_import(nullptr),
    stackwid(nullptr),
    qq(nullptr),
    thread(this)

{
    setMinimumWidth(310);
    setMaximumWidth(380);
    init();
    initThread();
    initConn();
}

void middleLeftStackWidget2::init()
{
    importSongList = new QLineEdit(this);
    btn_import = new myPushButton(this);
    stackwid = new middleLeftStackWidgetScrollArea2(this);
    qq = new QQ(); //工作线程不能有父对象


    importSongList->setPlaceholderText(tr("歌单id号"));
    importSongList->setMinimumSize(230*ScaleUtil::scale(),30*ScaleUtil::mscale());
    importSongList->setMaximumHeight(30*ScaleUtil::mscale());

    btn_import->setText("导入歌单");
    btn_import->setMinimumSize(80*ScaleUtil::scale(),30*ScaleUtil::mscale());
    btn_import->setMaximumHeight(30*ScaleUtil::mscale());


    QHBoxLayout *hlayout = new QHBoxLayout();

    hlayout->addWidget(importSongList);
    hlayout->addWidget(btn_import);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(stackwid);
    vlayout->setContentsMargins(0,2,0,0);
    vlayout->setSpacing(0);
    this->setLayout(vlayout);
}


void middleLeftStackWidget2::initThread()
{

      qq->moveToThread(&thread);
      //请求歌单
      connect(qq, SIGNAL(sig_reqPlayList(PlayList,QList<SongItem>)), stackwid, SLOT(addUserList(PlayList,QList<SongItem>)));
      connect(this, SIGNAL(sig_requestPlayList(QString)), qq, SLOT(requestPlayList(QString)));

      //请求歌词
      connect(stackwid, SIGNAL(sig_requestSongLyric(const QString &)),this, SLOT(slot_requestSongLyric(const QString &)));
      connect(this, SIGNAL(sig_reqsongLyricReady(const QString &, const QString &, const QString &)), qq, SLOT(requestlrc(const QString &, const QString &, const QString &)));
      connect(qq, SIGNAL(sig_reqSongLrc(QString)), this, SLOT(slot_setSongLyric(const QString &)));

      connect(stackwid, SIGNAL(sig_requestSongCover(const QString &)),this, SLOT(slot_requestSongCover(const QString &)));

      thread.start();   //启动工作线程
}

void middleLeftStackWidget2::initConn()
{
    connect(btn_import,SIGNAL(clicked(bool)),this,SLOT(slot_importUserList()));
}

void middleLeftStackWidget2::slot_importUserList()
{
    QString playlistID = importSongList->text();
    qDebug()<<playlistID;
    emit sig_requestPlayList(playlistID);
}

void middleLeftStackWidget2::slot_requestSongCover(const QString &coverUrl)
{
    //TODO:url转换QUrl，网络请求字节流转换成QPixmap,QMainWindow::getInstance() slot_SetMusicPicture(QPixmap)
//    qDebug()<<"图片url拿到啦！"<<coverUrl;
    QNetworkRequest request;
    request.setUrl(QUrl(coverUrl));
    QNetworkAccessManager netManager;
    QNetworkReply *reply = netManager.get(request);
    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    if(reply->error()==QNetworkReply::NoError)
    {
          QPixmap t_pixmap;
          QByteArray arry=reply->readAll();
          t_pixmap.loadFromData(arry);
          MainWindow::GetInstance()->slot_SetMusicPicture(t_pixmap);
    }else{

    }
    reply->deleteLater();
}

void middleLeftStackWidget2::slot_requestSongLyric(const QString &songID)
{
    //发送信息请求qq的lrc
    emit sig_reqsongLyricReady(songID, playListWidget::getCurrentList()->currentMusicName(), QDir::homePath()+"/.QMusic/lyrics/qqmusic/");
}

void middleLeftStackWidget2::slot_setSongLyric(const QString &path)
{
    MainWindow::GetInstance()->slot_SetMusicLyric(path);
}
