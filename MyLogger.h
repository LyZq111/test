#pragma once
#include <QObject>
#include <QString>
#include <QFile>

class MyLogger : public QObject
{
    Q_OBJECT
public:
    explicit MyLogger(QObject* parent = nullptr);

signals:
    void finished();

public slots:
    // �������ݵ���־��
    void saveData(const QByteArray& data,const QString& ipAddress ,const quint16& port);

private:
    QFile* logFile;

};