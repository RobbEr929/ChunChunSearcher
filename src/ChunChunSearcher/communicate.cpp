#include "communicate.h"

Communicate::Communicate()
{
	manager = new QNetworkAccessManager(this);
}

Communicate::~Communicate()
{
	delete manager;
}

QByteArray Communicate::Get(QString url)
{
	QByteArray data;
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	QEventLoop eventloop;
	QTimer timer;
	timer.setInterval(5000);
	timer.setSingleShot(true);
	QNetworkReply* reply = manager->get(request);
	connect(&timer, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
	timer.start();
	eventloop.exec();
	if (!timer.isActive())
	{
		disconnect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
		reply->abort();
		reply->deleteLater();
		LOG(INFO) << QStringLiteral("连接超时");
		return data;
	}
	if (reply->error() != QNetworkReply::NoError)
	{
		reply->abort();
		reply->deleteLater();
		LOG(INFO) << QStringLiteral("连接错误") << reply->errorString();
		return data;
	}
	data = reply->readAll().mid(1);
	reply->abort();
	reply->deleteLater();
	return data;
}

QByteArray Communicate::Post(QString url, QString body)
{
	QByteArray data;
	QByteArray bodyData;
	bodyData.append(body);
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setHeader(QNetworkRequest::ContentLengthHeader, bodyData.length());
	QEventLoop eventloop;
	QTimer timer;
	timer.singleShot(4000, &eventloop, SLOT(quit()));
	timer.start();
	QNetworkReply* reply = manager->post(request, bodyData);
	QMetaObject::Connection conRet = QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
	Q_ASSERT(conRet);
	eventloop.exec(QEventLoop::ExcludeUserInputEvents);
	if (!timer.isActive())
	{
		disconnect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
		reply->abort();
		reply->deleteLater();
		return data;
	}
	if (reply->error() != QNetworkReply::NoError)
	{
		reply->abort();
		reply->deleteLater();
		return data;
	}
	data = reply->readAll().mid(1);
	reply->abort();
	reply->deleteLater();
	return data;
}

void Communicate::AbleToOnline()
{
	if (!Configuration::OnlineEnable())
	{
		LOG(INFO) << QStringLiteral("本地模式");
		emit Online(false);
		return;
	}
	QByteArray data = Get("http://www.baidu.com");
	if (data.size() > 0)
		Online(true);
	else
		Online(false);
	return;
}

void Communicate::Sign()
{
	qDebug() << "Call Sign";
	QString url = Configuration::ServerAddress() % "sign?username=" % Configuration::Username() % "&password=" % Configuration::Password();
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code"))
			{
				if (obj.value("code").toInt() == 200)
				{
					emit SignRes(true);
					return;
				}
			}
		}
	}
	emit SignRes(false);
	return;
}

void Communicate::Register()
{
	qDebug() << "Call Register";
	QString url = Configuration::ServerAddress() % "register";
	QString body = "username=" % Configuration::Username() % "&password=" % Configuration::Password();
	QByteArray data = Post(url, body);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code"))
			{
				if (obj.value("code").toInt() == 200)
				{
					emit RegisterRes(true);
					return;
				}
			}
		}
	}
	emit RegisterRes(false);
	return;
}

void Communicate::GetConf()
{
	qDebug() << "Call GetConf";
	QString url = Configuration::ServerAddress() % "getconf?username=" % Configuration::Username() % "&password=" % Configuration::Password();
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200 && obj.contains("data"))
			{
				Configuration::SetCloudConf(obj.value("data").toString());
				emit GetConfRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("读取云端设置失败");
	emit GetConfRes(false);
	return;
}

void Communicate::WriteConf()
{
	qDebug() << "Call WriteConf";
	QString url = Configuration::ServerAddress() % "writeconf";
	QString confContent = Configuration::MetaString();
	QString body = "username=" % Configuration::Username() % "&password=" % Configuration::Password() % "&confcontent=" % confContent;
	QByteArray data = Post(url, body);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				emit WriteConfRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("写入云端设置失败");
	emit WriteConfRes(false);
	return;
}