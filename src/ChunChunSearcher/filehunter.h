#ifndef CCS_FILEHUNTER_H
#define CCS_FILEHUNTER_H
#include "global.h"
#include <tuple>
#include <QObject>
#include <QMap>
#include <QMetaType>
#include <QVariant>

struct FileStruct
{
	qulonglong pref;
	QString name;
	quint8 type;
};

struct FindStruct
{
	QString input;
	quint8 type;
};
Q_DECLARE_METATYPE(FindStruct)
class Volume : public QObject
{
	Q_OBJECT
public:
	Volume(char vol, char attr);
	qulonglong FileNumber()const;
	qulonglong RightFileNumber()const;
	char VolumeName()const;
	char IsOk()const;
	QVector<QPair<QString, QString>>& RightFile();
private:
	void InitNtfs();
	void InitOther();
	QMap <qulonglong, FileStruct> fileMap;
	QVector<QPair<QString, QString>> rightFile;
	void GetPath(qulonglong ref, QString& path);
	char volume;
	char attribute;
	bool isOk;
	bool isFirst;
	__int64 reInitUSN;

signals:
	void InitRes(bool res);
	void FindRes(char res);
	void ReInitRes(bool res);
	void BeginUpdate();
	void EndUpdate();
	void EmitInfo(QString str);

public slots:
	void Init();
	void ReInit(char c);
	void FindFile(QVariant str);
	void AutoUpdate();
	void RemoveData(char c);
	void SomeCreated(QString path);
	void SomeDeleted(QString path);
	void SomeRenamed(QString path);
};

class FileSystem : public QObject
{
	Q_OBJECT
public:
	FileSystem();

private:
	void getFileSystem(char c);

signals:
	void EmitInfo(QString str);
	void InitRes(bool res);

public slots:
	void Init();
};

#endif // FILEHUNTER_H
