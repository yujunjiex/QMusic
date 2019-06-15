#include "PagePreviewLyric.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ImageFilter.h"
#include "scaleUtil.h"

//参考：https://blog.csdn.net/caoshangpa/article/details/62421334

ThreadCalcBackgroundImage::~ThreadCalcBackgroundImage()
{
    // 请求终止
    requestInterruption();
    quit();
    wait();
}

void ThreadCalcBackgroundImage::run()
{
    // 是否请求终止
    while (!isInterruptionRequested())
    {
        bool bPicFound = false;
        QPixmap pixmapToDeal;

        {
            QMutexLocker locker(&m_mutex);
            if(!vecPic.empty())
            {
                bPicFound = true;
                pixmapToDeal = vecPic.back();
                vecPic.clear();
            }
        }
        // locker超出范围并释放互斥锁

        if(bPicFound)
        {
            QPixmap newPixmap = ImageFilter::BlurImage(pixmapToDeal, 50, 80);

            bPicFound = false;
            {
                QMutexLocker locker(&m_mutex);
                if(vecPic.empty())      //在没有新图片需要计算时才发出图片,保证发出的总是最后一次计算
                    emit(ready(newPixmap));
            }
            // locker超出范围并释放互斥锁
        }
        else
            msleep(2000);
    }
}

void ThreadCalcBackgroundImage::showPic(QPixmap pic)
{
    QMutexLocker locker(&m_mutex);
    vecPic.push_back(pic);
}

PagePreviewLyric::PagePreviewLyric(QWidget *parent):
QWidget(parent)
{
    this->setMouseTracking(true);//详见 BesFramelessWidget.h 注释

    initLayout();
    initEntity();
    initConnection();
    finishInit();
}

PagePreviewLyric::~PagePreviewLyric()
{

}

void PagePreviewLyric::initLayout()
{
    widgetMainPreview = new QWidget(this);
    widgetMainPreview->setObjectName("widgetMainPreview");
    widgetMainPreview->setMouseTracking(true);//详见 BesFramelessWidget.h 注释


    QHBoxLayout* hLayout = new QHBoxLayout(widgetMainPreview);
    hLayout->setMargin(0);
    phonagraph = new Phonograph(widgetMainPreview);
    phonagraph->setMinimumSize(480 * ScaleUtil::scale(),650* ScaleUtil::scale());
    phonagraph->setMaximumSize(480 * ScaleUtil::scale(),650* ScaleUtil::scale());
    phonagraph->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    lyricViewer = new LyricViewer(widgetMainPreview);
    lyricViewer->setMinimumSize(550* ScaleUtil::scale(),650* ScaleUtil::scale());
    lyricViewer->setMaximumSize(550* ScaleUtil::scale(),650* ScaleUtil::scale());
    lyricViewer->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QVBoxLayout * rightVlayout = new QVBoxLayout();
    rightVlayout->setMargin(20* ScaleUtil::scale());
    btnPackupLyricBox = new myPushButton(widgetMainPreview);
    btnPackupLyricBox->setObjectName("btnPackupLyricBox");
    btnPackupLyricBox->setMaximumSize(40* ScaleUtil::scale(),30* ScaleUtil::scale());
    btnPackupLyricBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    rightVlayout->addWidget(btnPackupLyricBox);
    rightVlayout->addSpacerItem(new QSpacerItem(50* ScaleUtil::scale(),50* ScaleUtil::scale(),QSizePolicy::Fixed,QSizePolicy::MinimumExpanding));

    hLayout->addSpacerItem(new QSpacerItem(20* ScaleUtil::scale(),20* ScaleUtil::scale(),QSizePolicy::MinimumExpanding,QSizePolicy::Fixed));
    hLayout->addWidget(phonagraph);
    hLayout->addWidget(lyricViewer);
    hLayout->addLayout(rightVlayout);
    hLayout->addSpacerItem(new QSpacerItem(20* ScaleUtil::scale(),20* ScaleUtil::scale(),QSizePolicy::MinimumExpanding,QSizePolicy::Fixed));


    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->setMargin(0);
    layoutMain->addWidget(widgetMainPreview);
    layoutMain->addSpacerItem(new QSpacerItem(20* ScaleUtil::scale(),20* ScaleUtil::scale(),QSizePolicy::Fixed,QSizePolicy::MinimumExpanding));
}

void PagePreviewLyric::initEntity()
{
    calPicThread = new ThreadCalcBackgroundImage(this);

    //初始化图片
    useBlackMask = false;
    blurbackgroudImage = QPixmap(":/playingwidget/images/playingwidget/default_preview_background.png");
    whiteMaskImage = QPixmap(":/playingwidget/images/playingwidget/album_background_white_mask.png");
    blackMaskImage = QPixmap(":/playingwidget/images/playingwidget/album_background_black_mask.png");

//    btnPackupLyricBox->setStyleSheet("QPushButton{image: url(:/playingwidget/images/playingwidget/btn_pack_back_to_box_black.png);}");
    btnPackupLyricBox->setStyleSheet("QPushButton{image:url(:/playingwidget/images/playingwidget/btn_pack_back_to_box_white.png);"
                                     "border:1px solid rgba(33, 33, 33, 33);"
                                     "border-radius:5px;"
                                     "width: "+QString::number(42 * ScaleUtil::scale())+"px;"
                                     "height:"+QString::number(32 * ScaleUtil::scale())+"px;"
                                     "padding:0px;"
                                     "color:#202020;"
                                     "background:rgba(255, 255, 255, 200);}"
                                     "QPushButton:hover{"
                                     "color: #000000;"
                                     "background:rgba(240, 240, 240, 200);"
                                     "}");
    //+QString::number(32 * ScaleUtil::scale())
}

void PagePreviewLyric::initConnection()
{
    connect(calPicThread, &ThreadCalcBackgroundImage::ready, this, &PagePreviewLyric::setNewBackgroundPixmap);
}

void PagePreviewLyric::finishInit()
{
    calPicThread->start(QThread::Priority::HighPriority);
}

void PagePreviewLyric::calcNewBackgroundImage(QPixmap pixmap)
{
    calPicThread->showPic(pixmap);
}

//设置是否使用黑色mask图层
void PagePreviewLyric::setWheterToUseBlackMask(bool useBlack)
{
    if(useBlackMask != useBlack)
    {
        useBlackMask = useBlack;
        update();
    }
}

void PagePreviewLyric::playPhonagraph()
{
    phonagraph->play();
}

void PagePreviewLyric::stopPhonagraph()
{
    phonagraph->stop();
}

void PagePreviewLyric::AlbumImageChanged(QPixmap newPixmap)
{
    phonagraph->setAlbumCover(QPixmap(newPixmap));
    calcNewBackgroundImage(QPixmap(newPixmap));
}

void PagePreviewLyric::setToDefaultAlbumImage()
{
    //不要每次都计算了，直接使用预定义的图片
    //AlbumImageChanged(QPixmap(":/resource/image/AlbumCover1.jpg"));

    phonagraph->setAlbumCover(QPixmap(":/playingwidget/images/playingwidget/AlbumCover1.jpg"));
    setNewBackgroundPixmap(QPixmap(":/playingwidget/images/playingwidget/default_preview_background.png"));
}

void PagePreviewLyric::setMusicTitle(QString title)
{
    lyricViewer->setMusicTitle(title);
}

void PagePreviewLyric::setMusicAlbum(QString album)
{
    lyricViewer->setMusicAlbum(album);
}

void PagePreviewLyric::setMusicSinger(QString singer)
{
    lyricViewer->setMusicSinger(singer);
}

void PagePreviewLyric::setLyricPath(QString path)
{
    lyricViewer->setLyricPath(path);
}


void PagePreviewLyric::setNewBackgroundPixmap(QPixmap newPixmap)
{
    blurbackgroudImage = newPixmap;
    update();
}


void PagePreviewLyric::mousePressEvent(QMouseEvent* event)
{
     QWidget::mousePressEvent(event);
}

void PagePreviewLyric::paintEvent(QPaintEvent* event)
{
    QPixmap maskLayer;
    if(useBlackMask)
        maskLayer = blackMaskImage;
    else
        maskLayer = whiteMaskImage;

    QPainter painter(this);

    QRect outerRect(0,0,this->width()-1,this->height()-1);
    painter.fillRect(outerRect, QBrush("#ffffff"));                   //绘制背景颜色
    QWidget::paintEvent(event);

    QSize windowSize = this->size();

    QSize halfSize = blurbackgroudImage.size();
    halfSize.setHeight(halfSize.height()*2.5/4);
    QPixmap half =  blurbackgroudImage.scaled(halfSize);  //高度先压缩为一半

    painter.drawPixmap(0,0,half.scaled(windowSize,Qt::KeepAspectRatioByExpanding));
    painter.drawPixmap(0,0,maskLayer.scaled(windowSize));

}

