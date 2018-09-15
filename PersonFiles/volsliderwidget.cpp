#include "volsliderwidget.h"
#include <QHBoxLayout>

volSliderWidget::volSliderWidget(QWidget *p):baseWidget(p)
{
    QHBoxLayout *hlyout=new QHBoxLayout;
    setStyleSheet("QWidget{background-color:rgb(64,64,64,200);border-radius:5px;}");
    m_slider=new mySlider(Qt::Vertical,this);

    m_slider->setStyleSheet("QSlider{background:transparent;}"
                            "QSlider::groove:vertical{background:transparent;border-radius:2px;width:3px;}"
                            "QSlider::sub-page:vertical{background:rgb(122,122,122);}"
                            "QSlider::add-page:vertical{background:rgb(255, 255, 160);}"
                            "QSlider::handle:vertical{background:rgb(255, 255, 160); height: 8px; border-radius: 4px; margin-left: -3px;  margin-right: -3px;  }");
    m_slider->setFixedSize(12,85);

    hlyout->addWidget(m_slider);
    hlyout->setContentsMargins(0,0,0,0);
    setLayout(hlyout);
    setFixedSize(30,110);
    connect(m_slider,SIGNAL(valueChanged(int)),this,SLOT(slot_sliderMove(int)));

}
bool volSliderWidget::eventFilter(QObject *o, QEvent *e)
{
    return QObject::eventFilter(o,e);
}
