#include "PageMain.h"
#include <QHBoxLayout>

PageMain::PageMain(QWidget *parent)
    : baseWidget(parent)
    , m_leftWid(nullptr)
    , m_rightWid(nullptr)
{
    setStyleSheet("baseWidget{background:white;}"); //设置leftwid和rightwid的背景色
    initLayout();
}

void PageMain::initLayout()
{
    m_leftWid = new middleWidgetLeft();
    m_rightWid = new middleWidgetRight();
    QHBoxLayout *hyout=new QHBoxLayout;

    hyout->addWidget(m_leftWid);
    hyout->addWidget(m_rightWid);
    hyout->setSpacing(0);
    hyout->setContentsMargins(0,0,0,0);
    setLayout(hyout);
}


