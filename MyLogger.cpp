#include "mylogger.h"
#include <QDebug>
#include <QDateTime>
#include <QDebug>

MyLogger::MyLogger(QObject *parent) : QObject(parent)
{
	// ������־�ļ�
	QString logFileName = "log_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")+".txt";
	logFile = new QFile(logFileName);
	if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Error : �򲻿���־�ļ�";
	}
}

void MyLogger::saveData(const QByteArray& data, const QString& ipAddress, const quint16& port)
{
	// �����ݱ��浽��־�ļ��У�ʹ�� UTF-8 ����
	QTextStream out(logFile);
	out.setCodec("UTF-8");

	QString ipStr = ipAddress.toUtf8();
	quint16 portStr = port;
	QString dataStr = QString::fromUtf8(data);

	out << QStringLiteral("�յ�����IP ") << ipStr << QStringLiteral("�˿ں�Ϊ��") << portStr << QStringLiteral("������:") << dataStr << endl;
	qDebug() << QStringLiteral("�յ�����IP ") << ipStr << QStringLiteral("�˿ں�Ϊ��")<< portStr << QStringLiteral("������:") << dataStr << endl;
	emit finished();
}