#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "jsonutils.h"
#include "tcpmonitor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_chbIsMonitor_clicked(bool checked);

    void on_btnUpdateStatus_clicked();

private:
    Ui::MainWindow *ui;

    TCPMonitor *_monitor;

    void Log(QString log);
};

#endif // MAINWINDOW_H
