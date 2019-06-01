#ifndef ABSTRACTMIDDLELEFTSTACKWIDGET_H
#define ABSTRACTMIDDLELEFTSTACKWIDGET_H

#include "myscrollarea.h"
#include "middleconvienttwobutton.h"
#include "baseWidget.h"
#include "showTableButton.h"
#include "playListWidget.h"
#include <QVBoxLayout>


class AbstractMiddleLeftStackWidget : public myScrollArea
{
    Q_OBJECT
public:
    explicit AbstractMiddleLeftStackWidget(QWidget *parent);
    ~AbstractMiddleLeftStackWidget(){}

    virtual void init()=0;

    virtual void initConnection()=0;

    void initConvientWidget();

    void setAutoLayout();//设置m_wid的高度，以用于动态的显示滚动条

    void setOriginalStatus();//将当前播放列表置空

    /*for Internet*/
    //void addMusicToDefaultList(const ItemResult& ,bool bPlay);
    //void addMusicToList(const ItemResult&result,playListWidget*);

    baseWidget *GetWidget(){return &m_wid;}

    QVector<playListWidget*> & playListWidgetVector(){return m_Vector;}

    void releaseAllCrossWid();//释放所有playListWidget的cell

public Q_SLOTS:
    void slot_localSearch(const QString&);

    void scrolltoCurrentPlayList();

    void slot_verScrBarChange(int);

    /*for Internet*/
    //void slot_setlabelpic(const QString&strPath,const QString &songname);

    void slot_removePlayList();//删除列表

    void addPlayList(const QString&);

    void slot_addPlayListWithRename();


protected:
    virtual void resizeEvent(QResizeEvent *);
protected:
    baseWidget m_wid;
    QVector<playListWidget*> m_Vector;
    middleListSearch m_searchwid;
    middleConvientTwoButton m_convtwowid;
    QVBoxLayout m_vlyout;
};

#endif // ABSTRACTMIDDLELEFTSTACKWIDGET_H
