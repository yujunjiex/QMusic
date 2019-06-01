#include "tableWidget.h"
#include <QAction>
#include <QScrollBar>
#include <QHeaderView>
#include <qgridlayout.h>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QApplication>
#include <QMediaPlaylist>
#include "mainwindow.h"
#include "playListWidget.h"
#include "middleLeftStackWidget0.h"
#include "middleconvienttwobutton.h"
#include "middleLeftStackWidget3.h"
#include "middlewidgetleft.h"

tableWidget::tableWidget(QWidget *parent):QTableWidget(parent)
  ,m_playrow(-1)
  ,m_preplayrow(-1)
  ,m_enter(false)
  ,m_prebgItem(-1)
  ,m_loveNowRow(0)
  ,m_text("")
  ,isShowTipWid(true)
  ,m_addWid(this)
  ,m_menu(this)
  ,m_Addtoplistmenu("添加到歌单",&m_menu)
{
    init();
    initMenu();
    connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doublick(int,int)));//播放事件
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_menuRequest(QPoint)));
    connect(this,SIGNAL(sig_RowCountChange()),this,SLOT(slot_rowCountChanged()));
}

void tableWidget::init()
{

    setMouseTracking(true);

    QHBoxLayout *hlyout=new QHBoxLayout;
    hlyout->addWidget(&m_addWid);
    hlyout->setContentsMargins(0,0,0,0);
    setLayout(hlyout);

    setFrameShadow(QFrame::Plain);//设置平的样式
    setFrameShape(QFrame::NoFrame);//设置无边样式
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    setShowGrid(false);//隐藏线
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    setEditTriggers(QTableWidget::NoEditTriggers);//禁用双击编辑功能
    setSelectionBehavior (QAbstractItemView::SelectRows); //选择整行模式
    setSelectionMode (QAbstractItemView::ExtendedSelection);//设为可多选
    setContextMenuPolicy(Qt::CustomContextMenu);//创建右键菜单必需策略

    insertColumn(0);
    insertColumn(1);
    insertColumn(2);
    horizontalHeader()->resizeSection(0,20);
    horizontalHeader()->resizeSection(1,170);
    horizontalHeader()->resizeSection(2,120);
    verticalHeader()->setDefaultSectionSize(35);//设置默认item高度

    setMinimumWidth(310);
    setMaximumWidth(380);
    setMinimumHeight(0);
    setStyleSheet("QTableWidget{color:rgb(48,48,48);}"
                  "QTableWidget::item:selected{background:rgb(180,180,180,100);}"
                  "QTableWidget::item{selection-color:rgb(38,38,38);}");
    connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(slot_cellEnter(int,int)));
    connect(&m_addWid.m_add,SIGNAL(clicked(bool)),this,SIGNAL(sig_addSong()));

    emit sig_RowCountChange();//发信号
}

void tableWidget::initMenu()
{
    QAction*act_del=new QAction("删除",&m_menu);
    QAction*act_play=new QAction("播放",&m_menu);
    QAction*act_addsong=new QAction("添加歌曲",&m_menu);

    m_menu.addAction(act_play);

    m_menu.addAction(act_addsong);
    m_menu.addSeparator();

    m_menu.addMenu(&m_Addtoplistmenu);
    m_menu.addSeparator();
    m_menu.addAction(act_del);
    m_menu.setContentsMargins(4,10,3,10);
    m_Addtoplistmenu.setContentsMargins(4,10,3,10);

    connect(act_addsong,SIGNAL(triggered(bool)),this,SIGNAL(sig_addSong()));
    connect(act_del,SIGNAL(triggered(bool)),this,SLOT(slot_removeRow()));
    connect(act_play,SIGNAL(triggered(bool)),this,SLOT(slot_actplay()));

    m_menu.setStyleSheet("QMenu{background-color: white;border: 1px solid rgb(214,214,214);}"
                    "QMenu::item{height: 28px;padding: 0px 20px 0px 40px;font-size : 12px;color: rgb(102, 102, 102);font-family: 微软雅黑;}"
                    "QMenu::item:focus{padding: -1;}"
                    "QMenu::item:!enabled{color:rgb(150,150,150);}"
                    "QMenu::item:selected{color: white;background-color: rgb(22, 154, 243);}"
                    "QMenu::icon{position: absolute;left: 12px;}"
                         "QMenu::separator{height:1px;background: rgb(209,209,209);margin:4px 0px 4px 0px;}");
}

void tableWidget::ShowOrHideTipWid(bool isshow)
{
    if(isshow==true)
    {
        isShowTipWid=true;
        m_addWid.show();
    }
    else
    {
        isShowTipWid=false;
        m_addWid.hide();
    }
}

void tableWidget::setPlayingRow(int row)
{
    m_playrow=row;
}

bool tableWidget::isPlaying(int row)
{
    if(row!=m_playrow)
        return false;
    else
        return true;
}

bool tableWidget::isLoved(int row)
{
    if(-1==row)  //当row为-1时，判断正在播放的行是否loved
    {
        row=m_playrow;
    }
    if(m_middleftStack->objectName()=="loveMusic")
    {
         return true;
    }
    else if(m_middleftStack->objectName()=="localMusic")
    {
        QString url=m_finalWidget->getUrlByIndex(row);//当前的url
        qDebug()<<"url="<<url;
        qDebug()<<middleLeftStackWidget3::getLoveList()->isContainUrl(url);
        if(middleLeftStackWidget3::getLoveList()->isContainUrl(url))//如果歌曲存在在我的喜欢列表中 就有Loveed
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //TODO:other stack

}


void tableWidget::setAutoLayoutSize()
{
    int minheight=0;
    //TODO:获得进行删除操作的leftstack
      foreach(playListWidget *f,m_middleftStack->playListWidgetVector())
      {
          int height=0;
          int btnheight=f->m_Btntable.height();
          if(!f->m_table.isHidden())//如果显示的话
          {
              for(int i=0;i<f->m_table.rowCount();i++)
                  height+=f->m_table.rowHeight(i);

              if(f->m_table.rowCount() == 0 && isShowTipWid==true)
                  height=m_addWid.height();
              f->m_table.setMinimumHeight(height);
              f->setMaximumHeight(height+btnheight);
              minheight+=(height+btnheight);
          }
          else
          {
              f->m_table.setMinimumHeight(height);
              f->setMaximumHeight(btnheight);
              minheight+=(btnheight);
          }
      }
    m_middleftStack->GetWidget()->setMinimumHeight(minheight);
}

void tableWidget::removeSong(int row, bool setAutoLayout)
{
    if(middleWidgetLeft::getCurrentPlayingStack()!=m_middleftStack->objectName())//防止removeSong影响其他Stack的逻辑
    {
        slot_cellEnter(-1,0);
        emit sig_delIndex(row);
        removeRow(row);
        return;
    }

    int curindex=currentSongIndex();

    qDebug()<<"删除中:"<<row<<"当前正在播放:"<<curindex;
    if(row<=-1)
        return;
    if(curindex<row)
    {
        slot_cellEnter(-1,0);
        emit sig_delIndex(row);
//        myDataBase::deleteSong(m_finalWidget->ShowButtonName(),row);
        removeRow(row);
    }

    else if(curindex==row)//当行正在播放
    {
        if(rowCount()==1)//删除最后一首歌曲
        {
            m_finalWidget->stopCurrentSong();
            emit sig_delIndex(curindex);
//            myDataBase::deleteSong(m_finalWidget->ShowButtonName(),curindex);
            removeRow(curindex);
            m_finalWidget->m_table.setPlayingRow(-1);
        }
        else//跳至下一首歌
        {

            emit sig_delIndex(curindex);
//            myDataBase::deleteSong(m_finalWidget->ShowButtonName(),curindex);
            m_finalWidget->m_table.setPlayingRow(curindex+1);
            m_finalWidget->m_table.setCrossWid(curindex+1,0);
            removeRow(curindex);
            PlayControl::slot_btnnextSong();//下一曲

        }
    }
    else if(curindex>row)
    {
        slot_cellEnter(-1,0);
        emit sig_delIndex(row);
//        myDataBase::deleteSong(m_finalWidget->ShowButtonName(),row);
        removeRow(row);
        m_finalWidget->m_table.setPlayingRow(curindex-1);
        m_finalWidget->m_table.setCrossWid(curindex-1,0);
    }

    if(setAutoLayout)
     setAutoLayoutSize();
}

void tableWidget::setCrossWid(int row, int c)
{
    Q_UNUSED(c);
    if(item(m_preplayrow,0)!=Q_NULLPTR&&row!=m_preplayrow)
    {
        removeCellWidget(m_preplayrow,0);

        m_crossWid->deleteLater();


        m_crossWid=NULL;
    }

    if(row!=m_preplayrow)
    {
        if(item(row,0)!=Q_NULLPTR)//防止内存无用增加
        {
            m_crossWid=new pushButtonCrossWidget(this);

            setCellWidget(row,0,m_crossWid);

        }
        m_preplayrow=m_playrow;
    }

}

void tableWidget::resizeEvent(QResizeEvent *e)
{
    QTableWidget::resizeEvent(e);
    horizontalHeader()->resizeSection(1,width()-140);//resizeHeader
}

void tableWidget::showEvent(QShowEvent *e)
{
    QTableWidget::showEvent(e);
    m_finalWidget->m_Btntable.setTableShowIndicator();
    setAutoLayoutSize();
}

void tableWidget::hideEvent(QHideEvent *e)
{
    QTableWidget::hideEvent(e);
    m_finalWidget->m_Btntable.setTableShowIndicator(false);
    setAutoLayoutSize();    //此处的setAutosize有防闪烁效果
}

void tableWidget::leaveEvent(QEvent *e)
{
    slot_cellEnter(-1, 0);
    QTableWidget::leaveEvent(e);
}

void tableWidget::wheelEvent(QWheelEvent *e)
{
    QTableWidget::wheelEvent(e);
}

void tableWidget::mouseMoveEvent(QMouseEvent *e)
{
    QTableWidget::mouseMoveEvent(e);

}

void tableWidget::slot_currentlovetrigger()
{
    tableWidget *table=(tableWidget*)(&(middleLeftStackWidget3::getLoveList()->m_table));
    if(m_middleftStack->objectName()=="loveMusic")
    {
        table->removeSong(m_playrow,true);  //这里是对当前播放的行做处理
    }
    else if(m_middleftStack->objectName()=="localMusic")
    {
            QString url=m_finalWidget->getUrlByIndex(m_playrow);//当前的url
            int loveRow=0;  //我的喜欢列表中的行号
            if(middleLeftStackWidget3::getLoveList()->isContainUrl(url))//如果歌曲存在在我的喜欢列表中 就有Loveed
            {
                loveRow=middleLeftStackWidget3::getLoveList()->getIndexByUrl(url);
                table->removeSong(loveRow,true);
            }
            else
            {

                QString songname=item(m_playrow,1)->text();
                QString url=m_finalWidget->getUrlByIndex(m_playrow);

                playListWidget *plove=middleLeftStackWidget3::getLoveList(); //第二个列表中

                plove->addToPlayList(songname,url,m_text.simplified());
            }
    }
}

void tableWidget::slot_btnloveclicked()
{
    tableWidget *table=(tableWidget*)(&(middleLeftStackWidget3::getLoveList()->m_table));

    if(!m_groupWid->isLoved())//删除喜爱列表中对应的歌曲
    {
        table->removeSong(m_loveNowRow,true);
    }
    else//添加到我的最爱列表
    {
        QString songname=item(m_prebgItem,1)->text();
        QString url=m_finalWidget->getUrlByIndex(m_prebgItem);

        playListWidget *plove=middleLeftStackWidget3::getLoveList(); //第二个列表中

        plove->addToPlayList(songname,url,m_text.simplified());
    }
    if(m_loveNowRow==m_playrow)//在处理完后发信号
    {
        emit sig_loveStatusChanged();
    }
}

void tableWidget::slot_rowCountChanged()
{
    if(rowCount()==0 && isShowTipWid==true)//如果为空
    {
        m_addWid.show();
    }
    else
    {
        m_addWid.hide();
    }
}

void tableWidget::slot_actplay()
{
    if(rowCount()==0)
        return;
    slot_doublick(currentRow(),0);
}

void tableWidget::slot_removeHoverRow()
{
    removeSong(m_prebgItem);
}

void tableWidget::slot_removeRow()
{
    removeSong(currentRow());
}


void tableWidget::slot_cellEnter(int row, int c)
{
    if(item(m_prebgItem,c)!=Q_NULLPTR&&row!=m_prebgItem)//释放其他cell
    {
        removeCellWidget(m_prebgItem,2);


        item(m_prebgItem,2)->setText(m_text);
        item(m_prebgItem,2)->setTextAlignment(Qt::AlignVCenter|Qt::AlignRight);


        item(m_prebgItem,0)->setBackgroundColor(Qt::transparent);
        item(m_prebgItem,1)->setBackgroundColor(Qt::transparent);
        item(m_prebgItem,2)->setBackgroundColor(Qt::transparent);

        m_groupWid->deleteLater();

        m_groupWid=NULL;

    }
    if(row!=m_prebgItem)
    {


        if(item(row,2)!=Q_NULLPTR)//防止内存无用增加
        {
            m_groupWid=new pushButtonGroupWidget(this);
            m_groupWid->setObjectName(QString::number(row));
            if(m_middleftStack->objectName()=="loveMusic")
            {
                m_groupWid->setLoved();
                connect(&m_groupWid->m_btnLove,SIGNAL(clicked(bool)),this,SLOT(slot_removeHoverRow()));
            }
            else if(m_middleftStack->objectName()=="localMusic")
            {
                QString url=m_finalWidget->getUrlByIndex(row);//当前的url


                if(middleLeftStackWidget3::getLoveList()->isContainUrl(url))//如果歌曲存在在我的喜欢列表中 就有Loveed
                {

                    m_loveNowRow=middleLeftStackWidget3::getLoveList()->getIndexByUrl(url);
                    m_groupWid->setLoved();
                }
                connect(&m_groupWid->m_btnLove,SIGNAL(clicked()),this,SLOT(slot_btnloveclicked()));
            }
            //Todo:OTHER Stack

            setCellWidget(row,2,m_groupWid);

            m_text=item(row,2)->text();

            item(row,2)->setText("");//隐藏时间
            QColor hoverbgcolor(180,180,180,50);

            this->item(row,0)->setBackgroundColor(hoverbgcolor);
            this->item(row,1)->setBackgroundColor(hoverbgcolor);
            this->item(row,2)->setBackgroundColor(hoverbgcolor);
            connect(&m_groupWid->m_btnDel,SIGNAL(clicked()),this,SLOT(slot_removeHoverRow()));
        }
        m_prebgItem=row;
    }
    m_enter=true;
}

void tableWidget::slot_doublick(int r, int c)
{
    if(rowCount()==0)
        return;

    playListWidget::setCurrentList(m_finalWidget); //设置当前列表

    qDebug()<<"当前列表名:"<<m_middleftStack->objectName();
    middleWidgetLeft::setCurrentPlayingStack(m_middleftStack->objectName());
    emit sig_doubleclicked();  //刷新其他的cell用
    setPlayingRow(r);

    slot_cellEnter(-1,0);//刷新cell
    setCrossWid(r,c);//设置左边的播放提示

    emit sig_play(r);
}

void tableWidget::slot_menuRequest(QPoint)
{
    QVector<playListWidget*> &plist=m_middleftStack->playListWidgetVector();
    int index=0;
    /*添加到歌单子菜单 初始化*/
    foreach (playListWidget *final, plist)
    {
        QAction* act=new QAction(final->ShowButtonName(),&m_Addtoplistmenu);
        act->setObjectName(QString::number(index));
        m_Addtoplistmenu.addAction(act);
        connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_moveToPList()));
        index++;
        if(final==m_finalWidget)
        {
            act->setEnabled(false);
        }
    }

    if(rowCount()==0)
        return;
    int height2=QApplication::desktop()->height()-QCursor::pos().y();
    if(height2<m_menu.height())
    {
       m_menu.exec(QPoint(QCursor::pos().x(),height2));
    }
    else
    {
        m_menu.exec(QCursor::pos());
    }
    QList<QAction*> actlist=  m_Addtoplistmenu.actions();
    foreach (QAction* act, actlist)
    {
        act->deleteLater();
    }
}

void tableWidget::slot_moveToPList()
{
    QVector<playListWidget*> &plist=m_middleftStack->playListWidgetVector();
    playListWidget* final=plist.value(sender()->objectName().toInt());

    //多选歌曲的移动
    QList<QTableWidgetItem*> items=selectedItems();

        int songcount=items.count();
        if(songcount==0)
            return;

      for(int i=0;i<songcount;i++)
       {
          QTableWidgetItem*it=items.at(i);
          int row= it->row();

//          if(!final->isContainUrl(m_finalWidget->getUrlByIndex(row)))//url判断在不在列表中
//          {
//               QString songname=item(row,1)->text();
//               QString duration=item(row,2)->text();
//               QString url= m_finalWidget->getUrlByIndex(row);

//               /*TODO:函数完善*/
//               final->addToPlayList(songname,url,duration.simplified());
//          }
      }
}

