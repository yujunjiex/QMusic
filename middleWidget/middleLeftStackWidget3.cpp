#include "middleLeftStackWidget3.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

middleLeftStackWidget3::middleLeftStackWidget3(QWidget *parent):baseWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout *vLyout=new QVBoxLayout;
    QLabel *label=new QLabel("开发中...",this);
    label->adjustSize();
    label->setAlignment(Qt::AlignHCenter);
    label->setStyleSheet("color:rgb(52,52,52);");
    vLyout->addWidget(label);
    this->setLayout(vLyout);
    //initLayout();
}
