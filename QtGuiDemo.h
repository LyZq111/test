#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtGuiDemo.h"
#include <ui_QtGuiDemo.h>
#include <QUdpSocket>
#include <QThread>
#include "SendData.h"
#include "MyLogger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QtGuiDemo; }
QT_END_NAMESPACE

class QtGuiDemo : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiDemo(QWidget *parent = Q_NULLPTR);
	virtual ~QtGuiDemo(); // ע���������������������Ϊ�麯��

private slots:
	void on_SendStatusInfoPButton_clicked(); // �������ݵĲۺ���
	void processdata();// �������ݲۺ���
	void processdataAnotherIP(); //���ղ�����������һ��IP������
	void saveLogFinished(); // ������־�Ĳۺ���

private:
	Ui::QtGuiDemoClass ui;
	QPushButton* SendStatusInfoPButton;
	QUdpSocket* socket1; // ����socket����
	QUdpSocket* socket2; // ���˳�socket����

	

};
