#ifndef MIDDLELEFTSTACKWIDGET0_H
#define MIDDLELEFTSTACKWIDGET0_H


#include "abstractmiddleleftstackwidget.h"

///本地音乐
class middleLeftStackWidget0 : public AbstractMiddleLeftStackWidget
{
    Q_OBJECT
public:
    explicit middleLeftStackWidget0(QWidget *parent);
    ~middleLeftStackWidget0(){}
    virtual void init();

    virtual void initConnection();

    playListWidget *getDefaultList(){return &m_defaultList;}

private:
    playListWidget m_defaultList;


};


#endif
