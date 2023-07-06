#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "Log/logger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qInstallMessageHandler(Logger::CustomMessageHandler);
    connect(&Logger::Instance(),SIGNAL(OnLogging(QString)),this,SLOT(Log(QString)),Qt::QueuedConnection);
    QJsonObject obj=TCPMonitor::CreateDefault();
    JsonUtils::LoadJsonObject("CommunicationManager",obj,false);
    _monitor=new TCPMonitor();
    _monitor->SetConfig(obj);
    _monitor->start();
    ui->chbIsMonitor->setChecked(true);
    trayIcon=CreateTrayIcon();
    trayIcon->show();
}

void MainWindow::Log(QString log)
{
    ui->txtLog->appendPlainText(log);

    if(ui->txtLog->document()->lineCount()>500)
    {
        ui->txtLog->document()->clear();
    }
}

QSystemTrayIcon *MainWindow::CreateTrayIcon()
{
    QMenu *trayIconMenu=new QMenu(this);
    QAction *minimizeAction = new QAction(tr("&Minimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);
    trayIconMenu->addAction(minimizeAction);

    QAction *restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    QAction *quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, this, [=]()
    {
        trayIcon->setVisible(false);
        this->close();
        qApp->quit();
        qDebug()<<"程序关闭!";
    });
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/Config/monitor_screen_icon.ico"));
    trayIcon->setToolTip("Tcp Monitor");
    return trayIcon;
}

MainWindow::~MainWindow()
{
    _monitor->WaitForEnd();
    _monitor->deleteLater();
    delete ui;
}

void MainWindow::on_chbIsMonitor_clicked(bool checked)
{
    if(checked)
    {
        _monitor->Resume();
    }
    else
    {
        _monitor->Pause();
    }
}

void MainWindow::on_btnUpdateStatus_clicked()
{
    _monitor->ExecuteSingle();
}

void MainWindow::on_txtLog_destroyed()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<__FUNCTION__<<__LINE__;
    if (trayIcon->isVisible())
    {
        qDebug()<<__FUNCTION__<<__LINE__;
        QIcon icon(":/Config/monitor_screen_icon.ico   ");
        qDebug()<<__FUNCTION__<<__LINE__;
        trayIcon->showMessage("warning", "Monitor Running!", icon,1000);
        qDebug()<<__FUNCTION__<<__LINE__;
        hide();
        event->ignore();
    }
}
