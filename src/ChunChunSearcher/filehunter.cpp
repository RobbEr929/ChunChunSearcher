#include "filehunter.h"
#include "identify.h"
#include "configuration.h"
#include "easylogging++.h"
#include <filesystem>
#include <QRegularExpression>
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include <QDebug>
#include <QCryptographicHash>
#include <QStringBuilder>
#include <QFileInfo>

using namespace ccs;
using namespace std;

bool IsCompare(QString str1, QString str2)
{
	str1 = str1.trimmed();
	str2 = str2.trimmed();
	if (Configuration::SearcRegEx())
	{
		QRegularExpression regex(str1);
		if (!Configuration::SearchCaseSensitive())
			regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
		return regex.match(str2).hasMatch();
	}
	else
	{
		if (Configuration::SearchCaseSensitive())
			return str2.contains(str1, Qt::CaseSensitive);
		else
			return str2.contains(str1, Qt::CaseInsensitive);
	}
}

bool IsIgnore(QString str1)
{
	for (auto i : Configuration::IgnorePath())
	{
		if (str1.contains(i))
		{
			return true;
		}
	}
	return false;
}

Volume::Volume(char vol, char attr)
	: volume(vol)
	, attribute(attr)
	, isOk(false)
	, isFirst(true)
{ }

qulonglong Volume::FileNumber() const
{
	return fileMap.size();
}

qulonglong Volume::RightFileNumber() const
{
	return rightFile.size();
}

char Volume::VolumeName() const
{
	return volume;
}

char Volume::IsOk() const
{
	return isOk;
}

QVector<QPair<QString, QString>>& Volume::RightFile()
{
	return rightFile;
}

void Volume::InitNtfs()
{
	qDebug() << "Call VolumeThread InitNtfs";
	QString rootName = QString("\\\\.\\%1:").arg(volume);
	HANDLE hVol = CreateFileA(rootName.toStdString().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if (hVol == INVALID_HANDLE_VALUE)
	{
		if (isFirst)
			emit InitRes(false);
		else
			emit ReInitRes(false);
		LOG(INFO) << QStringLiteral("读取磁盘 %1 路径失败").arg(volume);
		return;
	}
	DWORD br;
	CREATE_USN_JOURNAL_DATA cujd;
	cujd.AllocationDelta = 0;
	cujd.MaximumSize = 0;
	if (!DeviceIoControl(hVol, FSCTL_CREATE_USN_JOURNAL, &cujd, sizeof(cujd), NULL, 0, &br, NULL))
	{
		if (isFirst)
			emit InitRes(false);
		else
			emit ReInitRes(false);
		LOG(INFO) << QStringLiteral("读取磁盘 %1 路径失败").arg(volume);
		return;
	}
	USN_JOURNAL_DATA ujd;
	if (!DeviceIoControl(hVol, FSCTL_QUERY_USN_JOURNAL, NULL, 0, &ujd, sizeof(ujd), &br, NULL))
	{
		if (isFirst)
			emit InitRes(false);
		else
			emit ReInitRes(false);
		LOG(INFO) << QStringLiteral("读取磁盘 %1 路径失败").arg(volume);
		return;
	}
	MFT_ENUM_DATA med;
	med.StartFileReferenceNumber = 0;
	med.LowUsn = 0;
	if (isFirst)
	{
		med.HighUsn = ujd.NextUsn;
		reInitUSN = ujd.NextUsn;
	}
	else
	{
		med.HighUsn = reInitUSN > ujd.NextUsn
			? reInitUSN
			: ujd.NextUsn;
	}
	med.MaxMajorVersion = 2;
	const size_t BUF_LEN = 0xa000;
	char Buffer[BUF_LEN];
	DWORD usnDataSize;
	PUSN_RECORD UsnRecord;
	while (DeviceIoControl(hVol, FSCTL_ENUM_USN_DATA, &med, sizeof(med), Buffer, BUF_LEN, &usnDataSize, NULL))
	{
		med.StartFileReferenceNumber = *(USN*)&Buffer;
		usnDataSize -= sizeof(USN);
		UsnRecord = (PUSN_RECORD)(Buffer + sizeof(USN));
		while (usnDataSize > 0)
		{
			QString fileName = QString::fromWCharArray(UsnRecord->FileName, UsnRecord->FileNameLength / 2);
			if (UsnRecord->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				fileMap.insert(UsnRecord->FileReferenceNumber, { UsnRecord->ParentFileReferenceNumber, fileName, FILTER_DIRECTORY });
			}
			else
			{
				fileMap.insert(UsnRecord->FileReferenceNumber, { UsnRecord->ParentFileReferenceNumber, fileName, Identify::IdentifyBySuffix(fileName) });
			}
			usnDataSize -= UsnRecord->RecordLength;
			UsnRecord = (PUSN_RECORD)(((PCHAR)UsnRecord) + UsnRecord->RecordLength);
		}
	}
	isOk = true;
	DELETE_USN_JOURNAL_DATA dujd;
	dujd.UsnJournalID = ujd.UsnJournalID;
	dujd.DeleteFlags = USN_DELETE_FLAG_DELETE;
	DeviceIoControl(hVol, FSCTL_DELETE_USN_JOURNAL, &dujd, sizeof(dujd), NULL, 0, &br, NULL);
	CloseHandle(hVol);
}

void Volume::InitOther()
{
	qDebug() << "Call VolumeThread InitOther";
	QString rootName = QString("%1:\\").arg(volume);
	filesystem::path rootPath = filesystem::path(rootName.toStdString());
	if (!filesystem::exists(rootPath))
	{
		LOG(INFO) << QStringLiteral("读取磁盘 %1 路径失败").arg(volume);
		emit InitRes(false);
	}
	for (auto di : filesystem::recursive_directory_iterator(rootPath, filesystem::directory_options::skip_permission_denied))
	{
		try
		{
			QString str = QString::fromStdU16String(di.path().u16string());
			if (filesystem::is_directory(di.path()))
				fileMap.insert(0UL, { ULLONG_MAX, QString::fromStdU16String(di.path().u16string()),FILTER_DIRECTORY });
			else
				fileMap.insert(0UL, { ULLONG_MAX, QString::fromStdU16String(di.path().u16string()),FILTER_ALL });
		}
		catch (std::system_error& e)
		{
			continue;
		}
	}
	if (fileMap.contains(ULLONG_MAX))
	{
		fileMap.erase(fileMap.find(ULLONG_MAX));
	}
	isOk = true;
}

void Volume::GetPath(qulonglong ref, QString& path)
{
	auto it = fileMap.find(ref);
	if (it != fileMap.end())
	{
		if (it.value().pref != 0)
		{
			GetPath(it.value().pref, path);
		}
		path.append(it.value().name);
		path.append("\\");
	}
	return;
}

void Volume::Init()
{
	qDebug() << "Call VolumeThread Init";
	fileMap.clear();
	fileMap.insert(0x5000000000005UL, { 0UL, QString("%1:").arg(volume),1 });
	if ((attribute & VOLUME_IS_NTFS) && (attribute & VOLUME_USEING))
	{
		InitNtfs();
	}
	if (isFirst)
	{
		isFirst = false;
		emit InitRes(true);
	}
	else
	{
		emit ReInitRes(true);
	}
}

void Volume::ReInit(char c)
{
	qDebug() << "Call VolumeThread ReInit";
	if (volume != c || attribute & VOLUME_USEING)
	{
		return;
	}
	emit EmitInfo(QStringLiteral("正在重新读取磁盘 %1,可以照常搜索").arg(volume));
	LOG(INFO) << QStringLiteral("重新读取磁盘 %1").arg(volume);
	if ((attribute & VOLUME_IS_NTFS) && isOk == false)
	{
		//QDebug() << "Volume ReInit using ntfs" << volume;
		fileMap.clear();
		fileMap.insert(0x5000000000005UL, { 0UL, QString("%1:").arg(volume),1 });
		InitNtfs();
		attribute = attribute & 0b11 | VOLUME_USEING;
	}
	else if (isOk == false)
	{
		InitOther();
		attribute = attribute & 0b11 | VOLUME_USEING;
	}
	emit EmitInfo(QStringLiteral("磁盘 %1 重新读取完毕").arg(volume));
}

void Volume::FindFile(QVariant str)
{
	qDebug() << "Call VolumeThread FindFile";
	if (!isOk && (attribute & VOLUME_USEING) == 0)
	{
		emit FindRes(volume);
		return;
	}
	rightFile.clear();
	rightFile.shrink_to_fit();
	FindStruct st = str.value<FindStruct>();
	bool matchFile = Configuration::SearchMatchFile();
	bool matchPath = Configuration::SearchMatchPath();
	QString path;
	if (st.input.size() == 0)
	{
		for (auto i : fileMap)
		{
			if (st.type == FILTER_ALL || (i.type & 0b11110000) == st.type)
			{
				path.clear();
				GetPath(i.pref, path);
				if (IsIgnore(path))
					continue;
				if (path.size() != 0)
				{
					path = path.mid(0, path.size() - 1);
				}
				rightFile.push_back(qMakePair(i.name, path));
			}
		}
		emit FindRes(volume);
		return;
	}
	for (auto i : fileMap)
	{
		if (st.type == FILTER_ALL || (i.type & 0b11110000) == st.type)
		{
			if (matchFile && matchPath)
			{
				path.clear();
				if (IsCompare(st.input, i.name))
				{
					GetPath(i.pref, path);
					if (IsIgnore(path))
						continue;
					if (path.size() != 0)
					{
						path = path.mid(0, path.size() - 1);
					}
					rightFile.push_back(qMakePair(i.name, path));
				}
				else
				{
					GetPath(i.pref, path);
					if (IsIgnore(path))
						continue;
					if (path.size() != 0)
					{
						if (IsCompare(st.input, path))
						{
							path = path.mid(0, path.size() - 1);
							rightFile.push_back(qMakePair(i.name, path));
						}
					}
				}
			}
			else if (matchFile)
			{
				if (IsCompare(st.input, i.name))
				{
					path.clear();
					GetPath(i.pref, path);
					if (IsIgnore(path))
						continue;
					if (path.size() != 0)
						path = path.mid(0, path.size() - 1);
					rightFile.push_back(qMakePair(i.name, path));
				}
			}
			else if (matchPath)
			{
				path.clear();
				GetPath(i.pref, path);
				if (IsIgnore(path))
					continue;
				if (path.size() != 0)
				{
					if (IsCompare(st.input, path))
					{
						path = path.mid(0, path.size() - 1);
						rightFile.push_back(qMakePair(i.name, path));
					}
				}
			}
		}
	}
	emit FindRes(volume);
}

void Volume::AutoUpdate()
{
	qDebug() << "Call VolumeThread AutoUpdate";
	if ((attribute & VOLUME_IS_NTFS) && (attribute & VOLUME_USEING))
	{
		emit BeginUpdate();
		isOk = false;
		fileMap.clear();
		fileMap.insert(0x5000000000005UL, { 0UL, QString("%1:").arg(volume),1 });
		InitNtfs();
		emit EndUpdate();
	}
}

void Volume::RemoveData(char c)
{
	qDebug() << "Call VolumeThread RemoveData";
	if (c == volume)
	{
		attribute = attribute & 0b11 | VOLUME_DISCARD;
		fileMap.clear();
		isOk = false;
		emit EmitInfo(QStringLiteral("磁盘 %1 已移除").arg(volume));
		LOG(INFO) << QStringLiteral("移除磁盘 %1").arg(volume);
	}
}

void Volume::SomeCreated(QString path)
{
	qDebug() << "Call VolumeThread SomeCreated";
	char vol = path[0].toLatin1();
	if (vol == volume)
	{
		auto pos = path.lastIndexOf('*');
		QString fullPath, name, beforePath, afterPath;
		fullPath = path.mid(0, pos);
		name = path.mid(pos + 1);
		pos = fullPath.lastIndexOf('\\');
		beforePath = fullPath.mid(0, pos);
		if (beforePath.size() == fullPath.size() - 1)
		{
			QFileInfo info(fullPath % '\\' % name);
			qulonglong hashCode = info.birthTime().toMSecsSinceEpoch();
			while (fileMap.find(hashCode) != fileMap.end());
			{
				hashCode *= 0.99;
			}
			if (info.isDir())
			{
				fileMap.insert(hashCode, { 0x5000000000005UL,name,FILTER_DIRECTORY });
			}
			else
			{
				fileMap.insert(hashCode, { 0x5000000000005UL,name,Identify::IdentifyBySuffix(name) });
			}
			return;
		}
		afterPath = fullPath.mid(pos + 1);
		for (auto i = fileMap.begin(); i != fileMap.end(); ++i)
		{
			if (i->name.compare(afterPath) == 0)
			{
				QString p;
				GetPath(i->pref, p);
				if (p.compare(beforePath % '\\') == 0)
				{
					QFileInfo info(fullPath % '\\' % name);
					qulonglong hashCode = info.birthTime().toMSecsSinceEpoch();
					while (fileMap.contains(hashCode));
					{
						hashCode *= 0.99;
					}
					if (info.isDir())
					{
						fileMap.insert(hashCode, { i.key(),name,FILTER_DIRECTORY });
					}
					else
					{
						fileMap.insert(hashCode, { i.key(),name,Identify::IdentifyBySuffix(name) });
					}
					return;
				}
			}
		}
	}
}

void Volume::SomeDeleted(QString path)
{
	qDebug() << "Call VolumeThread SomeDeleted";
	char vol = path[0].toLatin1();
	if (vol == volume)
	{
		auto pos = path.lastIndexOf('*');
		QString fullPath, name, beforePath;
		fullPath = path.mid(0, pos);
		name = path.mid(pos + 1);
		for (auto i = fileMap.begin(); i != fileMap.end(); ++i)
		{
			if (i->name.compare(name) == 0)
			{
				QString p;
				GetPath(i->pref, p);
				if (fullPath[fullPath.size() - 1] != '\\')
					fullPath.append('\\');
				if (p.compare(fullPath) == 0)
				{
					fileMap.erase(i);
					return;
				}
			}
		}
	}
}

void Volume::SomeRenamed(QString path)
{
	qDebug() << "Call VolumeThread SomeRenamed";
	char vol = path[0].toLatin1();
	if (vol == volume)
	{
		auto pos = path.lastIndexOf('*');
		QString fullPath, name;
		fullPath = path.mid(0, pos);
		name = path.mid(pos + 1);
		for (auto i = fileMap.begin(); i != fileMap.end(); ++i)
		{
			if (i->name.compare(name) == 0)
			{
				QString p;
				GetPath(i->pref, p);
				if (fullPath[fullPath.size() - 1] != '\\')
					fullPath.append('\\');
				if (p.compare(fullPath) == 0)
				{
					i->name = name;
					return;
				}
			}
		}
	}
}

FileSystem::FileSystem()
{ }

void FileSystem::getFileSystem(char c)
{
	qDebug() << "Call FileSystemThread getFileSystem";
	QString lpRootPathName = QString("%1:\\").arg(c);
	char lpVolumeNameBuffer[MAX_PATH];
	DWORD lpVolumeSerialNumber;
	DWORD lpMaximumComponentLength;
	DWORD lpFileSystemFlags;
	char lpFileSystemNameBuffer[MAX_PATH];
	if (GetVolumeInformationA(
		lpRootPathName.toStdString().c_str(),
		lpVolumeNameBuffer,
		MAX_PATH,
		&lpVolumeSerialNumber,
		&lpMaximumComponentLength,
		&lpFileSystemFlags,
		lpFileSystemNameBuffer,
		MAX_PATH
	))
	{
		if (QString::fromLatin1(lpFileSystemNameBuffer).compare("NTFS") == 0)
			Configuration::AddVolumeFileSystem(c, VOLUME_IS_NTFS | VOLUME_USEING);
		else
			Configuration::AddVolumeFileSystem(c, VOLUME_NOT_NTFS | VOLUME_DISCARD);
	}
	else
	{
		LOG(INFO) << QStringLiteral("读取磁盘 %1 信息失败").arg(c);
	}
	return;
}

void FileSystem::Init()
{
	qDebug() << "Call FileSystemThread Init";
	QTime time;
	char dirveBuf[1000];
	memset(dirveBuf, 0, 1000);
	time.start();
	DWORD len = GetLogicalDriveStringsA(sizeof(dirveBuf) / sizeof(char), dirveBuf);
	for (char* buf = dirveBuf; *buf; buf += strlen(buf) + 1)
	{
		getFileSystem(*buf);
	}
	quint8 cnt = 0;
	auto volVec = Configuration::VolumeFileSystem();
	for (auto i = volVec.begin(); i != volVec.end(); ++i)
	{
		if (i.value() & VOLUME_IS_NTFS)
			cnt++;
	}
	emit EmitInfo(QStringLiteral("读取磁盘信息完成，获取到 %1 个磁盘，其中 %2 个为 NTFS ，更多可查看选项(Ctrl+P)，总共用时 %3 秒，读取路径中...").arg(len / 4).arg(cnt).arg(time.elapsed() / 1000.0));
	LOG(INFO) << QStringLiteral("读取磁盘信息完成，获取到 %1 个磁盘，其中 %2 个为 NTFS").arg(len / 4).arg(cnt);
	emit InitRes(true);
}