#include "QtGuiDemo.h"
#include "SendData.h"
#include<QDebug>

QtGuiDemo::QtGuiDemo(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// 创建UDP Socket
	socket1 = new QUdpSocket(this);
	socket2 = new QUdpSocket(this);

	// 绑定端口并监听
	socket1->bind(QHostAddress::Any,1234);
	socket2->bind(QHostAddress::Any,5678);

	// 连接信号槽，当数据接收到时调用处理函数
	connect(socket1, &QUdpSocket::readyRead, this, &QtGuiDemo::processdata);
	connect(socket2, &QUdpSocket::readyRead, this, &QtGuiDemo::processdataAnotherIP);

}

QtGuiDemo::~QtGuiDemo() {

	delete socket1;
	delete socket2;
}
// 发送数据的槽函数实现
void QtGuiDemo::on_SendStatusInfoPButton_clicked() {
	//创建发送数据的线程
	QThread* dataSend = new QThread();
	SendData* senddata = new SendData();
	senddata->moveToThread(dataSend);

	// 连接信号槽
	connect(dataSend,&QThread::started,senddata,&SendData::sendData);
	connect(senddata,&SendData::finished,dataSend,&QThread::quit);
	connect(dataSend,&QThread::finished,dataSend,&QThread::deleteLater);
	connect(dataSend,&QThread::finished,senddata,&SendData::deleteLater);

	// 启动线程
	dataSend->start();
}

void QtGuiDemo::processdata() {
	while (socket1->hasPendingDatagrams()) {
		// 读取接收到的数据
		QByteArray datagram;
		datagram.resize(socket1->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		socket1->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		qDebug() << "YOYOYO" << endl;
		//在表格中显示数据
		/*int row = ui->tableWidget->rowCount();s
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString(datagram)));
*/
		//保存数据到日志
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
		// 读取接收到的数据
		QByteArray datagram;
		datagram.resize(socket2->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		socket2->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		qDebug() << "YEYEYE" << endl;
		//在表格中显示数据
		/*int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString(datagram)));
*/
//保存数据到日志
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
	// 日志保存完的处理
}