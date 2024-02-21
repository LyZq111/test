#include <QObject>
#include "SendData.h"

SendData::SendData(QObject* parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

void SendData::sendData()
{
    // ��װ����
    QByteArray data;
    data.append("hello world");

    // ��������
    udpSocket->writeDatagram(data, QHostAddress("192.168.99.126"), 8080);

    // ��������ź�
    emit finished();
}