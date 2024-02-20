#include "mylogger.h"
#include <QDebug>
#include <QDateTime>
#include <QDebug>

MyLogger::MyLogger(QObject *parent) : QObject(parent)
{
	// 创建日志文件
	QString logFileName = "log_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")+".txt";
	logFile = new QFile(logFileName);
	if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Error : 打不开日志文件";
	}
}

void MyLogger::saveData(const QByteArray& data, const QString& ipAddress, const quint16& port)
{
	// 将数据保存到日志文件中，使用 UTF-8 编码
	QTextStream out(logFile);
	out.setCodec("UTF-8");

	QString ipStr = ipAddress.toUtf8();
	quint16 portStr = port;
	QString dataStr = QString::fromUtf8(data);

	out << QStringLiteral("收到来自IP ") << ipStr << QStringLiteral("端口号为：") << portStr << QStringLiteral("的数据:") << dataStr << endl;
	qDebug() << QStringLiteral("收到来自IP ") << ipStr << QStringLiteral("端口号为：")<< portStr << QStringLiteral("的数据:") << dataStr << endl;
	emit finished();
}