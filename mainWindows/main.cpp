#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include "singleApplication/qsingleapplication.h"

int main(int argc, char *argv[])
{
    QSingleApplication a(argc, argv);
    if(!a.isRunning())
    {

        a.setStyleSheet("QMenu{background-color: white;border: 1px solid rgb(214,214,214);}"
                        "QMenu::item{height: 28px;padding: 0px 20px 0px 40px;font-size : 12px;color: rgb(102, 102, 102);font-family: 微软雅黑;}"
                        "QMenu::item:focus{padding: -1;}"
                        "QMenu::item:!enabled{color:rgb(150,150,150);}"
                        "QMenu::item:selected{color: white;background-color: rgb(22, 154, 243);}"
                        "QMenu::icon{position: absolute;left: 12px;}"
                        "QMenu::separator{height:1px;background: rgb(209,209,209);margin:4px 0px 4px 0px;}"
                        "QPushButton:focus{padding: -1;}"
                        "QLabel:focus{padding: -1;}");

        MainWindow *w=MainWindow::InitInstance();
        a.w=w;
        double x,y;
        int currentScreenWid = QApplication::desktop()->width();
        int currentScreenHei  = QApplication::desktop()->height();
        x = currentScreenWid/1920.0;
        y = currentScreenHei/1080.0;

        w->show();
        w->setGeometry((QApplication::desktop()->width() - w->width())/2,(QApplication::desktop()->height() - w->height())/2,1320*x,850*y);//居中显示
        return a.exec();
    }
    return 0;
}
