#include "communicate.h"

#include <QApplication>
#include <QTextCodec>

Communicate::Communicate()
{
	manager = new QNetworkAccessManager(this);
	manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
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

void Communicate::LoadError(QNetworkReply::NetworkError error)
{
	qDebug() << "Call CommunicateThread LoadError";
	emit TransmissionError(error);
}

void Communicate::LoadProgress(qint64 bytesSent, qint64 bytesTotal)
{
	emit LoadProgressRes(bytesSent, bytesTotal);
}

void Communicate::AbleToOnline()
{
	qDebug() << "Call CommunicateThread AbleToOnline";
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
	qDebug() << "Call CommunicateThread Sign";
	QString url = Configuration::ServerAddress() % "sign?username=" % Configuration::Username() % "&password=" % Configuration::Password();
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto ob = obj.value("data").toArray();
				Configuration::SetUserId(ob.at(0).toObject().value("userid").toInt());
				emit SignRes(true);
				return;
			}
		}
	}
	emit SignRes(false);
	return;
}

void Communicate::Register()
{
	qDebug() << "Call CommunicateThread Register";
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
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				emit RegisterRes(true);
				return;
			}
		}
	}
	emit RegisterRes(false);
	return;
}

void Communicate::GetConf()
{
	qDebug() << "Call CommunicateThread GetConf";
	QString url = Configuration::ServerAddress() % "getconf?userid=" % QString::number(Configuration::UserId());
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
				Configuration::SetCloudConf(obj.value("data").toArray().at(0).toString());
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
	qDebug() << "Call CommunicateThread WriteConf";
	QString url = Configuration::ServerAddress() % "writeconf";
	QString body = "userid=" % QString::number(Configuration::UserId()) % "&confcontent=" % Configuration::MetaString();
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

void Communicate::GetUserInfo()
{
	qDebug() << "Call CommunicateThread GetUserInfo";
	if (Configuration::UserId() == 0)
	{
		LOG(INFO) << QStringLiteral("读取个人信息失败");
		emit GetUserInfoRes(false);
		return;
	}
	QString url = Configuration::ServerAddress() % "getuserinfo?userid=" % QString::number(Configuration::UserId());
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toObject();
				Configuration::SetPower(data.value("power").toInt());
				Configuration::SetStatus(data.value("status").toInt());
				int organizationid = data.value("organizationid").toInt();
				Configuration::SetOrganizationId(organizationid);
				if (organizationid != 0)
				{
					Configuration::SetOrganizationName(data.value("organizationname").toString());
					Configuration::SetOrganizationStatus(data.value("organizationstatus").toInt());
				}
				emit GetUserInfoRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("读取个人信息失败");
	emit GetUserInfoRes(false);
	return;
}

void Communicate::LeaveOrganization(int id)
{
	qDebug() << "Call CommunicateThread LeaveOrganization";
	if (id == 0)
		id = Configuration::UserId();
	QString url = Configuration::ServerAddress() % "leaveorganization";
	QString body = "userid=" % QString::number(id);
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
				emit LeaveOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("离开组织失败");
	emit LeaveOrganizationRes(false);
	return;
}

void Communicate::ApplyJoinOrganization(int id)
{
	qDebug() << "Call CommunicateThread ApplyJoinOrganization";
	QString url = Configuration::ServerAddress() % "applyjoinorganization";
	QString confContent = Configuration::MetaString();
	QString body = "userid=" % QString::number(Configuration::UserId()) % "&organizationid=" % QString::number(id);
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
				emit ApplyJoinOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("申请加入组织失败");
	emit ApplyJoinOrganizationRes(false);
	return;
}

void Communicate::JoinOrganization(int id)
{
	qDebug() << "Call CommunicateThread JoinOrganization";
	QString url = Configuration::ServerAddress() % "joinorganization";
	QString body = "userid=" % QString::number(id) % "&organizationid=" % QString::number(Configuration::OrganizationId());
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
				emit JoinOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("同意加入组织失败");
	emit JoinOrganizationRes(false);
	return;
}

void Communicate::GetOrganizationMembers()
{
	qDebug() << "Call CommunicateThread GetOrganizationMembers";
	QString url = Configuration::ServerAddress() % "getorganizationmembers?organizationid=" % QString::number(Configuration::OrganizationId());
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toArray();
				emit GetOrganizationMembersRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("获取组织成员失败");
	emit GetOrganizationMembersRes(QJsonArray());
	return;
}

void Communicate::CreateOrganization(QString name)
{
	qDebug() << "Call CommunicateThread CreateOrganization";
	QString url = Configuration::ServerAddress() % "createorganization";
	QString body = "userid=" % QString::number(Configuration::UserId()) % "&organizationname=" % name;
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
				emit CreateOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("创建组织失败");
	emit CreateOrganizationRes(false);
	return;
}

void Communicate::DissolveOrganization(int id)
{
	qDebug() << "Call CommunicateThread DissolveOrganization";
	QString url = Configuration::ServerAddress() % "dissolveorganization";
	QString body = "organizationid=" % QString::number(id);
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
				emit DissolveOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("解散组织失败");
	emit DissolveOrganizationRes(false);
	return;
}

void Communicate::ShowAppealOrganization()
{
	qDebug() << "Call CommunicateThread ShowAppealOrganization";
	QString url = Configuration::ServerAddress() % "showappealorganization?organizationid=" % QString::number(Configuration::OrganizationId());
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toArray();
				emit ShowAppealOrganizationRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("查看申请加入组织名单失败");
	emit ShowAppealOrganizationRes(QJsonArray());
	return;
}

void Communicate::UpOrganizationMemberPower(int id)
{
	qDebug() << "Call CommunicateThread UpOrganizationMemberPower";
	QString url = Configuration::ServerAddress() % "uporganizationmemberpower";
	QString body = "userid=" % QString::number(id);
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
				emit UpOrganizationMemberPowerRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("提升用户权限失败");
	emit UpOrganizationMemberPowerRes(false);
	return;
}

void Communicate::LowOrganizationMemberPower(int id)
{
	qDebug() << "Call CommunicateThread LowOrganizationMemberPower";
	QString url = Configuration::ServerAddress() % "loworganizationmemberpower";
	QString body = "userid=" % QString::number(id);
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
				emit LowOrganizationMemberPowerRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("降低用户权限失败");
	emit LowOrganizationMemberPowerRes(false);
	return;
}

void Communicate::ShowUser()
{
	qDebug() << "Call CommunicateThread ShowUser";
	QString url = Configuration::ServerAddress() % "showuser";
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toArray();
				emit ShowUserRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("查看所有用户失败");
	emit ShowUserRes(QJsonArray());
	return;
}

void Communicate::BanUser(int id)
{
	qDebug() << "Call CommunicateThread BanUser";
	QString url = Configuration::ServerAddress() % "banuser";
	QString body = "userid=" % QString::number(id);
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
				emit BanUserRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("封禁用户失败");
	emit BanUserRes(false);
	return;
}

void Communicate::ResetUser(int id)
{
	qDebug() << "Call CommunicateThread ResetUser";
	QString url = Configuration::ServerAddress() % "resetuser";
	QString body = "userid=" % QString::number(id);
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
				emit ResetUserRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("解除封禁用户失败");
	emit ResetUserRes(false);
	return;
}

void Communicate::AppealUser()
{
	qDebug() << "Call CommunicateThread AppealUser";
	QString url = Configuration::ServerAddress() % "appealuser";
	QString body = "userid=" % QString::number(Configuration::UserId());
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
				emit AppealUserRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("用户申请解除封禁失败");
	emit AppealUserRes(false);
	return;
}

void Communicate::ShowOrganization()
{
	qDebug() << "Call CommunicateThread ShowOrganization";
	QString url = Configuration::ServerAddress() % "showorganization";
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toArray();
				emit ShowOrganizationRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("查看所有组织失败");
	emit ShowOrganizationRes(QJsonArray());
	return;
}

void Communicate::BanOrganization(int id)
{
	qDebug() << "Call CommunicateThread BanOrganization";
	QString url = Configuration::ServerAddress() % "banorganization";
	QString body = "organizationid=" % QString::number(id);
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
				emit BanOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("封禁组织失败");
	emit BanOrganizationRes(false);
	return;
}

void Communicate::ResetOrganization(int id)
{
	qDebug() << "Call CommunicateThread ResetOrganization";
	QString url = Configuration::ServerAddress() % "resetorganization";
	QString body = "organizationid=" % QString::number(id);
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
				emit ResetOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("封禁组织失败");
	emit ResetOrganizationRes(false);
	return;
}

void Communicate::AppealOrganization()
{
	qDebug() << "Call CommunicateThread AppealOrganization";
	QString url = Configuration::ServerAddress() % "appealorganization";
	QString body = "organizationid=" % QString::number(Configuration::OrganizationId());
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
				emit AppealOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("申请解封组织失败");
	emit AppealOrganizationRes(false);
	return;
}

void Communicate::ShowFile()
{
	qDebug() << "Call CommunicateThread ShowFile";
	QString url = Configuration::ServerAddress() % "showfile";
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toObject();
				emit ShowFileRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("查看所有文件失败");
	emit ShowFileRes(QJsonObject());
	return;
}

void Communicate::BanFile(int id)
{
	qDebug() << "Call CommunicateThread BanFile";
	QString url = Configuration::ServerAddress() % "banfile";
	QString body = "fileid=" % QString::number(id);
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
				emit BanFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("封禁文件失败");
	emit BanFileRes(false);
	return;
}

void Communicate::ResetFile(int id)
{
	qDebug() << "Call CommunicateThread ResetFile";
	QString url = Configuration::ServerAddress() % "resetfile";
	QString body = "fileid=" % QString::number(id);
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
				emit ResetFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("解封文件失败");
	emit ResetFileRes(false);
	return;
}

void Communicate::AppealFile(int id)
{
	qDebug() << "Call CommunicateThread AppealFile";
	QString url = Configuration::ServerAddress() % "appealfile";
	QString body = "fileid=" % QString::number(id);
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
				emit AppealFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("申请解封文件失败");
	emit AppealFileRes(false);
	return;
}

void Communicate::ShowOrganizationFile()
{
	qDebug() << "Call CommunicateThread ShowOrganizationFile";
	QString url = Configuration::ServerAddress() % "showorganizationfile?organizationid=" % QString::number(Configuration::OrganizationId());
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toArray();
				emit ShowOrganizationFileRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("查看组织文件失败");
	emit ShowOrganizationFileRes(QJsonArray());
	return;
}

void Communicate::UpLoadOrganizationFile(QString path)
{
	qDebug() << "Call CommunicateThread UpLoadOrganizationFile";
	QString url = Configuration::ServerAddress() % "uploadorganizationfile";
	QNetworkRequest request;
	request.setUrl(url);
	QFile* file = new QFile(path);
	if (!file->open(QIODevice::ReadOnly))
	{
		LOG(INFO) << QStringLiteral("打开文件失败");
		emit UpLoadOrganizationFileRes(false);
		file->close();
		file->deleteLater();
		return;
	}
	QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	QHttpPart idPart;
	idPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"organizationid\";"));
	idPart.setBody(QString::number(Configuration::OrganizationId()).toLatin1());
	QHttpPart namePart;
	namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"organizationname\";"));
	namePart.setBody(Configuration::OrganizationName().toUtf8());
	QHttpPart fileNamePart;
	fileNamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"filename\";"));
	fileNamePart.setBody(QFileInfo(path).fileName().toUtf8());
	QHttpPart filePart;
	filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"file\";filename=\"%1\";").arg(QFileInfo(path).fileName())));
	filePart.setRawHeader("Content-Type", "multipart/form-data");
	filePart.setBodyDevice(file);
	file->setParent(multiPart);
	multiPart->append(idPart);
	multiPart->append(namePart);
	multiPart->append(fileNamePart);
	multiPart->append(filePart);
	QNetworkReply* reply = manager->post(request, multiPart);
	multiPart->setParent(reply);
	QEventLoop eventloop;
	QTimer timer;
	timer.singleShot(15000, &eventloop, SLOT(quit()));
	timer.start();
	QMetaObject::Connection conRet = QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(LoadProgress(qint64, qint64)));
	Q_ASSERT(conRet);
	eventloop.exec(QEventLoop::ExcludeUserInputEvents);
	if (!timer.isActive())
	{
		disconnect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
		reply->abort();
		reply->deleteLater();
		return;
	}
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(reply->readAll().mid(1), &error);
	disconnect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
	reply->abort();
	reply->deleteLater();
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				emit UpLoadOrganizationFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("组织文件上传失败");
	emit UpLoadOrganizationFileRes(false);
	return;
}

void Communicate::DeleteOrganizationFile(int id)
{
	qDebug() << "Call CommunicateThread DeleteOrganizationFile";
	QString url = Configuration::ServerAddress() % "deleteorganizationfile";
	QString body = "fileid=" % QString::number(id);
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
				emit DeleteOrganizationFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("删除组织文件失败");
	emit DeleteOrganizationFileRes(false);
	return;
}

QByteArray PercentEncoding2ByteArray(QString strInput, QByteArray ByteArrayOut = QByteArray())
{
	for (int i = 0; i < strInput.length();)
	{
		if (0 == QString::compare(strInput.mid(i, 1), QString("%")))
		{
			if ((i + 2) < strInput.length())
			{
				ByteArrayOut.append(strInput.mid(i + 1, 2).toShort(0, 16));
				i = i + 3;
			}
			else
			{
				ByteArrayOut.append(strInput.mid(i, 1));
				i++;
			}
		}
		else
		{
			ByteArrayOut.append(strInput.mid(i, 1));
			i++;
		}
	}
	return ByteArrayOut;
}

void Communicate::ReplyToFile(QNetworkReply* reply)
{
	qDebug() << "Call CommunicateThread ReplyToFile";
	QString fileName;
	if (reply->hasRawHeader("Content-Disposition"))
	{
		QString fileNameStr = reply->rawHeader("Content-Disposition");
		int index = fileNameStr.indexOf("filename=");
		if (index >= 0)
		{
			if (fileNameStr.contains("filename*="))
			{
				fileNameStr = fileNameStr.replace('"', "");
				fileNameStr = fileNameStr.mid(fileNameStr.lastIndexOf("''") + 2);
				fileName = QTextCodec::codecForName("UTF-8")->toUnicode(PercentEncoding2ByteArray(fileNameStr));
			}
			else
			{
				fileNameStr = fileNameStr.replace('"', "");
				fileNameStr = fileNameStr.mid(index + 9);
				fileName = fileNameStr;
			}
		}
	}
	else
	{
		QUrl url = reply->url();
		if (!url.isEmpty())
		{
			fileName = url.fileName();
		}
	}
	qDebug() << "fileName:" << fileName;
	if (!fileName.isEmpty())
	{
		QString filePath = QApplication::applicationDirPath() % "/download/" % Configuration::Username() % "/" % fileName;
		QFile file(filePath);
		if (file.open(QIODevice::WriteOnly))
		{
			disconnect(manager, 0, 0, 0);
			file.write(reply->readAll());
			emit DownLoadFileRes(true);
			file.close();
			reply->abort();
			reply->deleteLater();
			return;
		}
	}
	disconnect(manager, 0, 0, 0);
	reply->abort();
	reply->deleteLater();
	emit DownLoadFileRes(false);
	return;
}

void Communicate::RefuseOrganization(int id)
{
	qDebug() << "Call CommunicateThread RefuseOrganization";
	QString url = Configuration::ServerAddress() % "refuseorganization";
	QString body = "userid=" % QString::number(id);
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
				emit RefuseOrganizationRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("拒绝加入组织失败");
	emit RefuseOrganizationRes(false);
	return;
}

void Communicate::ShowUserFile()
{
	qDebug() << "Call CommunicateThread ShowUserFile";
	QString url = Configuration::ServerAddress() % "showuserfile?userid=" % QString::number(Configuration::UserId());
	QByteArray data = Get(url);
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				auto data = obj.value("data").toArray();
				emit ShowUserFileRes(data);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("获取用户文件失败");
	emit GetOrganizationMembersRes(QJsonArray());
	return;
}

void Communicate::UpLoadUserFile(QString path)
{
	qDebug() << "Call CommunicateThread UpLoadUserFile";
	QString url = Configuration::ServerAddress() % "uploaduserfile";
	QNetworkRequest request;
	request.setUrl(url);
	QFile* file = new QFile(path);
	if (!file->open(QIODevice::ReadOnly))
	{
		LOG(INFO) << QStringLiteral("打开文件失败");
		emit UpLoadUserFileRes(false);
		file->close();
		file->deleteLater();
		return;
	}
	QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	QHttpPart idPart;
	idPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"userid\";"));
	idPart.setBody(QString::number(Configuration::UserId()).toLatin1());
	QHttpPart namePart;
	namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\";"));
	namePart.setBody(Configuration::Username().toUtf8());
	QHttpPart fileNamePart;
	fileNamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"filename\";"));
	fileNamePart.setBody(QFileInfo(path).fileName().toUtf8());
	QHttpPart filePart;
	filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"file\";filename=\"%1\";").arg(QFileInfo(path).fileName())));
	filePart.setRawHeader("Content-Type", "multipart/form-data");
	filePart.setBodyDevice(file);
	file->setParent(multiPart);
	multiPart->append(idPart);
	multiPart->append(namePart);
	multiPart->append(fileNamePart);
	multiPart->append(filePart);
	QNetworkReply* reply = manager->post(request, multiPart);
	multiPart->setParent(reply);
	QEventLoop eventloop;
	QTimer timer;
	timer.singleShot(15000, &eventloop, SLOT(quit()));
	timer.start();
	QMetaObject::Connection conRet = QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(LoadProgress(qint64, qint64)));
	Q_ASSERT(conRet);
	eventloop.exec(QEventLoop::ExcludeUserInputEvents);
	if (!timer.isActive())
	{
		disconnect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
		reply->abort();
		reply->deleteLater();
		return;
	}
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(reply->readAll().mid(1), &error);
	disconnect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
	reply->abort();
	reply->deleteLater();
	if (error.error == QJsonParseError::NoError)
	{
		if (doc.isObject())
		{
			const QJsonObject obj = doc.object();
			if (obj.contains("code") && obj.value("code").toInt() == 200)
			{
				emit UpLoadUserFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("个人文件上传失败");
	emit UpLoadUserFileRes(false);
	return;
}

void Communicate::DownLoadFile(int id)
{
	qDebug() << "Call CommunicateThread DownLoadFile";
	QString downloadPath = QApplication::applicationDirPath() % "/download/" % Configuration::Username();
	QString filePath = downloadPath % "/tmp.file";
	QDir dir;
	if (!dir.exists(downloadPath))
	{
		if (!dir.mkdir(downloadPath))
			LOG(INFO) << QStringLiteral("无法创建%1/download文件夹，请手动创建").arg(QApplication::applicationDirPath());
	}

	QString url = Configuration::ServerAddress() % "downloadfile?fileid=" % QString::number(id);
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	QNetworkReply* reply = manager->get(request);

	disconnect(manager, 0, 0, 0);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyToFile(QNetworkReply*)));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(LoadError(QNetworkReply::NetworkError)));
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(LoadProgress(qint64, qint64)));

	return;
}

void Communicate::DeleteUserFile(int id)
{
	qDebug() << "Call CommunicateThread DeleteUserFile";
	QString url = Configuration::ServerAddress() % "deleteuserfile";
	QString body = "fileid=" % QString::number(id);
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
				emit DeleteUserFileRes(true);
				return;
			}
		}
	}
	LOG(INFO) << QStringLiteral("删除文件失败");
	emit DeleteUserFileRes(false);
	return;
}