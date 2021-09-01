<<<<<<< HEAD
#include "widget.h"
#include <clientwidget.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   Widget w;
   w.show();
    // ClientWidget cw;
    // cw.show();
    return a.exec();
}
=======
#include "widget.h"
#include "serialsender.h"
#include "serialreceiver.h"
#include "widgetselect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //选择界面
    WidgetSelect *widgetSelect = new WidgetSelect( );
    widgetSelect->resize(1200,900);
    widgetSelect->setWindowTitle("“救救我”无人值守监控系统");
    widgetSelect->setStyleSheet("{image: url(:./picture/background.jpg);}");//背景图
    widgetSelect->show();

    return a.exec();
}
>>>>>>> tmp
