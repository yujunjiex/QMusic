#include "showTableButton.h"
#include "middleLeftStackWidget0.h"
#include "middlewidgetleft.h"
#include "middleWidgets.h"
#include <QHBoxLayout>
#include <QAction>
#include <QMessageBox>


showTableButton::showTableButton(QWidget *parent):QPushButton(parent)
  ,m_indicator(this)
  ,m_lineEdit(this)
  ,m_playlistName("新建列表[]",this)
  ,m_btncover(this)
{
    init();
    initMenu();
    setFixedHeight(74);
}

void showTableButton::init()
{
    setCursor(Qt::PointingHandCursor);
    m_lineEdit.setGeometry(72,5,250,30);
    m_lineEdit.setContextMenuPolicy(Qt::NoContextMenu);
    m_lineEdit.setStyleSheet("QLineEdit{border:4px solid rgb(40,80,150);}");
    m_lineEdit.installEventFilter(this);
    m_lineEdit.raise();
    m_lineEdit.hide();

    m_btncover.setFixedSize(70,70);
    m_btncover.setIcon(QIcon(":/middlewidget/images/middlewidget/lab_Author.png"));
    m_btncover.setIconSize(QSize(70,70));

    QHBoxLayout *lyout=new QHBoxLayout;

    m_playlistName.setStyleSheet("color:rgb(38,38,38);font: 14px 黑体;");

    m_indicator.setFixedSize(30,30);
    m_indicator.setStyleSheet("QLabel{border-image:url(:/image/middlewidget/indicator_top (1).png);}"
                               "QLabel:hover{border-image:url(:/image/middlewidget/indicator_top (2).png);}"
                               "QLabel:pressed{border-image:url(:/image/middlewidget/indicator_top (1).png);}");
    lyout->addWidget(&m_btncover,0,Qt::AlignVCenter);
    lyout->addWidget(&m_playlistName,0,Qt::AlignVCenter);
    lyout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
    lyout->addWidget(&m_indicator,0,Qt::AlignVCenter);
    lyout->addSpacing(14);
    lyout->setContentsMargins(0,0,0,0);
    lyout->setSpacing(2);
    setLayout(lyout);

    connect(&m_lineEdit,SIGNAL(returnPressed()),this,SLOT(setFocus()));
    connect(&m_btncover,SIGNAL(clicked(bool)),this,SLOT(click()));
}

void showTableButton::initMenu()
{
    QAction *act_addplaylist=new QAction("新建列表",&m_menu);
    QAction *act_addsong=new QAction("添加歌曲",&m_menu);
    QAction *act_delplayList=new QAction("删除列表",&m_menu);
    QAction *act_reName=new QAction("重命名",&m_menu);
    QAction* act_emptyList=new QAction("清空列表",&m_menu);

    m_menu.addAction(act_addplaylist);
    m_menu.addAction(act_addsong);
    m_menu.addSeparator();
    m_menu.addAction(act_emptyList);
    m_menu.addAction(act_delplayList);
    m_menu.addAction(act_reName);
    m_menu.setContentsMargins(4,10,3,10);
    m_menu.actionGeometry(act_reName);//一定不能删除 setEnabledMenuItem要工作必须要它 可能是一个bug

    QAction *act_fixedCov=new QAction("固定当前封面",&m_cover);
    QAction *act_seleCov=new QAction("手动选择图片",&m_cover);
    QAction *act_unfixedCov=new QAction("取消固定",&m_cover);
    m_cover.addAction(act_fixedCov);
    m_cover.addAction(act_seleCov);
    m_cover.addAction(act_unfixedCov);
    m_cover.setContentsMargins(4,10,3,10);
    m_cover.actionGeometry(act_unfixedCov);


    connect(act_emptyList,SIGNAL(triggered(bool)),this,SIGNAL(sig_emptyList()));
    connect(act_reName,SIGNAL(triggered(bool)),this,SLOT(slot_ReName()));
    connect(act_delplayList,SIGNAL(triggered(bool)),this,SIGNAL(sig_delPlayList()));
    connect(act_addplaylist,SIGNAL(triggered(bool)),this,SIGNAL(sig_addPlayList()));
    connect(act_addsong,SIGNAL(triggered(bool)),this,SIGNAL(sig_addSong()));
    //connect(this,SIGNAL(sig_reName(QString)),this,SLOT(slot_reNameDB(QString)));

    connect(act_fixedCov,SIGNAL(triggered(bool)),this,SIGNAL(sig_fixedCover()));
    connect(act_seleCov,SIGNAL(triggered(bool)),this,SIGNAL(sig_selectCover()));
    connect(act_unfixedCov,SIGNAL(triggered(bool)),this,SIGNAL(sig_unfixedCover()));

}

void showTableButton::setTableFinal(playListWidget *parent)
{
     m_finalWid=parent;
}

void showTableButton::setTableShowIndicator(bool bShow)
{
    if(bShow)
    {
        m_indicator.setStyleSheet("QLabel{border-image:url(:/middlewidget/images/middlewidget/indicator_down (1).png);}"
                                   "QLabel:hover{border-image:url(:/middlewidget/images/middlewidget/indicator_down (2).png);}"
                                   "QLabel:pressed{border-image:url(:/middlewidget/images/middlewidget/indicator_down (1).png);}");
    }
    else
    {
        m_indicator.setStyleSheet("QLabel{border-image:url(:/middlewidget/images/middlewidget/indicator_top (1).png);}"
                                   "QLabel:hover{border-image:url(:/middlewidget/images/middlewidget/indicator_top (2).png);}"
                                   "QLabel:pressed{border-image:url(:/middlewidget/images/middlewidget/indicator_top (1).png);}");
    }
}

void showTableButton::setEnabledMenuItem(bool isSetting)
{
//    m_cover.actionAt(QPoint(5,85))->setEnabled(m_iscover);

//    m_menu.actionAt(QPoint(5,309))->setEnabled(isSetting);//del
//    m_menu.actionAt(QPoint(5,337))->setEnabled(isSetting);//rename

}

void showTableButton::slot_updateSongCount()
{
    if(m_finalWid->m_table.rowCount()==0)
        m_playlistName.setText(m_finalWid->ShowButtonName());
    else
        m_playlistName.setText(m_finalWid->ShowButtonName()+=QString("[%1]").arg(QString::number(m_finalWid->m_table.rowCount())));
}


void showTableButton::slot_returnPressed()
{
//    QVector<playListWidget*> &plistVec= m_finalWid->m_midleft0->myTablePlayListFinalVector();

//     foreach(playListWidget*pListFinal,plistVec)
//     {
//       if(&pListFinal->m_Btntable != this)
//       {
//           if(pListFinal->ShowButtonName()==m_lineEdit.text())
//           {
//               QMessageBox::warning(NULL,"warning","歌单名重复!");
//               slot_ReName();
//               return;
//           }
//       }
//     }

   if(m_lineEdit.text().isEmpty())
       slot_ReName();
   else
   {
       emit sig_reName(m_lineEdit.text()); //要先发送消息

       m_finalWid->setShowButtonName(m_lineEdit.text());
       m_finalWid->updateCount();
       m_playlistName.show();
       m_lineEdit.hide();
   }
}

void showTableButton::slot_ReName()
{
    m_lineEdit.show();
    m_lineEdit.setFocus();
    m_lineEdit.raise();
    m_playlistName.hide();
    m_lineEdit.setText(m_playlistName.text().split("[").at(0));
    m_lineEdit.selectAll();
}

void showTableButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        if(m_btncover.contentsRect().contains(mapFromGlobal(QCursor::pos())))
        {
            m_cover.exec(QCursor::pos());
        }
        else
         m_menu.exec(QCursor::pos());
    }
    QPushButton::mouseReleaseEvent(e);
}

bool showTableButton::eventFilter(QObject *o, QEvent *e)
{
    if(o==&m_lineEdit)
    {
        if(e->type()==QEvent::FocusOut)
        {
            slot_returnPressed();
        }
    }
    return QObject::eventFilter(o,e);
}
