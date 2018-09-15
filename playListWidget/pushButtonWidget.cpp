#include "pushButtonWidget.h"
#include <QHBoxLayout>

pushButtonCrossWidget::pushButtonCrossWidget(QWidget *parent):QWidget(parent)
  ,m_btn(this)
{
    QHBoxLayout *vlyout=new QHBoxLayout;
    m_btn.setFixedSize(16,16);
    m_btn.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/sound.png);}"
                         "QPushButton:hover{border-image:url(:/middlewidget/images/middlewidget/sound.png);}"
                         "QPushButton:pressed{border-image:url(:/middlewidget/images/middlewidget/sound.png);}");
    vlyout->addWidget(&m_btn,0,Qt::AlignCenter);
    vlyout->setContentsMargins(0,0,0,0);
    setLayout(vlyout);
}



/////////////////////////////////////////////////////////////////////////////
pushButtonGroupWidget::pushButtonGroupWidget(QWidget *parent):QWidget(parent)
  ,m_btnLove(this)
  ,m_btnDel(this)
{
    m_islove=false;

    QHBoxLayout *hlyout=new QHBoxLayout;

    m_btnLove.setFixedSize(16,16);

    m_btnDel.setFixedSize(16,16);


    m_btnLove.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/btn_love (1).png);}"
                             "QPushButton:hover{border-image:url(:/middlewidget/images/middlewidget/btn_love (2).png);}"
                             "QPushButton:pressed{border-image:url(:/middlewidget/images/middlewidget/btn_love (3).png);}");

    m_btnDel.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/btn_del (1).png);}"
                            "QPushButton:hover{border-image:url(:/middlewidget/images/middlewidget/btn_del (2).png);}"
                            "QPushButton:pressed{border-image:url(:/middlewidget/images/middlewidget/btn_del (3).png);}");

    hlyout->addWidget(&m_btnLove,0,Qt::AlignCenter);
    hlyout->addWidget(&m_btnDel,0,Qt::AlignCenter);
    hlyout->addSpacing(14);
    hlyout->setSpacing(5); //上下边距
    hlyout->setContentsMargins(50,0,0,0);
    setLayout(hlyout);

    connect(&m_btnLove,SIGNAL(clicked(bool)),this,SLOT(slot_btnloveclicked()));
}

void pushButtonGroupWidget::setLoved()
{
    m_islove=true;
    m_btnLove.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/btn_islove (1).png);}"
                                         "QPushButton:hover{border-image:url(:/middlewidget/images/middlewidget/btn_islove (2).png);}"
                                         "QPushButton:pressed{border-image:url(:/middlewidget/images/middlewidget/btn_islove (3).png);}");
}

void pushButtonGroupWidget::slot_btnloveclicked()
{
    if(m_islove)
    {
        m_btnLove.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/btn_love (1).png);}"
                                 "QPushButton:hover{border-image:url(:/middlewidget/images/middlewidget/btn_love (2).png);}"
                                 "QPushButton:pressed{border-image:url(:/middlewidget/images/middlewidget/btn_love (3).png);}");
    }
    else
    {
        m_btnLove.setStyleSheet("QPushButton{border-image:url(:/middlewidget/images/middlewidget/btn_islove (1).png);}"
                                             "QPushButton:hover{border-image:url(:/middlewidget/images/middlewidget/btn_islove (2).png);}"
                                             "QPushButton:pressed{border-image:url(:/middlewidget/images/middlewidget/btn_islove (3).png);}");
    }
    m_islove=!m_islove;
}
