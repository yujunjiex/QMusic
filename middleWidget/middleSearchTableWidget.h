#ifndef MIDDLESEARCHTABLEWIDGET_H
#define MIDDLESEARCHTABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QTableWidget>
#include "baseWidget.h"
#include "myPushButton.h"
#include "playListWidget/playListWidget.h"
#include "netWork/structs.h"

class tableCellWidget:public baseWidget
{
    Q_OBJECT
public:
   explicit tableCellWidget(QWidget*p=0);
    ~tableCellWidget(){}

   void init();
   myPushButton m_btntableplay;
   myPushButton m_btntableadd;
};


///可用作搜索窗口部件和歌单详情部件
class middleSearchTableWidget:public QTableWidget
{
    Q_OBJECT
public:
   explicit middleSearchTableWidget(QWidget*p=0);
   void init();
   void setItem(int row, int column, QTableWidgetItem *item);//add checkbox for column 0
   void removeRow(int row);
   void appendRow(int row, const ItemResult &item);
signals:
   void sig_doubleclicked(const QStringList&,const QStringList&,const QStringList&);
protected:
   virtual void leaveEvent(QEvent *);

public slots:
   void slot_tableContainerBtnClicked();
   void slot_playbtnclicked();
   void slot_addbtnclicked();

//   void slot_cellEnter(int row, int c);

   void slot_itemclick(int,int);

   void slot_doubleClicked(QTableWidgetItem*);
private:
    int m_prebgItem;
    playListWidget *m_plistwid;  //这里的歌单列表与界面耦合死了(没办法。)

};

#endif // MIDDLESEARCHTABLEWIDGET_H
