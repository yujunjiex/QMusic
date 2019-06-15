#include "playControl.h"
#include "playListWidget/playListWidget.h"
#include "middleWidget/middleWidgetLeft.h"
#include "mainWindows/mainwindow.h"


void PlayControl::slot_play(int index)
{
    playListWidget*pPlayList= playListWidget::getCurrentList();

    QUrl url= pPlayList->mediaList()->mediaUrl(index);  //Netease的url不是真实链接,需要发送信号获取
    if (pPlayList->m_midleft->objectName()=="qqMusic")
    {
        QString coverUrl = pPlayList->mediaList()->coverUrl(index);
        emit pPlayList->m_midleft->sig_requestSongCover(coverUrl);
        emit pPlayList->m_midleft->sig_requestSongLyric(pPlayList->mediaList()->songID(index));
    }
    if(!url.isEmpty())
    {
        MainWindow::GetInstance()->player()->setMedia(url.toString());
//        MainWindow::GetInstance()->player()->setMedia("http://music.163.com/song/media/outer/url?id=347230.mp3");
//        MainWindow::GetInstance()->player()->setMedia("https://v1.itooi.cn/tencent/url?id=000EIzeR3yqAGP");

//        MainWindow::GetInstance()->player()->play();
        MainWindow::GetInstance()->player()->reload();
    }
}

void PlayControl::slot_endOfMedia()
{
   playListWidget*pPlayList= playListWidget::getCurrentList();
   if(!pPlayList)
       return;

   int index= pPlayList->mediaList()->nextMediaIndex();
   pPlayList->m_table.slot_doublick(index,0);
}

void PlayControl::slot_btnnextSong()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;
    int index= pPlayList->mediaList()->nextMediaIndex();
    pPlayList->m_table.slot_doublick(index,0);

//    pPlayList->m_table.setPlayingRow(currentIndex);
//    pPlayList->m_table.setCrossWid(currentIndex,0);

}

void PlayControl::slot_btnpreSong()
{
    playListWidget*pPlayList= playListWidget::getCurrentList();
    if(!pPlayList)
        return;
    int index= pPlayList->mediaList()->preMediaIndex();
    pPlayList->m_table.slot_doublick(index,0);
}
