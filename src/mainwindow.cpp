#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->btnUpdateStatus->setChecked(true);
}

void MainWindow::Log(QString log)
{
    ui->txtLog->appendPlainText(log);

    if(ui->txtLog->document()->lineCount()>500)
    {
        ui->txtLog->document()->clear();
    }
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
