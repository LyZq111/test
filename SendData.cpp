#include <QObject>
#include "SendData.h"

SendData::SendData(QObject* parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

void SendData::sendData()
{
    // 封装数据
    QByteArray data;
    data.append("hello world");

    // 发送数据
    udpSocket->writeDatagram(data, QHostAddress("192.168.99.126"), 8080);

    // 发送完成信号
    emit finished();
}