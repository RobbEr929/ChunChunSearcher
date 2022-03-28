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

public slots:
	void AbleToOnline();
	void Sign();
	void Register();
	void GetConf();
	void WriteConf();
};

#endif