#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QTimer>
#include "easylogging++.h"
class MyClient :public QObject
{
	Q_OBJECT
public:
	explicit MyClient(QObject* parent = nullptr, QHostAddress addr = QHostAddress::LocalHost, int num = 929);
	void SetAddress(QString addr);
	void SetListenPort(int num);

private slots:
	void Init();
	void ConnectEvent();
	void SendOutMessage(QString str);
	void ReciveMessage();
	void DisConnect();
	void Error(QAbstractSocket::SocketError);

signals:
	void Connected();
	void Closed();
	void Message(QString str);

private:
	QTcpSocket* client;
	QHostAddress address;
	int port;
};

#endif