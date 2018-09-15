#include <QPainter>
#include "downloadstackedwidget.h"

downloadStackedWidget::downloadStackedWidget(QWidget *parent)
    :baseWidget(parent)
    ,m_stackwid(this)
{
    init();
}

void downloadStackedWidget::init()
{
    m_hlyout.setSpacing(0);
    m_hlyout.setContentsMargins(0,0,0,0);

    m_stackwid.setCurrentIndex(0);
    connect(&m_stackwid,SIGNAL(currentChanged(int)),this,SLOT(curWidIndexChange(int)));
}

void downloadStackedWidget::addPushButton(const QString &name)
{
    myPushButton *m_btn=new myPushButton(this);
    m_btn->setFixedHeight(50);
    m_btn->setText(name);
    m_btn->setStyleSheet("color:rgb(68,68,68);font-size:20px;");
    m_btnList<<m_btn;//添加进容器
    m_hlyout.addWidget(m_btn);
}

void downloadStackedWidget::showLayout()
{
    for(int i=0;i<m_btnList.count();i++)//建立槽
    {
        m_btnList.at(i)->setObjectName(QString::number(i));//目标名
        connect(m_btnList.at(i),SIGNAL(clicked()),this,SLOT(buttonClicked()));
    }

    m_vlyout.addLayout(&m_hlyout);
    m_vlyout.addWidget(&m_stackwid);
    m_vlyout.setSpacing(0);
    m_vlyout.setContentsMargins(0,0,0,0);
    setLayout(&m_vlyout);
}

void downloadStackedWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(230,230,230));
    p.drawLine(QPoint(0,50),QPoint(width(),50));
}

void downloadStackedWidget::buttonClicked()
{
    m_stackwid.setCurrentIndex(sender()->objectName().toInt());
}

void downloadStackedWidget::curWidIndexChange(int index)
{
    for(int i=0;i<m_btnList.count();i++)
    {
        if(i==index)
        {
            m_btnList.at(i)->setStyleSheet("color:rgb(40,143,231);font-size:20px;");
        }
        else
        {
            m_btnList.at(i)->setStyleSheet("color:rgb(68,68,68);font-size:20px;");
        }
    }
}
