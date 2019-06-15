#include "abstractmiddleleftstackwidget.h"
#include "mainWindows/mainwindow.h"


AbstractMiddleLeftStackWidget::AbstractMiddleLeftStackWidget(QWidget *parent)
    :myScrollArea(parent)
    ,m_wid(this)
    ,m_searchwid(this)
    ,m_convtwowid(this)
{
    setMinimumWidth(310);
    setMaximumWidth(380);
}

void AbstractMiddleLeftStackWidget::initConvientWidget()
{
    m_convtwowid.hide();
    m_convtwowid.raise();
    connect(&(m_convtwowid.m_btnlocate),SIGNAL(clicked(bool)),this,SLOT(scrolltoCurrentPlayList()));
    m_searchwid.hide();
    m_searchwid.raise();
    connect(&(m_convtwowid.m_btnsearch),SIGNAL(clicked(bool)),&m_searchwid,SLOT(show()));
    connect(&(m_searchwid.m_lineEdit),SIGNAL(textChanged(QString)),this,SLOT(slot_localSearch(QString)));
}

void AbstractMiddleLeftStackWidget::setAutoLayout()
{
    int height=0;
    foreach(playListWidget* p,m_Vector)
    {
        height+= p->height();
    }
    m_wid.setMinimumHeight(height);
}

void AbstractMiddleLeftStackWidget::setOriginalStatus()
{
    playListWidget::setCurrentList(NULL);
}

void AbstractMiddleLeftStackWidget::releaseAllCrossWid()
{
    update();
    foreach(playListWidget *f,this->playListWidgetVector())
    {
            f->m_table.setCrossWid(-1,0);
    }
}

void AbstractMiddleLeftStackWidget::slot_localSearch(const QString &words)
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

void AbstractMiddleLeftStackWidget::scrolltoCurrentPlayList()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;
   int pindex= m_vlyout.indexOf(pPlayList); //若不在当前stack会返回-1

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

void AbstractMiddleLeftStackWidget::slot_verScrBarChange(int value)
{
    if(value!=0)
        m_convtwowid.show();
}

void AbstractMiddleLeftStackWidget::slot_removePlayList()
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

playListWidget * AbstractMiddleLeftStackWidget::addPlayList(const QString &plname)
{
    playListWidget *m_table=new playListWidget(this);
    m_table->setMiddleStackWidget(this);//pass the pointer
    m_table->m_table.hide();
    m_vlyout.insertWidget(m_vlyout.count()-1,m_table);
    m_Vector.insert(m_Vector.count(),m_table);
    m_table->setShowButtonName(plname);
   // m_table->getlistfromDateBase(); //根据目标名 添加歌曲
    m_table->updateCount();//更新一下
    if(MainWindow::GetInstance())
        MainWindow::GetInstance()->UpdateListConn();
    setAutoLayout();
    return m_table;
}

void AbstractMiddleLeftStackWidget::slot_addPlayListWithRename()
{
    playListWidget *table=new playListWidget(this);
    table->setMiddleStackWidget(this);

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
    m_Vector.insert(m_Vector.count(),table);
    table->m_Btntable.click();
    if(MainWindow::GetInstance())
        MainWindow::GetInstance()->UpdateListConn();
    setAutoLayout();
    table->m_Btntable.slot_ReName();
}

void AbstractMiddleLeftStackWidget::resizeEvent(QResizeEvent *e)
{
    myScrollArea::resizeEvent(e);
    m_convtwowid.setGeometry(width()*7/10,height()*8/10,m_convtwowid.width(),m_convtwowid.height());
    m_searchwid.setGeometry(0,height()-m_searchwid.height(),width(),m_searchwid.height());
}
