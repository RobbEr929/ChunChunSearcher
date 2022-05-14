#include "myclient.h"

#include <QEventLoop>

MyClient::MyClient(QObject* parent, QHostAddress addr, int num) :
	QObject(parent),
	address(addr),
	port(num)
{
}

void MyClient::SetAddress(QString addr)
{
	address = addr;
}

void MyClient::SetListenPort(int num)
{
	port = num;
}

void MyClient::ConnectEvent()
{
	qDebug() << "Call ClientThread ConnectEvent";
	emit Connected();
}

void MyClient::SendOutMessage(QString str)
{
	qDebug() << "Call ClientThread SendOutMessage";
	if (!str.isEmpty())
	{
		client->write(str.toLocal8Bit());
	}
}

void MyClient::ReciveMessage()
{
	qDebug() << "Call ClientThread ReciveMessage";
	emit Message(QString::fromLocal8Bit(client->readAll()));
}

void MyClient::DisConnect()
{
	qDebug() << "Call ClientThread DisConnect";
	client->disconnectFromHost();
}

void MyClient::Error(QAbstractSocket::SocketError error)
{
	qDebug() << "Call ClientThread Error";
	switch (error)
	{
	case QAbstractSocket::RemoteHostClosedError:
	{
		qDebug() << "Call ClientThread RemoteHostClosedError";
		break;
	}
	default:
		break;
	}
}

void MyClient::Init()
{
	qDebug() << "Call ClientThread Init";
	LOG(INFO) << QStringLiteral("正在连接%1:%2").arg(address.toString()).arg(port);
	client = new QTcpSocket;
	client->connectToHost(address, port);

	connect(client, SIGNAL(connected()), this, SLOT(ConnectEvent()));
	connect(client, SIGNAL(readyRead()), this, SLOT(ReciveMessage()));
	connect(client, SIGNAL(disconnected()), this, SLOT(DisConnect()));
	connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error(QAbstractSocket::SocketError)));
}