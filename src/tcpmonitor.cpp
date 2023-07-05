#pragma execution_character_set("utf-8")
#include "tcpmonitor.h"
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
    for(auto key:_communicationList.keys())
    {
        if(!IPUtils::IsPortListening(_communicationList[key].toString()))
        {
            qDebug()<<key<<" "<<_communicationList[key].toString()<<"is close";
        }
    }
}

QJsonObject TCPMonitor::CreateDefault()
{
    QJsonObject obj{
        {"1间隔",60},
    };
    JsonUtils::LoadJsonObject("abc",obj);
    return obj;
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
