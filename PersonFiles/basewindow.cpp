#include "basewindow.h"
#include "QGridLayout"

baseWindow::baseWindow(QWidget *parent)
    : AbsFrameLessAutoSize(parent)
    , m_mainwid(this)
{
    m_border=8;
    setMinimumSize(1250,850);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    m_mainwid.setAutoFillBackground(true);
    QGridLayout *lyout=new QGridLayout;
    lyout->addWidget(&m_mainwid);
    lyout->setContentsMargins(4,4,4,4); //for shadow margin
    setLayout(lyout);
}
void baseWindow::paintEvent(QPaintEvent *e)
{
    AbsFrameLessAutoSize::paintEvent(e);
 // draw shadow margin

    QPainter painter(this);

    QColor color(0, 0, 0, 50);
    for(int i=0; i<9; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

//////////////////////////////////////////////////////////////////////////
mySkinWidget::mySkinWidget(QWidget *parent):QWidget(parent)
{

}

void mySkinWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //更换皮肤背景
    float d =(float)m_skinPic.height()/m_skinPic.width();
    int h=d*width();
    int w=height()/d;
    if(h<height())//如果图片高度小于窗口高度
    {
        painter.drawPixmap(0,0,w,height(),m_skinPic);
        return;
    }
    painter.drawPixmap(0,0,width(),h,m_skinPic);
    return;
}

void mySkinWidget::setSkin(const QString &skin)
{
    m_skinPic.load(skin);
    m_curPixPath=skin;
    update();
}
