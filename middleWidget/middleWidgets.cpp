#include <QFileInfo>
#include "middleWidgets.h"
#include "middlewidgetleft.h"
#include "middleWidgetRight.h"
#include "mainwindow.h"
#include "myPushButton.h"
#include "QHBoxLayout"
#include "mainWindows/mainwindow.h"

middleWidgets::middleWidgets(QWidget *parent)
    : baseWidget(parent),
      pageMain(nullptr),
      pagePreviewLyric(nullptr),
//      pageSetting(nullptr),
      currentPage(0)
{

    setStyleSheet("baseWidget{background:white;}");
    initLayout();
    initAnimation();
    initConnection();

    /*test*/
    onSetPagePreviewOriginStyle();
}

void middleWidgets::initLayout()
{
    pageMain = new PageMain(this);
    pagePreviewLyric = new PagePreviewLyric(this);
//    pageSetting = new PageSetting(this);

    pageMain->raise();
}

void middleWidgets::initConnection()
{
//    connect(pageMain->boxPagePreviewLyric->extendButton, &QPushButton::clicked, [=](){
//        switchPage(0,1);
//    });

//    connect(pageLyricList->boxPagePreviewLyric->extendButton, &QPushButton::clicked, [=](){
//        switchPage(2,0);
//        switchPage(0,1);
//    });

    connect(pagePreviewLyric->btnPackupLyricBox, &QPushButton::clicked,[=](){
        switchPage(1,0);
    });

    connect(&animationPreviewExtend, &QPropertyAnimation::finished, this, &middleWidgets::geometryAnimationFinish);
    connect(&animationSettingExtend, &QPropertyAnimation::finished, this, &middleWidgets::geometryAnimationFinish);

}


void middleWidgets::initAnimation()
{
    //由于一个动画对象不能同时驱动2个动画，所以每个页面对应一个动画对象
    animationPreviewExtend.setPropertyName("geometry");
    animationSettingExtend.setPropertyName("geometry");

    nRuningAnimationCount = 0;
}


void middleWidgets::AnimateFromRectToRect(QPropertyAnimation& animation, QWidget* widget, QRect fromRect, QRect toRect)
{
    nRuningAnimationCount ++;
    widget->raise();
    animation.setDuration(100 * nRuningAnimationCount); //同时多个动画时，后面的动画时间间隔100加长
    animation.setTargetObject(widget);
    animation.setStartValue(fromRect);
    animation.setEndValue(toRect);
    animation.start();
}

middleWidgetLeft *middleWidgets::GetLeftWid()
{
    return pageMain->m_leftWid;
}

void middleWidgets::switchPage(int from, int to)
{
    if(from == 0 && to == 1)
    {
        MainWindow *mainwindow = MainWindow::GetInstance();
        QPushButton *btn_bottom = MainWindow::GetInstance()->getBottomButton();
        QPoint pt = btn_bottom->pos();
        QPoint GlobalPoint(btn_bottom->mapTo(mainwindow,pt));//获取控件在窗体中的坐标

        QRect previewBoxRect = btn_bottom->geometry();
        previewBoxRect = previewBoxRect.translated(GlobalPoint);

        if(currentPage==1)  //点击底部按钮可实现显示与隐藏
        {
            AnimateFromRectToRect(animationPreviewExtend,pagePreviewLyric,
                                  QRect(0,0,mainwindow->width(),mainwindow->height()),previewBoxRect);
            currentPage = from;
            return;
        }
        else
        {
            AnimateFromRectToRect(animationPreviewExtend,pagePreviewLyric,
                                  previewBoxRect,QRect(0,0,mainwindow->width(),mainwindow->height()));
        }

    }

    if(from == 1 && to == 0)
    {
        MainWindow *mainwindow = MainWindow::GetInstance();
        QPushButton *btn_bottom = MainWindow::GetInstance()->getBottomButton();
        QPoint pt = btn_bottom->pos();
        QPoint GlobalPoint(btn_bottom->mapTo(mainwindow,pt));//获取控件在窗体中的坐标

        QRect previewBoxRect = btn_bottom->geometry();
        previewBoxRect = previewBoxRect.translated(GlobalPoint);

        AnimateFromRectToRect(animationPreviewExtend,pagePreviewLyric,
                              QRect(0,0,mainwindow->width(),mainwindow->height()),previewBoxRect);

    }
    currentPage = to;
}

void middleWidgets::geometryAnimationFinish()
{
    switch(currentPage)
    {
    case 0: pageMain->raise();   break;
    case 1: pagePreviewLyric->raise();   break;
    case 2:
        pageMain->raise();      //由于setting出现前可能会有1、2页面存在，其动画目标（currentPage）为 0，
                                //  而在currentPage 被setting 页面改变为4时，pageMain->raise()不生效
//        pageSetting->raise();
        break;
    }


    nRuningAnimationCount--;
}

void middleWidgets::onReloadMusic(QString musicFileNamePath)
{
    QFileInfo fileinfo(musicFileNamePath);
    onSetMusicTitle(fileinfo.baseName());
    onSetMusicArtist("");                   //重载时，歌手未知

    pagePreviewLyric->setToDefaultAlbumImage();
}

void middleWidgets::onSetMusicTitle(QString title)
{
    pagePreviewLyric->setMusicTitle(title);
}

void middleWidgets::onSetMusicArtist(QString artist)
{
    pagePreviewLyric->setMusicSinger(artist);
}

void middleWidgets::onSetMusicAlbum(QString album)
{
    pagePreviewLyric->setMusicAlbum(album);
}

void middleWidgets::onSetMusicLyricPath(QString path)
{
    pagePreviewLyric->setLyricPath(path);
}

void middleWidgets::onSetAlbumImage(QPixmap pixmap)
{
    pagePreviewLyric->AlbumImageChanged(pixmap);
}

void middleWidgets::onSetPagePreviewOriginStyle()
{
    pagePreviewLyric->lyricViewer->setOriginStyle();
    pagePreviewLyric->phonagraph->setOriginStyle();
}

void middleWidgets::resizeEvent(QResizeEvent *event)
{
    pageMain->setGeometry(0,0,this->width(),this->height());
    pagePreviewLyric->setGeometry(0,0,this->width(),this->height());
//    pageSetting->setGeometry(0,0,this->width(),this->height());

    switch(currentPage)
    {
    case 0: pageMain->raise();   break;
    case 1: pagePreviewLyric->raise();   break;
//    case 2: pageSetting->raise();   break;
    }

    QWidget::resizeEvent(event);
}


