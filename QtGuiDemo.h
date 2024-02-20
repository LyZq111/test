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
	virtual ~QtGuiDemo(); // 注意这里的析构函数被声明为虚函数

private slots:
	void on_SendStatusInfoPButton_clicked(); // 发送数据的槽函数
	void processdata();// 接收数据槽函数
	void processdataAnotherIP(); //接收并处理来自另一个IP的数据
	void saveLogFinished(); // 保存日志的槽函数

private:
	Ui::QtGuiDemoClass ui;
	QPushButton* SendStatusInfoPButton;
	QUdpSocket* socket1; // 吴翀socket对象
	QUdpSocket* socket2; // 芮兴超socket对象

	

};
