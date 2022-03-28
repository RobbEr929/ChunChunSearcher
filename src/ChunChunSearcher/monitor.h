#ifndef CCS_MONITOR_H
#define CCS_MONITOR_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QFileSystemWatcher>

class Monitor :public QObject
{
	Q_OBJECT
public:
	Monitor();
	void AddPath(QString path);
	void RemovePath(QString path);

private:
	QFileSystemWatcher* watcher;
	QMap<QString, QStringList> fileList;

signals:
	void SomeCreated(QString path);
	void SomeDeleted(QString path);
	void SomeRenamed(QString path);

public slots:
	void DiretoryModified(const QString& path);
};

#endif