#ifndef ABSFRAMELESSAUTOSIZE_H  //自动大小的无边框窗口
#define ABSFRAMELESSAUTOSIZE_H

#include <QWidget>
#include <QMouseEvent>

enum CursorPos{Default,Right,Left,Bottom,Top,TopRight,TopLeft,BottomRight,BottomLeft};
struct pressWindowsState
{
    bool    MousePressed;
    bool   IsPressBorder;
    QPoint  MousePos;
    QPoint  WindowPos;
    QSize PressedSize;
};

class AbsFrameLessAutoSize : public QWidget
{
    Q_OBJECT
public:
    AbsFrameLessAutoSize(QWidget *parent = 0);
    virtual~AbsFrameLessAutoSize(){}
    void setBorder(int border);
    void mouseMoveRect(const QPoint &p);
    virtual void mouseMoveEvent(QMouseEvent *event); //交给别个调用
protected:

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    pressWindowsState m_state;
    int m_border;
    CursorPos m_curPos;
};

#endif // ABSFRAMELESSAUTOSIZE_H
