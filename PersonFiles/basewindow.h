#ifndef BASEWINDOW_H
#define BASEWINDOW_H


#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <qmath.h>
#include "AbsFrameLessAutoSize.h"

class mySkinWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mySkinWidget(QWidget*parent=0);

    const QString currentSkinPath(){return m_curPixPath;}

protected:
    virtual void paintEvent(QPaintEvent *);
public slots:
    void setSkin(const QString &str);
private:
    QString m_curPixPath;
    QPixmap m_skinPic;
    QPixmap m_curPix;

};


class baseWindow : public AbsFrameLessAutoSize
{
    Q_OBJECT
public:
    explicit baseWindow(QWidget *parent = 0);
    mySkinWidget m_mainwid;
protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // BASEWINDOW_H
