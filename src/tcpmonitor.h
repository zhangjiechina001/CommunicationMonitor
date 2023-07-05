#pragma execution_character_set("utf-8")
#ifndef TCPMONITOR_H
#define TCPMONITOR_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QJsonObject>

class TCPMonitor : public QThread
{
    Q_OBJECT
public:
    explicit TCPMonitor(QObject *parent = nullptr);

    bool SetConfig(QJsonObject obj);

    void Pause();

    void Resume();

    void run() override;

    void WaitForEnd();

    void ExecuteSingle();

    static QJsonObject CreateDefault();
    
signals:

public slots:

private:
    QJsonObject _communicationList;
    bool _isRunning=true;
    int _interval=60;
    bool _isPause=false;
};

#endif // TCPMONITOR_H
