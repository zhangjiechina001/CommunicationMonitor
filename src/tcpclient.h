#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QSemaphore>


class TcpClient :public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();

    //ICommunicationInit
    void SetCommunicationParam(QString communicationParam);
    QString GetCommunicationParam();
    bool Connect();
    bool IsConnected();
    void SetName(QString name);
    QString GetName();
    void Dispose();

    bool ConnectToHost();
    bool DisConnect();

    bool SendReply(QByteArray sendBuff,QByteArray &receiveBuff);
    bool SendNoReply(QByteArray sendBuff);

    QString GetClientName();

    static QString HexToString(QByteArray data);

signals:
    void OnSend(QString hex);
    void OnReceive(QString hex);

public slots:
    void reconnect();

    void OnDataReady();
private:
    QTcpSocket *_socket=nullptr;
    QString _name="";
    QString _ipPort="";
    QTimer* _timer=nullptr;
    bool _autoConnect=false;

};

#endif // TCPCLIENT_H
