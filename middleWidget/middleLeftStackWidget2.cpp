#include "middleLeftStackWidget2.h"
#include "qlabel.h"
#include <QVBoxLayout>

middleLeftStackWidget2::middleLeftStackWidget2(QWidget *parent)
    :baseWidget(parent)
    ,m_wid(this)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    init();
}


void middleLeftStackWidget2::init()
{
    QVBoxLayout *vLyout=new QVBoxLayout;

    m_wid.addPushButton("正在下载");
    m_wid.addPushButton("我的下载");
    m_wid.showLayout();
    m_wid.addWidget(new QWidget());
    m_wid.addWidget(new QWidget());

    vLyout->addWidget(&m_wid);
    vLyout->setContentsMargins(0,0,0,0);
    setLayout(vLyout);
}
