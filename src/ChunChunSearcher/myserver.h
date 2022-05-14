#ifndef SEVER_H
#define SEVER_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QObject>
#include <QList>
#include <QStringBuilder>
#include "easylogging++.h"
class MyServer : public QObject
{
	Q_OBJECT
public:
	explicit MyServer(QObject* parent = nullptr);
	void SetListenPort(unsigned int num);
	int NowConnectNum() const;

public slots:
	void Init();
	void Close();

private slots:
	void NewConnection();
	void ReadMessage();
	void Error(QAbstractSocket::SocketError);

signals:
	void InitRes(bool res);
	void CloseRes(bool res);
	void ReciveData(QString str);
	void ConnectChanged();

private:
	QTcpServer* server;
	QList<QTcpSocket*> sockets;
	unsigned int port;
};
#endif