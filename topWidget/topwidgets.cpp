#include "topwidgets.h"
#include <QLayout>
#include <QLabel>

TopWidgets::TopWidgets(QWidget *parent):baseWidget(parent)
{
    m_btnserch = new myPushButton(&m_lineEdit);
    init();
    setMouseTracking(true);
}

void TopWidgets::init()
{
    setStyleSheet("bottomWidgets{background:transparent;}");
    setMinimumSize(1000,50); //让右边距显现出来
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QHBoxLayout *hmainyout=new QHBoxLayout;
///////////////////////////////////////////////////////////////////////////////////////////////////////////first lyout

    QHBoxLayout *hyout1=new QHBoxLayout;
    myPushButton*btn=new myPushButton(this);
    btn->setFixedSize(38,38);
    btn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/ico/QuickTimePlayer48px.ico)}");
    hyout1->addWidget(btn);

////////////////////////////////////////////////////////////////////////////////////////////////////////////second lyout
    QHBoxLayout *hyout2=new QHBoxLayout;

    m_lineEdit.setMinimumSize(360,36);
    m_lineEdit.setMaximumSize(400,36);
    m_lineEdit.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_lineEdit.setStyleSheet("QLineEdit{border-radius:10px;background:rgb(255,255,255,150);}");
    m_lineEdit.setContextMenuPolicy(Qt::NoContextMenu);

    m_btnserch->setFixedSize(26,26);
    m_btnserch->setStyleSheet("QPushButton{background:transparent;border-image: url(:/topwidget/images/topwidget/btn_search (1).png);}"
                          "QPushButton::hover{border-image: url(:/topwidget/images/topwidget/btn_search (2).png);}"
                          "QPushButton::pressed{border-image: url(:/topwidget/images/topwidget/btn_search (3).png);}");
    m_lineEdit.setPlaceholderText("搜索歌曲");
    QMargins margins = m_lineEdit.textMargins();
    m_lineEdit.setTextMargins(margins.left()+15, margins.top(), m_btnserch->width()+15, margins.bottom());


    QHBoxLayout *pSearchLayout = new QHBoxLayout(this);
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(m_btnserch);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0,0,15,0);
    m_lineEdit.setLayout(pSearchLayout);

    hyout2->addWidget(&m_lineEdit);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////third lyout
    QHBoxLayout *hyout3=new QHBoxLayout;


    m_btnexit.setFixedSize(20,20);
    m_btnmini.setFixedSize(20,20);
    m_btnsetting.setFixedSize(20,20);
    m_btnskin.setFixedSize(20,20);

    m_btnexit.setObjectName("m_btnexit");
    m_btnmini.setObjectName("m_btnmini");
    m_btnsetting.setObjectName("m_btnsetting");
    m_btnskin.setObjectName("m_btnskin");

    m_btnexit.setStyleSheet("QPushButton{border-image:url(:/topwidget/images/topwidget/btn_close (1).png);}"
                             "QPushButton::hover{border-image:url(:/topwidget/images/topwidget/btn_close (2).png);}"
                             "QPushButton::pressed{border-image:url(:/topwidget/images/topwidget/btn_close (3).png);}");
    m_btnmini.setStyleSheet("QPushButton{border-image:url(:/topwidget/images/topwidget/btn_mini (1).png);}"
                             "QPushButton::hover{border-image:url(:/topwidget/images/topwidget/btn_mini (2).png);}"
                             "QPushButton::pressed{border-image:url(:/topwidget/images/topwidget/btn_mini (3).png);}");
    m_btnsetting.setStyleSheet("QPushButton{border-image:url(:/topwidget/images/topwidget/btn_setting (1).png);}"
                                "QPushButton::hover{border-image:url(:/topwidget/images/topwidget/btn_setting (2).png);}"
                                "QPushButton::pressed{border-image:url(:/topwidget/images/topwidget/btn_setting (3).png);}");
    m_btnskin.setStyleSheet("QPushButton{border-image:url(:/topwidget/images/topwidget/btn_skin (1).png);}"
                             "QPushButton::hover{border-image:url(:/topwidget/images/topwidget/btn_skin (2).png);}"
                             "QPushButton::pressed{border-image:url(:/topwidget/images/topwidget/btn_skin (3).png);}");

    QLabel*label3=new QLabel("丨",this);
    label3->setFixedSize(10,20);
    label3->setStyleSheet("color:rgb(255,255,255,50);");
    label3->adjustSize();

    hyout3->addWidget(&m_btnskin);
    hyout3->addWidget(&m_btnsetting);
    hyout3->addWidget(label3);
    hyout3->addWidget(&m_btnmini);
    hyout3->addWidget(&m_btnexit);
    hyout3->setSpacing(12);


    hmainyout->addLayout(hyout1);
    hmainyout->addSpacing(190);
    hmainyout->addSpacerItem(new QSpacerItem(80,30,QSizePolicy::Maximum));
    hmainyout->addLayout(hyout2);
    hmainyout->addSpacerItem(new QSpacerItem(110,30,QSizePolicy::Expanding));
    hmainyout->addLayout(hyout3);
    hmainyout->setSpacing(0);
    hmainyout->setContentsMargins(16,10,15,10);
    setLayout(hmainyout);

    connect(m_btnserch,SIGNAL(clicked(bool)),&m_lineEdit,SIGNAL(returnPressed()));

}

void TopWidgets::searchFromLineEdit(const QString str)
{
    m_lineEdit.setText(str);
    emit m_lineEdit.returnPressed();
}

void TopWidgets::slot_serTipsClick(QListWidgetItem *it)
{
     searchFromLineEdit(it->text());
}
