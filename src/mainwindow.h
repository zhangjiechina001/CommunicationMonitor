#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <memory>

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

    void Log(QString log);

    void on_txtLog_destroyed();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    TCPMonitor *_monitor;

    QSystemTrayIcon  *trayIcon=nullptr;

    QSystemTrayIcon *CreateTrayIcon();
};

#endif // MAINWINDOW_H
