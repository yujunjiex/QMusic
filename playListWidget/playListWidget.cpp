#include "playListWidget.h"
#include "mainwindow.h"
#include "abstractmiddleleftstackwidget.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QPainter>
#include <QEventLoop>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QScrollBar>


static QColor  BGcolor=QColor(230,230,230);
playListWidget * playListWidget::s_pCurList=NULL;
playListWidget::playListWidget(QWidget *parent):baseWidget(parent)
  ,m_playList(this)
{
    //m_playList.setPlaybackMode(QMediaPlaylist::Loop);
    m_table.setTableFinal(this);
    m_Btntable.setTableFinal(this);
    m_playList.setTableFinal(this);

    setMouseTracking(true);

    connect(&m_Btntable,SIGNAL(sig_emptyList()),this,SLOT(slot_emptyList()));//清空列表
    connect(&m_Btntable,SIGNAL(sig_addSong()),this,SLOT(slot_addSong()));//添加歌曲
    connect(&m_table,SIGNAL(sig_RowCountChange()),&m_Btntable,SLOT(slot_updateSongCount()));//歌曲列表改变信息
    connect(&m_Btntable,SIGNAL(clicked(bool)),this,SLOT(slot_showHideTable()));
    connect(&m_table,SIGNAL(sig_doubleclicked()),this,SLOT(slot_releaseCrossWid()));

    connect(&m_table,SIGNAL(sig_delIndex(int)),&m_playList,SLOT(slot_removeSong(int)));//从列表中删除
    connect(&m_table,SIGNAL(sig_addSong()),this,SLOT(slot_addSong()));//添加歌曲

    QVBoxLayout *vlyout1=new QVBoxLayout();
    setMinimumSize(310,74);
    setMaximumWidth(380);

    vlyout1->addWidget(&m_Btntable);
    vlyout1->addWidget(&m_table);
    vlyout1->setContentsMargins(0,0,0,0);
    vlyout1->setSpacing(0);
    setLayout(vlyout1);
}

void playListWidget::setCurrentSongAlbumPic(const QString &strPath)
{
    m_Btntable.setCoverimg(strPath);
}

void playListWidget::setAutoLayout()
{
    m_table.setAutoLayoutSize();
}

const QString playListWidget::currentSongDuration()
{
    int index= m_table.m_playrow;
    QTableWidgetItem *it=m_table.item(index,2);
    if(it!=Q_NULLPTR)
    {
        QString text=it->text();
        return text.isEmpty()? m_table.getHoverDuration().simplified():text.simplified();
    }
    else
        return m_table.getHoverDuration().simplified();
}

int playListWidget::currentSongDurationToInt()
{
    QTime time= QTime::fromString( currentSongDuration(),"mm:ss");
    return time.minute()*60*1000+time.second()*1000;
}

void playListWidget::stopCurrentSong()
{
    MainWindow::GetInstance()->player()->stop();
    m_midleft->setOriginalStatus();
    MainWindow::GetInstance()->player()->setMedia(NULL);
    /*metaDataChanged是在setMedia中发送的，
    *metaDataChanged关联UpdateInfo
    *而UpdateInfo取决于CurrentList，所以要先设置OriginalStatus
    */

}

void playListWidget::addToPlayList(const QString &name, const QString &url, const QString &dur, const QString &strHash, bool /*bAddtoDB*/)
{

    int rowcount= m_table.rowCount();
    /*列表的添加*/
    m_table.insertRow(rowcount);
    m_table.setItem(rowcount,0,new QTableWidgetItem(""));
    m_table.setItem(rowcount,1, new QTableWidgetItem(name));
    m_table.setItem(rowcount,2, new QTableWidgetItem(QString(dur+"    ")));
    m_table.item(rowcount,2)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);

    /*本地文件的列表添加方式*/
    m_playList.addPlayList(url,strHash);

    /*数据库的添加*/
//    if(bAddtoDB)
    //       myDataBase::addSong(ShowButtonName(),name,url,dur);
}

void playListWidget::slot_emptyList()
{
    int i=0;
    int count=m_table.rowCount();
    int mb= QMessageBox::warning(NULL,"","确定要清空吗？",QMessageBox::Ok|QMessageBox::Cancel);
    if(mb==QMessageBox::Cancel) //OK就继续
        return;


    //myDataBase::emptyList(ShowButtonName());

   if(this == getCurrentList())//如果正在播放的
     {
        stopCurrentSong();
     }
    while(i<count)
    {
        int row=m_table.rowCount()-1;
        m_table.slot_cellEnter(-1,0);
        m_table.setCrossWid(-1,0);
        emit m_table.sig_delIndex(row);

        m_table.removeRow(row);
        ++i;
    }

    m_playList.clearMediaList();
    MainWindow::GetInstance()->slot_updateInfo();//更新底部label
    setAutoLayout();
}

void playListWidget::slot_showHideTable()
{
    update();
    if(!m_table.isHidden())
    {
        m_table.hide();
        foreach(playListWidget *f,m_midleft->playListWidgetVector())
                f->m_table.hide();
        //m_midleft->convientShowTableBtn()->hide();

    }
    else
    {
       m_table.show();
       foreach(playListWidget *f,m_midleft->playListWidgetVector())
       {
           if(f!=this)//如果显示的话
           {
               f->m_table.hide();
           }
       }
    }
}

void playListWidget::slot_releaseCrossWid()
{
    update();
    foreach(playListWidget *f,m_midleft->playListWidgetVector())
    {
        if(f!=this)
        {
            f->m_table.setCrossWid(-1,0);
        }
    }
}

void playListWidget::slot_addSong()
{
    static QString  initialName ="F:/CloudMusic";
    QStringList files=QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr("*.mp3"));
    if(files.isEmpty())
        return;

    QMediaPlayer player;
    QEventLoop lp;
    for(int i=0;i<files.count();i++)
    {

        QFileInfo info(files[i]);
        QString m_name=info.completeBaseName();

        if(!m_playList.GetList().contains(files.value(i)))
        {
            QString filePath=files.value(i);
            player.setMedia(QUrl(filePath));
            ////prevent the loop dont stop
            QTimer timer;
            connect(&timer,&QTimer::timeout,[&](){
                lp.quit();
            });
            timer.setSingleShot(true);
            timer.start(2000);
            ////
            connect(&player,SIGNAL(durationChanged(qint64)),&lp,SLOT(quit()));
            lp.exec();
            qint64 musicTime= player.duration();
            //qDebug()<<"duration:"<<musicTime;

            QTime total_time(0, (musicTime/60000)%60, (musicTime/1000)%60);
            QString duration=total_time.toString("mm:ss");
            //qDebug()<<"处理后:"<<duration;

            addToPlayList(m_name,files.at(i),duration);
            setAutoLayout();
        }
    }
}

void playListWidget::wheelEvent(QWheelEvent *e)
{
    int i=e->delta()/5;
    int value=m_midleft->verticalScrollBar()->value();
    m_midleft->verticalScrollBar()->setValue(value-i);
}

void playListWidget::paintEvent(QPaintEvent *e)
{
    baseWidget::paintEvent(e);
    QPainter p(this);
    p.setPen(BGcolor);
    p.drawLine(0,height()-1,width()-1,height()-1);
}

