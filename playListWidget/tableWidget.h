#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>
#include <QMenu>
#include <QDesktopWidget>
#include <QPushButton>

#include "pushButtonWidget.h"
#include "addTipWidget.h"

class middleLeftStackWidget0;
class playListWidget;

class tableWidget : public QTableWidget
{
    Q_OBJECT

public:
     explicit tableWidget(QWidget *parent=0);
     void init();
     void initMenu();

     void setPlayingRow(int row);
     bool isPlaying(int row);

/*pass the pointer*/
     void setTableFinal(playListWidget *f){m_finalWidget=f;}
     void setMiddleStackWidget0(middleLeftStackWidget0*p){m_middleftStack0=p;}

/*other functions*/
     const QString getHoverDuration(){return m_text;}

     void setItem(int row, int column, QTableWidgetItem *item){QTableWidget::setItem(row,column,item);emit sig_RowCountChange();}
     void removeRow(int i){QTableWidget::removeRow(i);emit sig_RowCountChange();}

     void setAutoLayoutSize();
     void removeSong(int row,bool setAutoLayout=true);

     void setCrossWid(int,int);

     int m_playrow; //当前正在播放的row
     int m_preplayrow;
     bool m_enter;

protected:
    virtual  void resizeEvent(QResizeEvent*);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
    virtual void enterEvent(QEvent*e){QTableWidget::enterEvent(e);setCursor(Qt::ArrowCursor);}
    virtual void leaveEvent(QEvent *);
    virtual void wheelEvent(QWheelEvent *);

    virtual void mouseMoveEvent(QMouseEvent*);

public slots:

     /*待实现*/
     void slot_btnloveclicked();

     void slot_rowCountChanged();
     void slot_actplay();

     void slot_removeHoverRow();
     void slot_removeRow(); //菜单使用
     void slot_cellEnter(int,int);  //鼠标进入item

     void slot_doublick(int r,int c);
     void slot_menuRequest(QPoint);
     void slot_moveToPList();//移动歌曲到歌单

signals:
     void sig_setLoveState(bool);

     void sig_play(int);
     void sig_doublick();

     void sig_addSong();

     void sig_RowCountChange();
private:
     int m_prebgItem;//当前鼠标所在行数(不需要选中)
     int m_loveNowRow;//其余列表在喜欢列表的index处  

     QString m_text;//歌曲时长

     addTipWidget m_addWid;
     QMenu m_menu;
     QMenu m_Addtoplistmenu;

     pushButtonCrossWidget *m_crossWid;
     pushButtonGroupWidget *m_groupWid;

     playListWidget *m_finalWidget;
     middleLeftStackWidget0 *m_middleftStack0;
};


#endif
