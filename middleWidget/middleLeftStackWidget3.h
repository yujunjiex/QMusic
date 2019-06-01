#ifndef MIDDLELEFTSTACKWIDGET3_H
#define MIDDLELEFTSTACKWIDGET3_H

#include "abstractmiddleleftstackwidget.h"

///我的最爱
class middleLeftStackWidget3:public AbstractMiddleLeftStackWidget
{  
    Q_OBJECT
public:
    explicit middleLeftStackWidget3(QWidget *parent);
    ~middleLeftStackWidget3(){}
    virtual void init();

    virtual void initConnection();

    static playListWidget *getLoveList(){return m_lovedList;}

public:
    static playListWidget *m_lovedList;
};

#endif // MIDDLELEFTSTACKWIDGET3_H
