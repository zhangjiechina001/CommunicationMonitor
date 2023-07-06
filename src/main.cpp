#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/Config/monitor_screen_icon.png"));
    QApplication::setQuitOnLastWindowClosed(false);
    MainWindow w;
    w.show();

    return a.exec();
}
