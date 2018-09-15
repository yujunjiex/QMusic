#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include<QList>
#include<QMouseEvent>
#include<QTimer>
#include<QSlider>

//#include<myMediaList.h>
class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    myPushButton(QWidget*parent=0);
    myPushButton(const QString& str,QWidget*parent=0);
};
///////////////////////////////////////////////////////////////////
class volButton:public QPushButton
{
    Q_OBJECT
public:
    volButton(const QString& normal,const QString& hover,const QString& pressed,QWidget*parent=0);
    void setParentSlider(QSlider* slider){m_partnerslider=slider;}
protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
private:
    bool m_isenter;
    int m_savevol;
    int m_isvolempty;
    int m_index;
    QVector<QPixmap> m_listnormal;
    QVector<QPixmap> m_listhover;
    QVector<QPixmap> m_listpressed;

    QSlider *m_partnerslider;
public slots:
    void setButtonPixmap(int);//getFromSlider
signals:
    void setMute(int);
};

class volButton2:public QPushButton
{
    Q_OBJECT
public:
    volButton2(const QString& normal,const QString& hover,const QString& pressed,QWidget*parent=0);
    void setPartnerSlider(QSlider *slider){m_partnerslider=slider;}

    void startTimer(int interval){m_timer.start(interval);}

    void stopTimer(){m_timer.stop();}
    QTimer m_timer;
public slots:

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;

private:
    QSlider *m_partnerslider;
    bool m_isenter;
    int m_savevol;
    int m_isvolempty;
    int m_index;
    QVector<QPixmap> m_listnormal;
    QVector<QPixmap> m_listhover;
    QVector<QPixmap> m_listpressed;


public slots:
    void setButtonPixmap(int);//getFromSlider
signals:
    void setMute(int);
    void sig_hideVolWidget();
};

/////////////////////////////////////////////////////////////
class downloadButton:public QPushButton
{
    Q_OBJECT
public:
    downloadButton(const QString& normal,const QString& hover,const QString& pressed,QWidget*parent=0);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *e)override;

private:
    bool m_isenter;
    int m_index;
    QVector<QPixmap> m_listnormal;
    QVector<QPixmap> m_listhover;
    QVector<QPixmap> m_listpressed;

public slots:
    void setButtonPixmap(int);
signals:
    void sig_download();
};
////////////////////////////////////////////////////////////
class stackButton:public QPushButton
{
    Q_OBJECT
public:
    explicit stackButton(const QString& pixnormal,const QString& pixhover,const QString& pixsel,QWidget*parent);
    void setselected(bool=true);
protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
private:
    QPixmap m_pixnormal;
    QPixmap m_pixhover;
    QPixmap m_pixselected;

    int m_index;
    bool m_enter;
    bool m_pressed;
};







#endif // MYPUSHBUTTON_H
