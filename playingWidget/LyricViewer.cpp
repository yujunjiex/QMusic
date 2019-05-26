#include "LyricViewer.h"

#include <QFileInfo>
#include <QRegExp>
#include <QMessageBox>
#include <QSpacerItem>
#include "LrcProcessor.h"
#include "ScaleUtil.h"

LyricViewer::LyricViewer(QWidget* parent):QWidget(parent)
{
    setMouseTracking(true);

    initEntity();
    initLayout();
    initConnection();
}


void LyricViewer::initEntity()
{
    lrcLyrics.clear();
    bIsLrcLyric = false;
    bIsLyricValid = false;
    bIsNeteaseLrcFormat = true;
}

void LyricViewer::initLayout()
{
    labelPreviewTitle = new QLabel(this);
    labelPreviewAlbumTip= new QLabel(this);
    labelPreviewSingerTip= new QLabel(this);
    labelPreviewTitle->setObjectName("labelPreviewTitle");
    labelPreviewAlbumTip->setObjectName("labelPreviewAlbumTip");
    labelPreviewSingerTip->setObjectName("labelPreviewSingerTip");
    labelPreviewTitle->setText("");
    labelPreviewAlbumTip->setText("专辑:");    //歌曲路径
    labelPreviewSingerTip->setText("歌手:"); //歌词路径

    labelPreviewAlbumTip->setMaximumSize(80,30 * ScaleUtil::mscale());
    labelPreviewSingerTip->setMaximumSize(80,30 * ScaleUtil::mscale());
    labelPreviewAlbumTip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelPreviewSingerTip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    labelPreviewAlbum = new QLabel(this);
    labelPreviewSinger = new QLabel(this);
    labelPreviewAlbum->setObjectName("labelPreviewAlbumPath");
    labelPreviewSinger->setObjectName("labelPreviewSingerPath");
    labelPreviewAlbum->setText("未知");
    labelPreviewSinger->setText("未知");

    labelPreviewAlbum->setAlignment(Qt::AlignLeft);
    labelPreviewSinger->setAlignment(Qt::AlignLeft);

    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(labelPreviewAlbumTip);
    hLayout1->addWidget(labelPreviewAlbum);

    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(labelPreviewSingerTip);
    hLayout2->addWidget(labelPreviewSinger);

    scrollLyricPanel = new ScrollLyricPanel(this);
    scrollLyricPanel->setObjectName("scrollLyricPanel");
    scrollLyricPanel->setMinimumSize(548* ScaleUtil::scale(),500* ScaleUtil::scale());
    scrollLyricPanel->setMaximumSize(548* ScaleUtil::scale(),500* ScaleUtil::scale());
    scrollLyricPanel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addSpacerItem(new QSpacerItem(10,10* ScaleUtil::scale(),QSizePolicy::Fixed,QSizePolicy::Fixed));
    vLayout->addWidget(labelPreviewTitle);
    vLayout->addSpacerItem(new QSpacerItem(10,10* ScaleUtil::scale(),QSizePolicy::Fixed,QSizePolicy::Fixed));
    vLayout->addLayout(hLayout1);
    vLayout->addSpacerItem(new QSpacerItem(10,5* ScaleUtil::scale(),QSizePolicy::Fixed,QSizePolicy::Fixed));
    vLayout->addLayout(hLayout2);
    vLayout->addSpacerItem(new QSpacerItem(10,10* ScaleUtil::scale(),QSizePolicy::Fixed,QSizePolicy::Fixed));
    vLayout->addWidget(scrollLyricPanel);

    this->setStyleSheet("QWidget{font-family:Microsoft YaHei ;}"
                        "QLabel#labelPreviewTitle{color:#000000;font-size:15pt;}"
                        "QLabel#labelPreviewAlbumTip, QLabel#labelPreviewSingerTip{color:#111111;"
                                                                                "font-size:10pt;}"
                        "QLabel#labelPreviewAlbumPath, QLabel#labelPreviewSingerPath{color:#000000;"
                                                                                  "font-size:10pt;}"
                        "QWidget#scrollLyricPanel"
                        "{"
                             "margin-right:10px;"
                             "border-right: 1px solid rgba(100,100,100,25%);"
                        "}");
}

void LyricViewer::initConnection()
{



}

//歌词是否有效(路径不存在或者为空都是无效)
bool  LyricViewer::isLyricValid()
{
    return bIsLyricValid;
}

//歌词是否是LRC歌词
bool LyricViewer::isLrcLyric()
{
    return bIsLrcLyric;
}

void LyricViewer::setMusicTitle(QString title)
{
    labelPreviewTitle->setText(title);
    labelPreviewTitle->setToolTip(title);
}

void LyricViewer::setMusicAlbum(QString album)
{
    labelPreviewAlbum->setText(album);
    labelPreviewAlbum->setToolTip(album);
}

void LyricViewer::setMusicSinger(QString singer)
{
    labelPreviewSinger->setText(singer);
    labelPreviewSinger->setToolTip(singer);
}

void LyricViewer::setLyricPath(QString path)
{

    //使用该路径初始化歌词预览面板
    if(!loadLyricFromFile(path))
    {
        QMessageBox::information(NULL, tr("提示"),tr("打开载入lrc歌词时发生错误：")+path
                                   +"\n\n"+ tr("请注意是否歌词是否存在？"));

        lrcLyrics.clear();
        bIsLrcLyric = false;
    }
    scrollLyricPanel->updateLyric(lrcLyrics, bIsLrcLyric);
}

//设置空的歌词
void LyricViewer::setEmptyLyric()
{
    labelPreviewSinger->setText(tr("无"));

    lrcLyrics.clear();
    scrollLyricPanel->updateLyric(lrcLyrics, true);

    bIsLyricValid = false;
}


void LyricViewer::skinNameChanged(QString skinName)
{
    if(skinName == "black")
        scrollLyricPanel->lyricPanel->switchColor(true);
    else
       scrollLyricPanel->lyricPanel->switchColor(false);
}


bool LyricViewer::loadLyricFromFile(QString lyricPath)
{
    LrcProcessor lrcProcessor;

    if(!lrcProcessor.LoadFromFile(lyricPath))
    {
        return false;
    }
    else
    {
        lrcLyrics = lrcProcessor.GetLrcLyric();

        bIsLyricValid = lrcProcessor.bIsLrcLyric;
        bIsLrcLyric = lrcProcessor.bIsLrcLyric;
        bIsNeteaseLrcFormat = lrcProcessor.bIsNeteaseLrcFormat;
    }

    return true;
}

