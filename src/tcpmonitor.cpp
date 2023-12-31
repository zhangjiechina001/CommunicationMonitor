﻿#include "tcpmonitor.h"
#include <QDebug>
#include <QElapsedTimer>

#include "iputils.h"
#include "jsonutils.h"

TCPMonitor::TCPMonitor(QObject *parent) : QThread(parent)
{

}

bool TCPMonitor::SetConfig(QJsonObject obj)
{
    _communicationList=obj["Items"].toObject();

    for(auto key:_communicationList.keys())
    {
        QJsonObject obj=_communicationList[key].toObject();
        TcpClient *client=new TcpClient();
        client->SetName(key);
        client->SetCommunicationParam(obj["CommunicationParam"].toString());
        client->Connect();
        CommandTest testItem;
        testItem.Client=client;
        testItem.SendCommand=QByteArray::fromHex(obj["SendCommand"].toString().trimmed().toLatin1());
        _allcmd.append(testItem);
//        qDebug()<<key<<":"<<client->IsConnected()<<" "<<testItem.SendCommand;
    }
    _interval=obj["Interval"].toInt();
    return true;
}

void TCPMonitor::Pause()
{
    _isPause=true;
}

void TCPMonitor::Resume()
{
    _isPause=false;
}

void TCPMonitor::ExecuteSingle()
{
    qDebug()<<"---------- START ----------";
    for(const CommandTest &cmd:_allcmd)
    {
        QByteArray rec;

        if(!cmd.Client->SendReply(cmd.SendCommand,rec))
        {
            qCritical()<<cmd.Client->GetClientName()<<"测试失败！";
        }        
    }
    qDebug()<<"---------- END ----------";
}

void TCPMonitor::run()
{
    //这样设计的目的是为了在程序结束时减少等待时间,减少检查_isRunning标志的时间
    QElapsedTimer ela;
    ela.start();
    while(_isRunning)
    {
        //每60秒检查一次连通性
        QThread::msleep(100);
        if(_isPause)
        {
            continue;
        }

        if(ela.elapsed()>_interval*1000)
        {
            ExecuteSingle();
            ela.restart();
        }
    }
}

void TCPMonitor::WaitForEnd()
{
    _isRunning=false;
    wait();
}
