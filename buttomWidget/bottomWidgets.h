#ifndef BOTTOMWIDGETS_H
#define BOTTOMWIDGETS_H

#include <QObject>
#include <QWidget>
#include<QLabel>

#include"baseWidget.h"
#include"myPushButton.h"
#include"mySlider.h"
#include"TextMovingWidget.h"


class bottomWidgets : public baseWidget
{
    Q_OBJECT
public:
    explicit bottomWidgets(QWidget *parent = 0);

    void init();

    void initConnect();

    void setPauseStyle();

    void setPlayStyle();

    void setBufferStyle();

    void setRandomStyle();
    void setInOrderStyle();
    void setOneCycleStyle();

    void setSongName(const QString&str){ m_labnowPlayname.setText(QString("正在播放: ")+QString(str));}

    void setPicture(const QString&url);

    myPushButton m_btnprevious;
    myPushButton m_btnPlay;
    myPushButton m_btnnext;
    volButton2 m_btnvol;
    myPushButton m_btnplaylist;

    myPushButton m_btnfavorite;
    myPushButton m_btnplaymode;
    downloadButton m_btndownload;

    myPushButton m_btnpicture;
    mySlider m_mainslider;
    QLabel m_labposition;
    TextMovingWidget m_labnowPlayname;

signals:
    void sig_showPlayingPanel();

public slots:

    /*mainslider*/
    void updateText(int position);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
private:
    QString Time(qint64 time);//转换时间


};

#endif // bottomWidgets_H
