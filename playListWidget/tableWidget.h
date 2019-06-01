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

class AbstractMiddleLeftStackWidget;
class playListWidget;
class middleLeftStackWidget3;

class tableWidget : public QTableWidget
{
    Q_OBJECT

public:
     explicit tableWidget(QWidget *parent=0);
     void init();
     void initMenu();

     void ShowOrHideTipWid(bool);
     void setPlayingRow(int row);
     bool isPlaying(int row);

     bool isLoved(int row); //该行是否在喜欢列表中,row的默认值为m_playrow

/*pass the pointer*/
     void setTableFinal(playListWidget *f){m_finalWidget=f;}
     void setMiddleStackWidget(AbstractMiddleLeftStackWidget*p){m_middleftStack=p;}

/*other functions*/
     const QString getHoverDuration(){return m_text;}

     void setItem(int row, int column, QTableWidgetItem *item){QTableWidget::setItem(row,column,item);emit sig_RowCountChange();}
     void removeRow(int i){QTableWidget::removeRow(i);emit sig_RowCountChange();}

     void setAutoLayoutSize();
     void removeSong(int row,bool setAutoLayout=true);

     void setCrossWid(int,int);

     int currentSongIndex(){return m_playrow;}

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

     void slot_currentlovetrigger();//底部点击love按钮时

     void slot_btnloveclicked();//localMusic调用

     void slot_rowCountChanged();
     void slot_actplay();

     void slot_removeHoverRow();
     void slot_removeRow(); //菜单使用
     void slot_cellEnter(int,int);  //鼠标进入item

     void slot_doublick(int r,int c);
     void slot_menuRequest(QPoint);
     void slot_moveToPList();//移动歌曲到歌单

signals:
     void sig_loveStatusChanged();

     void sig_play(int);
     void sig_doubleclicked();
     void sig_delIndex(int);

     void sig_addSong();

     void sig_RowCountChange();
private:
     int m_prebgItem;//当前鼠标所在行数(不需要选中)
     int m_loveNowRow;//其余列表在喜欢列表的index处  

     QString m_text;//歌曲时长

     bool isShowTipWid;
     addTipWidget m_addWid;
     QMenu m_menu;
     QMenu m_Addtoplistmenu;

     pushButtonCrossWidget *m_crossWid;
     pushButtonGroupWidget *m_groupWid;

     playListWidget *m_finalWidget;
     AbstractMiddleLeftStackWidget *m_middleftStack;
};


#endif
