#include "middleLeftStackWidget3.h"
#include "mainwindow.h"

playListWidget *middleLeftStackWidget3::m_lovedList = nullptr;
middleLeftStackWidget3::middleLeftStackWidget3(QWidget *parent)
  :AbstractMiddleLeftStackWidget(parent)
//  ,m_lovedList(this)
{
    setMinimumWidth(310);
    setMaximumWidth(380);

    init();
    initConvientWidget();
    initConnection();
}


void middleLeftStackWidget3::init()
{

    if(!m_lovedList)
        m_lovedList=new playListWidget();

    this->setObjectName("loveMusic");
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setWidget(&m_wid);
    QGridLayout *glyout=new QGridLayout();
    glyout->addWidget(&m_wid);
    glyout->setContentsMargins(0,0,0,0);
    setLayout(glyout);

    m_lovedList->setMiddleStackWidget(this);
    m_lovedList->setShowButtonName("我的最爱");
 //   m_defaultList.getlistfromDateBase();//添加歌曲
//    m_defaultList.m_table.show();

//    m_defaultList.m_Btntable.setEnabledMenuItem();
    m_lovedList->m_table.ShowOrHideTipWid(false);
    m_lovedList->m_Btntable.ShowOrHideMenu(false);
//    m_defaultList.m_Btntable.ShowOrHideCoverMenu(false);

    m_Vector<<m_lovedList;
    m_vlyout.addWidget(m_lovedList);

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

void middleLeftStackWidget3::initConnection()
{
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(slot_verScrBarChange(int)));
}
