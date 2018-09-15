#include "middleLeftStackWidget0.h"
#include "mainwindow.h"
#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QDebug>
#include <qmath.h>


middleLeftStackWidget0::middleLeftStackWidget0(QWidget *parent)
    :myScrollArea(parent)
    ,m_wid(this)
    ,m_searchwid(this)
    ,m_convtwowid(this)
    ,m_defaultList(this)
{
    setMinimumWidth(310);
    setMaximumWidth(380);

    init();
    initConvientWidget();
    initConnection();
}

void middleLeftStackWidget0::init()
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setWidget(&m_wid);
    QGridLayout *glyout=new QGridLayout;
    glyout->addWidget(&m_wid);
    glyout->setContentsMargins(0,0,0,0);
    setLayout(glyout);

    m_defaultList.setMiddleStackWidget0(this);
    m_defaultList.setShowButtonName("默认列表");
 //   m_defaultList.getlistfromDateBase();//添加歌曲
    m_defaultList.m_table.show();
    m_defaultList.m_Btntable.setEnabledMenuItem();

    m_Vector<<&m_defaultList;
    m_vlyout.addWidget(&m_defaultList);

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

void middleLeftStackWidget0::initConvientWidget()
{
    m_convtwowid.hide();
    m_convtwowid.raise();
    connect(&(m_convtwowid.m_btnlocate),SIGNAL(clicked(bool)),this,SLOT(scrolltoCurrentPlayList()));
    m_searchwid.hide();
    m_searchwid.raise();
    connect(&(m_convtwowid.m_btnsearch),SIGNAL(clicked(bool)),&m_searchwid,SLOT(show()));
    connect(&(m_searchwid.m_lineEdit),SIGNAL(textChanged(QString)),this,SLOT(slot_localSearch(QString)));
}

void middleLeftStackWidget0::initConnection()
{
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(slot_verScrBarChange(int)));
}

void middleLeftStackWidget0::setAutoLayout()
{
    int height=0;
    foreach(playListWidget* p,m_Vector)
    {
        height+= p->height();
    }
    m_wid.setMinimumHeight(height);
}

void middleLeftStackWidget0::setOriginalStatus()
{
    playListWidget::setCurrentList(NULL);
}

void middleLeftStackWidget0::slot_localSearch(const QString &words)
{
    foreach(playListWidget *f,m_Vector)
    {
        int row= f->m_table.m_playrow;
        int count=f->m_table.rowCount();
        for(int i=0;i<count;i++)
        {
            f->m_table.setRowHeight(i,0);
            if(f->m_table.item(i,1)->text().contains(words))
            {
                f->m_table.show();
                if(row!=i)
                   f->m_table.setRowHeight(i,35);
                else
                     f->m_table.setRowHeight(i,35);
            }
            if(words=="")
            {
                 if(row!=i)
                    f->m_table.setRowHeight(i,35);
                 else
                    f->m_table.setRowHeight(i,35);
            }
        }
        f->setAutoLayout();
    }
}

void middleLeftStackWidget0::scrolltoCurrentPlayList()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;
   int pindex= m_vlyout.indexOf(pPlayList);

    if(!pPlayList->m_table.isHidden()&&pPlayList->m_table.rowCount()!=0)//if it is visiable
    {
        int height=0;
        for(int i=0;i<pindex;i++)
        {
            height+=m_Vector.value(i)->height();
        }
        int index=pPlayList->m_table.m_playrow;
        this->verticalScrollBar()->setValue(height+index*32);

    }
    else if(pPlayList->m_table.isHidden()&&pPlayList->m_table.rowCount()!=0)
    {
        pPlayList->m_Btntable.clicked();
        int index=pPlayList->m_table.m_playrow;
        this->verticalScrollBar()->setValue(index*32);
    }
}

void middleLeftStackWidget0::slot_verScrBarChange(int value)
{
    if(value!=0)
        m_convtwowid.show();
}

void middleLeftStackWidget0::slot_removePlayList()
{
    playListWidget* f= (playListWidget*)sender()->parent();
    m_vlyout.removeWidget(f);
    if(f == playListWidget::getCurrentList())//如果遇到正在播放
    {
        f->stopCurrentSong();
    }
   // myDataBase::removePlayList(f->ShowButtonName());//dbremoved
    m_Vector.removeOne(f);//从这里vector移出
    f->deleteLater();
    MainWindow::GetInstance()->slot_updateInfo();//更新底部label
    setAutoLayout();
}

void middleLeftStackWidget0::addPlayList(const QString &plname)
{
    playListWidget *m_table=new playListWidget(this);
    m_table->setMiddleStackWidget0(this);//pass the pointer
    m_table->m_table.hide();
    m_vlyout.insertWidget(m_vlyout.count()-1,m_table);
    m_Vector.insert(m_Vector.count()-1,m_table);
    m_table->setShowButtonName(plname);
   // m_table->getlistfromDateBase(); //根据目标名 添加歌曲
    m_table->updateCount();//更新一下
    setAutoLayout();
}

void middleLeftStackWidget0::slot_addPlayListWithRename()
{
    playListWidget *table=new playListWidget(this);
    table->setMiddleStackWidget0(this);

    QStringList strlist;
    for(int i=0;i<m_Vector.count();i++)
    {
        strlist<<m_Vector.at(i)->ShowButtonName();
    }
    for(int i=1;i<=m_Vector.count();i++)
    {
        if(!strlist.contains(QString("新建列表%1").arg(i)))//如果包含
        {
            table->setShowButtonName(QString("新建列表%1").arg(i));
            break;
        }
    }
   // myDataBase::addPlayList(table->ShowButtonName());  //db

    table->m_table.hide();
    m_vlyout.insertWidget(m_vlyout.count()-1,table);
    m_Vector.insert(m_Vector.count()-1,table);
    table->m_Btntable.click();
    if(MainWindow::GetInstance())
        MainWindow::GetInstance()->UpdateListConn();
    setAutoLayout();
    table->m_Btntable.slot_ReName();
}

void middleLeftStackWidget0::slot_play(int index)
{
    playListWidget *pPlayList= playListWidget::getCurrentList();
    QMediaPlaylist *playlist= pPlayList->mediaList();
    if(!playlist->isEmpty())
    {

        MainWindow::GetInstance()->player()->setPlaylist(playlist);
        playlist->setCurrentIndex(index);
        MainWindow::GetInstance()->player()->play();
    }
}

void middleLeftStackWidget0::slot_endOfMedia()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;

    int currentIndex=0;
    if(MainWindow::GetInstance()->player()->playlist()->playbackMode()==QMediaPlaylist::Random)
    {
        int row=MainWindow::GetInstance()->player()->playlist()->mediaCount();
        currentIndex=qrand()%row;
    }
    else if(MainWindow::GetInstance()->player()->playlist()->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        currentIndex=MainWindow::GetInstance()->player()->playlist()->currentIndex();
    }
    else
    {
        currentIndex=MainWindow::GetInstance()->player()->playlist()->currentIndex();

        if(++currentIndex==MainWindow::GetInstance()->player()->playlist()->mediaCount())//当前播放的是最后一首歌
        {
            currentIndex=0;

        }
    }

    MainWindow::GetInstance()->player()->playlist()->setCurrentIndex(currentIndex);
    MainWindow::GetInstance()->player()->play();
    pPlayList->m_table.setPlayingRow(currentIndex);
    pPlayList->m_table.setCrossWid(currentIndex,0);
}

void middleLeftStackWidget0::slot_btnnextSong()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;

    int currentIndex=0;
    if(MainWindow::GetInstance()->player()->playlist()->playbackMode()==QMediaPlaylist::Random)
    {
        int row=MainWindow::GetInstance()->player()->playlist()->mediaCount();
        currentIndex=qrand()%row;
    }
    else if(MainWindow::GetInstance()->player()->playlist()->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        currentIndex=MainWindow::GetInstance()->player()->playlist()->currentIndex();
    }
    else
    {
        currentIndex=MainWindow::GetInstance()->player()->playlist()->currentIndex();

        if(++currentIndex==MainWindow::GetInstance()->player()->playlist()->mediaCount())//当前播放的是最后一首歌
        {
            currentIndex=0;
        }
    }

    MainWindow::GetInstance()->player()->playlist()->setCurrentIndex(currentIndex);
    MainWindow::GetInstance()->player()->play();
    pPlayList->m_table.setPlayingRow(currentIndex);
    pPlayList->m_table.setCrossWid(currentIndex,0);

}

void middleLeftStackWidget0::slot_btnpreSong()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;

    int count=MainWindow::GetInstance()->player()->playlist()->mediaCount();
    int currentIndex=0;
    if(MainWindow::GetInstance()->player()->playlist()->playbackMode()==QMediaPlaylist::Random)
    {
        int row=count;
        currentIndex=qrand()%row;
    }
    else if(MainWindow::GetInstance()->player()->playlist()->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        currentIndex=MainWindow::GetInstance()->player()->playlist()->currentIndex();
    }
    else
    {
        currentIndex=MainWindow::GetInstance()->player()->playlist()->currentIndex();

        if(--currentIndex<0)//当前播放的是剩下最后一首歌或第一首歌
        {

            currentIndex=0;
            if(count>1)//第一首歌
            {
                currentIndex=count-1;
            }
        }
    }

    MainWindow::GetInstance()->player()->playlist()->setCurrentIndex(currentIndex);
    MainWindow::GetInstance()->player()->play();
    pPlayList->m_table.setPlayingRow(currentIndex);
    pPlayList->m_table.setCrossWid(currentIndex,0);
}

void middleLeftStackWidget0::resizeEvent(QResizeEvent *e)
{
    myScrollArea::resizeEvent(e);
    m_convtwowid.setGeometry(width()*7/10,height()*8/10,m_convtwowid.width(),m_convtwowid.height());
    m_searchwid.setGeometry(0,height()-m_searchwid.height(),width(),m_searchwid.height());
}












