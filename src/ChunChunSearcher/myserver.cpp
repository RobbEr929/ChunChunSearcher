#include "myserver.h"

MyServer::MyServer(QObject* parent) :QObject(parent)
{
}

void MyServer::SetListenPort(unsigned int num)
{
	port = num;
}

int MyServer::NowConnectNum() const
{
	return sockets.size();
}

void MyServer::Close()
{
	qDebug() << "Call ServerThread Close";
	LOG(INFO) << QStringLiteral("�رշ�����");
	QString closeMsg = QStringLiteral("�����������رգ����Ӽ����Ͽ�");
	for (auto& i : sockets)
	{
		i->write(closeMsg.toStdString().data());
		i->close();
		i->deleteLater();
	}
	sockets.clear();
	server->close();
	server->deleteLater();
	emit CloseRes(true);
}

void MyServer::Init()
{
	qDebug() << "Call ServerThread Init";
	LOG(INFO) << QStringLiteral("��������ʼ��");
	server = new QTcpServer(this);
	if (server->listen(QHostAddress::Any, port))
	{
		LOG(INFO) << QStringLiteral("���� localhost:%1 �ɹ�").arg(port);
		connect(server, SIGNAL(newConnection()), this, SLOT(NewConnection()));
		emit InitRes(true);
	}
	else
	{
		LOG(INFO) << QStringLiteral("���� localhost:%1 ʧ��").arg(port);
		emit InitRes(false);
	}
}

void MyServer::NewConnection()
{
	qDebug() << "Call ServerThread NewConnection";
	QTcpSocket* socket = server->nextPendingConnection();
	sockets.push_back(socket);
	connect(socket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error(QAbstractSocket::SocketError)));
	LOG(INFO) << QStringLiteral("���������� %1").arg(socket->QAbstractSocket::peerAddress().toString());
	emit ConnectChanged();
	emit ReciveData(QStringLiteral("���������� %1").arg(socket->QAbstractSocket::peerAddress().toString()));
}

void MyServer::ReadMessage()
{
	qDebug() << "Call ServerThread ReadMessage";
	QTcpSocket* socket = (QTcpSocket*)QObject::sender();
	QString data = socket->QAbstractSocket::peerAddress().toString() % ":" % QString::fromLocal8Bit(socket->readAll());
	LOG(INFO) << data;
	emit ReciveData(data);
	for (auto& i : sockets)
	{
		i->write(data.toLocal8Bit());
	}
}
void MyServer::Error(QAbstractSocket::SocketError)
{
	qDebug() << "Call ServerThread Error";
	QTcpSocket* socket = (QTcpSocket*)QObject::sender();
	int error = socket->error();
	switch (error)
	{
	case QAbstractSocket::RemoteHostClosedError:
	{
		QString hostAddress = socket->QAbstractSocket::peerAddress().toString();
		auto i = sockets.begin();
		for (; i != sockets.end(); ++i)
		{
			if (*i == socket)
				break;
		}
		socket->close();
		sockets.erase(i);
		for (auto& i : sockets)
		{
			i->write(QStringLiteral("%1 �Ѿ��Ͽ�����").arg(hostAddress).toStdString().data());
		}
		emit ConnectChanged();
		emit ReciveData(QStringLiteral("%1 �Ѿ��Ͽ�����").arg(hostAddress).toStdString().data());
		LOG(INFO) << QStringLiteral("%1 �Ѿ��Ͽ�����").arg(hostAddress);
		break;
	}
	default:
		break;
	}
}