#ifndef PLAYCONTROL_H
#define PLAYCONTROL_H

#include <QObject>

//播放控制类
class PlayControl : public QObject
{
    Q_OBJECT
public:
    explicit PlayControl(QObject *parent = 0):QObject(parent){}


public slots:
    static void slot_play(int);

    static void slot_endOfMedia();

    static void slot_btnnextSong();

    static void slot_btnpreSong();
};

#endif // PLAYCONTROL_H
