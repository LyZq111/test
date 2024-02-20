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
    void sendData();// �������ݲۺ���

private:
    QUdpSocket* udpSocket;
};