#ifndef SHOWTABLEBUTTON_H
#define SHOWTABLEBUTTON_H


#include <QWidget>
#include "myPushButton.h"
#include <QLabel>
#include <QLineEdit>
#include <QMenu>

class playListWidget;
class tableWidget;

class showTableButton:public QPushButton
{
    Q_OBJECT
public:
    explicit showTableButton(QWidget*parent=0);
    void init();
    void initMenu();

    void setTableFinal(playListWidget*parent);

    void setTableShowIndicator(bool bShow=true);

    void ShowOrHideMenu(bool isShow=true);

    void ShowOrHideCoverMenu(bool isShow=true);

    void setEnabledMenuItem(bool isSetting=false);

    void setListName(const QString&strText){m_playlistName.setText(strText);}

    QString getListName(){return m_playlistName.text().split("[").value(0);}

    void setCoverimg(QString strPath){m_cover.setIcon(QPixmap(strPath).scaled(70,70));}

public slots:
    void slot_updateSongCount();

    void slot_returnPressed();
    void slot_ReName();
   // void slot_reNameDB(const QString&);


signals:
    void sig_emptyList();
    void sig_addPlayList();
    void sig_addSong();
    void sig_delPlayList();
    void sig_reName(const QString&);

    /*for cover*/
    void sig_fixedCover();
    void sig_unfixedCover();
    void sig_selectCover();
protected:

    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual bool eventFilter(QObject *, QEvent *);

private:
    QLabel m_indicator;
    QMenu  m_menu;
    QMenu  m_cover;
    QLineEdit m_lineEdit;
    playListWidget *m_finalWid;
    QLabel m_playlistName;
    myPushButton m_btncover; //列表封面 70*70
//    bool m_iscover;

    bool isShowMenu;
    bool isShowCoverMenu;
};

#endif
