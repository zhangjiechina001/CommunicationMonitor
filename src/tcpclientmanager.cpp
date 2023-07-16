#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager()
{

}

TcpClientManager &TcpClientManager::Instance()
{
    static TcpClientManager _instance;
    return _instance;
}

TcpClientManager::~TcpClientManager()
{

}
