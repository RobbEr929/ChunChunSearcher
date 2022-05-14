#ifndef CCS_COMMUNICATE_H
#define CCS_COMMUNICATE_H
#include "configuration.h"
#include "easylogging++.h"
#include <QObject>
#include <QTimer>
#include <QStringBuilder>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetWorkReply>
#include <QJsonArray>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QDir>
#include <QProgressBar>

class Communicate : public QObject
{
	Q_OBJECT
public:
	Communicate();
	~Communicate();

private:
	QByteArray Get(QString url);
	QByteArray Post(QString url, QString body);
	QNetworkAccessManager* manager;

signals:
	void Online(bool res);
	void SignRes(bool res);
	void RegisterRes(bool res);
	void GetConfRes(bool res);
	void WriteConfRes(bool res);
	void GetUserInfoRes(bool res);
	void LeaveOrganizationRes(bool res);
	void ApplyJoinOrganizationRes(bool res);
	void JoinOrganizationRes(bool res);
	void GetOrganizationMembersRes(QJsonArray obj);
	void ShowUserFileRes(QJsonArray obj);
	void UpLoadOrganizationFileRes(bool res);
	void AppealUserRes(bool res);
	void AppealFileRes(bool res);
	void AppealOrganizationRes(bool res);
	void DownLoadFileRes(bool res);
	void CreateOrganizationRes(bool res);
	void DissolveOrganizationRes(bool res);
	void ShowAppealOrganizationRes(QJsonArray obj);
	void UpOrganizationMemberPowerRes(bool res);
	void LowOrganizationMemberPowerRes(bool res);
	void TransmissionError(QNetworkReply::NetworkError);
	void ShowUserRes(QJsonArray obj);
	void ShowOrganizationFileRes(QJsonArray obj);
	void ShowOrganizationRes(QJsonArray obj);
	void ShowFileRes(QJsonObject obj);
	void ResetUserRes(bool res);
	void ResetOrganizationRes(bool res);
	void ResetFileRes(bool res);
	void DeleteUserFileRes(bool res);
	void DeleteOrganizationFileRes(bool res);
	void BanUserRes(bool res);
	void BanFileRes(bool res);
	void BanOrganizationRes(bool res);
	void LoadProgressRes(qint64 bytesSent, qint64 bytesTotal);
	void UpLoadUserFileRes(bool res);
	void RefuseOrganizationRes(bool res);

public slots:
	void LoadError(QNetworkReply::NetworkError error);
	void LoadProgress(qint64 bytesSent, qint64 bytesTotal);
	void AbleToOnline();
	void Sign();
	void Register();
	void GetConf();
	void WriteConf();
	void GetUserInfo();
	void LeaveOrganization(int id);
	void ApplyJoinOrganization(int id);
	void JoinOrganization(int id);
	void GetOrganizationMembers();
	void CreateOrganization(QString name);
	void DissolveOrganization(int id);
	void ShowAppealOrganization();
	void UpOrganizationMemberPower(int id);
	void LowOrganizationMemberPower(int id);
	void ShowUser();
	void BanUser(int id);
	void ResetUser(int id);
	void AppealUser();
	void ShowOrganization();
	void BanOrganization(int id);
	void ResetOrganization(int id);
	void AppealOrganization();
	void ShowFile();
	void BanFile(int id);
	void ResetFile(int id);
	void AppealFile(int id);
	void ShowUserFile();
	void UpLoadUserFile(QString path);
	void DownLoadFile(int id);
	void DeleteUserFile(int id);
	void ShowOrganizationFile();
	void UpLoadOrganizationFile(QString path);
	void DeleteOrganizationFile(int id);
	void ReplyToFile(QNetworkReply* reply);
	void RefuseOrganization(int id);
};

#endif