#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QObject>

#include "tcpclient.h"
#include "tcpmonitor.h"

class TcpClientManager:public QObject
{
    Q_OBJECT
private:
    explicit TcpClientManager();
    TcpClientManager& operator=(const TcpClientManager&) = delete;
    QList<TcpClient*> _allClients;
    TCPMonitor *_monitor=nullptr;

public:
    static TcpClientManager& Instance();
    ~TcpClientManager();


};

#endif // TCPCLIENTMANAGER_H
