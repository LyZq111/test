#pragma once
#include <QObject>
#include <QUdpSocket>

class SendData : public QObject
{
    Q_OBJECT
public:
    explicit SendData(QObject* parent = nullptr);

signals:
    void finished();

public slots:
    void sendData();// 发送数据槽函数

private:
    QUdpSocket* udpSocket;
};