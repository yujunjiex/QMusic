#ifndef MIDDLELEFTSTACKWIDGET0_H
#define MIDDLELEFTSTACKWIDGET0_H


#include "myscrollarea.h"
#include "middleconvienttwobutton.h"
#include "baseWidget.h"
#include "showTableButton.h"
#include "playListWidget.h"
#include <QVBoxLayout>

class middleLeftStackWidget0 : public myScrollArea
{
    Q_OBJECT
public:
    explicit middleLeftStackWidget0(QWidget *parent);
    ~middleLeftStackWidget0(){}
    void init();

    void initConvientWidget();

    void initConnection();

    void setAutoLayout();

    void setOriginalStatus();

    /*for Internet*/
    //void addMusicToDefaultList(const ItemResult& ,bool bPlay);
    //void addMusicToList(const ItemResult&result,playListWidget*);

    baseWidget *GetWidget(){return &m_wid;}

    middleListSearch* middleListSearchs(){return &m_searchwid;}

    QVector<playListWidget*> & playListWidgetVector(){return m_Vector;}

    playListWidget *getDefaultList(){return &m_defaultList;}
public Q_SLOTS:
    void slot_localSearch(const QString&);

    void scrolltoCurrentPlayList();

    void slot_verScrBarChange(int);

    /*for Internet*/
    //void slot_setlabelpic(const QString&strPath,const QString &songname);

    void slot_removePlayList();//删除列表

    void addPlayList(const QString&);

    void slot_addPlayListWithRename();

    void slot_play(int);

    void slot_endOfMedia();

    void slot_btnnextSong();

    void slot_btnpreSong();
protected:
    virtual void resizeEvent(QResizeEvent *);
private:
    baseWidget m_wid;
    QVector<playListWidget*> m_Vector;
    middleListSearch m_searchwid;
    middleConvientTwoButton m_convtwowid;
    QVBoxLayout m_vlyout;
    playListWidget m_defaultList;


};


#endif
