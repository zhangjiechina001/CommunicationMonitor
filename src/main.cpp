#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon("monitor_screen_icon.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
