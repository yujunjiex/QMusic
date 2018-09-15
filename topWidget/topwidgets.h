#ifndef TOPWIDGETS_H
#define TOPWIDGETS_H

#include <QObject>
#include <QWidget>

#include <QLineEdit>
#include"baseWidget.h"
#include"myPushButton.h"
#include"topSearchTipsWidget.h"

class TopWidgets : public baseWidget
{

    Q_OBJECT
public:
    explicit TopWidgets(QWidget *parent = 0);
    void init();
    void searchFromLineEdit(const QString);

    myPushButton m_btnsetting;
    myPushButton m_btnskin;
    QLineEdit m_lineEdit;
    myPushButton *m_btnserch;
    myPushButton m_btnexit;
    myPushButton m_btnmini;

public slots:

    void slot_serTipsClick(QListWidgetItem*);

};

#endif // TOPWIDGETS_H
