#include "QtGuiDemo.h"
#include "SendData.h"
#include<QDebug>

QtGuiDemo::QtGuiDemo(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// ����UDP Socket
	socket1 = new QUdpSocket(this);
	socket2 = new QUdpSocket(this);

	// �󶨶˿ڲ�����
	socket1->bind(QHostAddress::Any,1234);
	socket2->bind(QHostAddress::Any,5678);

	// �����źŲۣ������ݽ��յ�ʱ���ô�����
	connect(socket1, &QUdpSocket::readyRead, this, &QtGuiDemo::processdata);
	connect(socket2, &QUdpSocket::readyRead, this, &QtGuiDemo::processdataAnotherIP);

}

QtGuiDemo::~QtGuiDemo() {

	delete socket1;
	delete socket2;
}
// �������ݵĲۺ���ʵ��
void QtGuiDemo::on_SendStatusInfoPButton_clicked() {
	//�����������ݵ��߳�
	QThread* dataSend = new QThread();
	SendData* senddata = new SendData();
	senddata->moveToThread(dataSend);

	// �����źŲ�
	connect(dataSend,&QThread::started,senddata,&SendData::sendData);
	connect(senddata,&SendData::finished,dataSend,&QThread::quit);
	connect(dataSend,&QThread::finished,dataSend,&QThread::deleteLater);
	connect(dataSend,&QThread::finished,senddata,&SendData::deleteLater);

	// �����߳�
	dataSend->start();
}

void QtGuiDemo::processdata() {
	while (socket1->hasPendingDatagrams()) {
		// ��ȡ���յ�������
		QByteArray datagram;
		datagram.resize(socket1->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		socket1->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		qDebug() << "YOYOYO" << endl;
		//�ڱ������ʾ����
		/*int row = ui->tableWidget->rowCount();s
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString(datagram)));
*/
		//�������ݵ���־
		MyLogger* logger = new MyLogger();
		connect(logger, &MyLogger::finished, logger, &MyLogger::deleteLater);
		connect(logger, &MyLogger::finished, this, &QtGuiDemo::saveLogFinished);
		QThread* logThread1 = new QThread();
		logger->moveToThread(logThread1);
		connect(logThread1, &QThread::started, logger, [=]() {
			logger->saveData(datagram, sender.toString(), senderPort);
			});
		connect(logger, &MyLogger::finished, logThread1, &QThread::quit);
		connect(logThread1, &QThread::finished, logThread1, &QThread::deleteLater);
		logThread1->start();
	}
}

void QtGuiDemo::processdataAnotherIP() {
	while (socket2->hasPendingDatagrams()) {
		// ��ȡ���յ�������
		QByteArray datagram;
		datagram.resize(socket2->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		socket2->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		qDebug() << "YEYEYE" << endl;
		//�ڱ������ʾ����
		/*int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString(datagram)));
*/
//�������ݵ���־
		MyLogger* logger = new MyLogger();
		connect(logger, &MyLogger::finished, logger, &MyLogger::deleteLater);
		connect(logger, &MyLogger::finished, this, &QtGuiDemo::saveLogFinished);
		QThread* logThread2 = new QThread();
		logger->moveToThread(logThread2);
		connect(logThread2, &QThread::started, logger, [=]() {
			logger->saveData(datagram, sender.toString(), senderPort);
			});
		connect(logger, &MyLogger::finished, logThread2, &QThread::quit);
		connect(logThread2, &QThread::finished, logThread2, &QThread::deleteLater);
		logThread2->start();
	}
}
void QtGuiDemo::saveLogFinished() {
	// ��־������Ĵ���
}