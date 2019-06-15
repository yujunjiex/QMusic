#ifndef MIDDLEWIDGETS_H
#define MIDDLEWIDGETS_H

#include <QObject>
#include <QWidget>
#include "baseWidget.h"
#include "middleWidgetLeft.h"
#include "middleWidgetRight.h"
#include "PageMain.h"
#include "PagePreviewLyric.h"


class middleWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit middleWidgets(QWidget *parent = 0);

    void initLayout();
    void initConnection();
    void initAnimation();

    void AnimateFromRectToRect(QPropertyAnimation& animation, QWidget* widget, QRect fromRect, QRect toRect);

    middleWidgetLeft* GetLeftWid();

public slots:
    void switchPage(int from, int to);
    void geometryAnimationFinish();

    void onReloadMusic(QString musicFileNamePath);  //当没有歌曲在播放列表中调用
    void onSetMusicTitle(QString title);
    void onSetMusicArtist(QString artist);
    void onSetMusicAlbum(QString album);
    void onSetMusicLyricPath(QString path);
    void onSetAlbumImage(QPixmap pixmap);

    void onSetPagePreviewOriginStyle();

    void playPhonagraph(){pagePreviewLyric->playPhonagraph();}
    void stopPhonagraph(){pagePreviewLyric->stopPhonagraph();}

protected:
    void mousePressEvent(QMouseEvent *){setFocus();}
    void mouseReleaseEvent(QMouseEvent *){}
    virtual void resizeEvent(QResizeEvent *event);

public:
    PageMain *pageMain;     //page0
    PagePreviewLyric *pagePreviewLyric;     //page1
    //PageSetting *pageSetting;     //page2

    int currentPage;    //标记当前页
private:
    QPropertyAnimation  animationPreviewExtend;
    QPropertyAnimation  animationSettingExtend;

    int nRuningAnimationCount;
};

#endif // MIDDLEWIDGETS_H
