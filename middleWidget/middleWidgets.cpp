#include "middleWidgets.h"

#include "middlewidgetleft.h"
#include "middleWidgetRight.h"
#include "mainwindow.h"
#include "myPushButton.h"
#include "QHBoxLayout"

middleWidgets::middleWidgets(QWidget *parent)
    : baseWidget(parent)
    , m_leftWid(this)
    , m_rightWid(this)
{

    setStyleSheet("baseWidget{background:white;}");
    initLayout();

}
void middleWidgets::initLayout()
{
    QHBoxLayout *hyout=new QHBoxLayout;

    hyout->addWidget(&m_leftWid);
    hyout->addWidget(&m_rightWid);
    hyout->setSpacing(0);
    hyout->setContentsMargins(0,0,0,0);
    setLayout(hyout);
}


