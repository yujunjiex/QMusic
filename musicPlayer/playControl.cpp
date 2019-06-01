#include "playControl.h"
#include "playListWidget/playListWidget.h"
#include "middleWidget/middlewidgetleft.h"
#include "mainWindows/mainwindow.h"


void PlayControl::slot_play(int index)
{
    playListWidget*pPlayList= playListWidget::getCurrentList();

    QUrl url= pPlayList->mediaList()->mediaUrl(index);
    if(!url.isEmpty())
    {
        MainWindow::GetInstance()->player()->setMedia(url.toString());
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
