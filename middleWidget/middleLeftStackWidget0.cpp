#include "middleLeftStackWidget0.h"
#include "mainwindow.h"
#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QDebug>
#include <qmath.h>


middleLeftStackWidget0::middleLeftStackWidget0(QWidget *parent)
    :AbstractMiddleLeftStackWidget(parent)
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
    this->setObjectName("localMusic");
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    setWidget(&m_wid);
    QGridLayout *glyout=new QGridLayout();
    glyout->addWidget(&m_wid);
    glyout->setContentsMargins(0,0,0,0);
    setLayout(glyout);

    m_defaultList.setMiddleStackWidget(this);
    m_defaultList.setShowButtonName("默认列表");
 //   m_defaultList.getlistfromDateBase();//添加歌曲
//    m_defaultList.m_table.show();

    m_defaultList.m_Btntable.setEnabledMenuItem();
//    m_defaultList.m_table.ShowOrHideTipWid(false);
//    m_defaultList.m_Btntable.ShowOrHideMenu(false);
//    m_defaultList.m_Btntable.ShowOrHideCoverMenu(false);

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

void middleLeftStackWidget0::initConnection()
{
    connect(this->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(slot_verScrBarChange(int)));
}












