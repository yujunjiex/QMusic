#ifndef PUSHBUTTONWIDGET_H
#define PUSHBUTTONWIDGET_H

#include <QWidget>
#include"myPushButton.h"
class pushButtonCrossWidget : public QWidget //播放状态
{
    Q_OBJECT
public:
    explicit pushButtonCrossWidget(QWidget *parent = 0);
    myPushButton m_btn;
signals:

public slots:

};


//////////////////////////////////////////////////////
class pushButtonGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit pushButtonGroupWidget(QWidget *parent = 0);
    void setLoved();
    inline bool isLoved(){return m_islove;}

    myPushButton m_btnLove;
    myPushButton m_btnDel;
signals:

public slots:
    void slot_btnloveclicked();
private:
    bool m_islove;
};


#endif
