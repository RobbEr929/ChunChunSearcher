#include "monitor.h"
#include "easylogging++.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QStringBuilder>
#include <QString>

Monitor::Monitor()
	:watcher(new QFileSystemWatcher)
{
	connect(watcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(DiretoryModified(const QString&)));
}

void Monitor::AddPath(QString path)
{
	qDebug() << "Call MonitorThread AddPath";
	QFileInfo info(path);
	if (info.isDir())
	{
		watcher->addPath(path);
		const QDir dir(path);
		fileList[path] = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
		LOG(INFO) << QStringLiteral("正在监视文件夹 %1").arg(path);
	}
}

void Monitor::RemovePath(QString path)
{
	qDebug() << "Call MonitorThread RemovePath";
	QFileInfo info(path);
	if (info.isDir())
	{
		watcher->removePath(path);
		const QDir dir(path);
		fileList.erase(fileList.find(path));
		LOG(INFO) << QStringLiteral("取消监视文件夹 %1").arg(path);
	}
}

void Monitor::DiretoryModified(const QString& path)
{
	qDebug() << "Call MonitorThread DiretoryModified";
	qDebug() << QString("Directory updated: %1").arg(path);
	QStringList nowList = fileList[path];
	const QDir dir(path);
	QStringList newList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
	QSet<QString> newSet = QSet<QString>::fromList(newList);
	QSet<QString> nowSet = QSet<QString>::fromList(nowList);

	//create
	QSet<QString> newFiles = newSet - nowSet;
	QStringList newFile = newFiles.toList();

	//delete
	QSet<QString> delFiles = nowSet - newSet;
	QStringList delFile = delFiles.toList();

	fileList[path] = newList;

	if (!newFile.isEmpty() && !delFile.isEmpty())
	{
		if ((newFile.count() == 1) && (delFile.count() == 1))
		{
			qDebug() << QString("%1 Renamed %2").arg(delFile.first()).arg(newFile.first());
			emit SomeRenamed(path % '*' % delFile.first() % '*' % newFile.first());
		}
	}
	else
	{
		if (!newFile.isEmpty())
		{
			foreach(QString file, newFile)
			{
				qDebug() << "Created " << file;
				emit SomeCreated(path % '*' % file);
			}
		}
		if (!delFile.isEmpty())
		{
			qDebug() << "Deleted: " << delFile;
			foreach(QString file, delFile)
			{
				emit SomeDeleted(path % '*' % file);
			}
		}
	}
}