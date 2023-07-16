#include <QTimer>
#include <QDebug>


#include "tcpclient.h"
#include "QThread"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    _socket=new QTcpSocket();
    _timer=new QTimer(this);
    _timer->setInterval(3*1000);
    connect(_timer,&QTimer::timeout,this,&TcpClient::reconnect);
    _timer->start();
    connect(_socket,&QTcpSocket::readyRead,this,&TcpClient::OnDataReady);
}

TcpClient::~TcpClient()
{
    Dispose();
}

void TcpClient::reconnect()
{
    if (_socket->state()!=QTcpSocket::SocketState::ConnectedState)
    {
        _socket->abort(); // 中止当前连接
        bool ret=ConnectToHost(); // 重新连接到服务器
//        qDebug() << "Reconnecting to server..."<<ret;
    }
}

void TcpClient::OnDataReady()
{
}


void TcpClient::SetCommunicationParam(QString communicationParam)
{
    _ipPort=communicationParam;
}

QString TcpClient::GetCommunicationParam()
{
    return _ipPort;
}

bool TcpClient::IsConnected()
{
    return _socket->state()==QAbstractSocket::SocketState::ConnectedState;
}

bool TcpClient::Connect()
{
    return ConnectToHost();
}

void TcpClient::SetName(QString name)
{
    _name=name;
}

QString TcpClient::GetName()
{
    return _name;
}

void TcpClient::Dispose()
{
    disconnect(_socket,&QTcpSocket::readyRead,this,&TcpClient::OnDataReady);
    _socket->abort();
    delete _socket;
}

bool TcpClient::ConnectToHost()
{
    QString hostaddr = _ipPort.split(":").at(0);
    QString strportID = _ipPort.split(":").at(1);
    _socket->connectToHost(hostaddr,strportID.toUShort());
    return _socket->waitForConnected(100);
}

bool TcpClient::DisConnect()
{
    return _socket->disconnect();
}

bool TcpClient::SendReply(QByteArray sendBuff, QByteArray &receiveBuff)
{
    _socket->readAll();
    int ret=_socket->write(sendBuff);
    _socket->waitForBytesWritten(100);
    OnSend(HexToString(sendBuff));
    if(ret!=sendBuff.size())
    {
        qDebug()<<__FUNCTION__<<__LINE__<<"write data error"<<_socket->errorString();
        return false;
    }

    QThread::msleep(50);
    if(_socket->waitForReadyRead(3*1000))
    {
        receiveBuff=_socket->readAll();
        emit OnReceive(HexToString(receiveBuff));
        return true;
    }
    else
    {
        qDebug() << __FUNCTION__ << __LINE__ << "waitForReadyRead timeout";
        return false;
    }
}

bool TcpClient::SendNoReply(QByteArray sendBuff)
{
    int ret=_socket->write(sendBuff);
    _socket->waitForBytesWritten(100);
    OnSend(HexToString(sendBuff));

    QThread::msleep(50);
    if(ret!=sendBuff.size())
    {
        qDebug()<<__FUNCTION__<<__LINE__<<"write data error"<<_socket->errorString();
        return false;
    }
    {
        return true;
    }
}

QString TcpClient::GetClientName()
{
    return _name;
}

QString TcpClient::HexToString(QByteArray data)
{
    QString hexString = data.toHex();
    QString formattedString;
    for (int i = 0; i < hexString.length(); i += 2) {
        formattedString +=  hexString.mid(i, 2) + " ";
    }
    return formattedString;
}
