#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>

class myScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit myScrollArea(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *){setFocus();}
};

#endif // MYSCROLLAREA_H
