#pragma execution_character_set("utf-8")
#ifndef IPUTILS_H
#define IPUTILS_H

#include <QUdpSocket>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>
#include <string>
#include <QString>
#include <QTcpSocket>

class IPUtils
{
public:
    IPUtils(){}

    static bool Ping(const QString& address)
    {
        QProcess process;
        QString command = "ping";
        QStringList args = {"-n", "1", "-w", "1000", address};
        process.start(command, args);
        process.waitForFinished();
        QTextCodec* pTextCodec = QTextCodec::codecForName("System");
        QByteArray output=process.readAllStandardOutput();
        QString str2 = GetCorrectUnicode(output);
         qDebug() << "Address" << str2 ;
        if (str2.contains("回复"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    static bool IsPortListening(const QString ipPort)
    {
        QString ip=ipPort.split(":").at(0);
        QString port=ipPort.split(":").at(1);
        return IsPortListening(ip,port.toInt());
    }

    static bool IsPortListening(const QString& ipAddress, quint16 port)
    {
        QTcpSocket socket;
        socket.connectToHost(ipAddress, port);
        bool connected = socket.waitForConnected(500); // 等待500ms连接成功

        if (connected) {
            // 连接成功，端口处于监听状态
            socket.disconnectFromHost();
            return true;
        } else {
            // 连接失败，端口未处于监听状态
            return false;
        }
    }

    static QString GetCorrectUnicode(const QByteArray &ba)
    {
        QTextCodec::ConverterState state;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
        if (state.invalidChars > 0)
        {
            text = QTextCodec::codecForName("GBK")->toUnicode(ba);
        }
        else
        {
            text = ba;
        }
        return text;
    }
    static bool IsIPAddress(const QString& ipAddress)
    {
        QHostAddress address(ipAddress);
        return address.protocol() == QAbstractSocket::IPv4Protocol;
    }
};

#endif // IPUTILS_H
