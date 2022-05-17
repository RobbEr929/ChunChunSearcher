#include "configuration.h"
#include <QCoreApplication>
#include <QTextCodec>
#include <QStringBuilder>
#include <qDebug>
#include <QFile>
bool Configuration::isSigned = false;
bool Configuration::autoSign = false;
QString Configuration::serverAddress = "http://47.95.214.101:929/api/ccs/";
int Configuration::userid = 0;
int Configuration::power = 0;
int Configuration::organizationId = 0;
QString Configuration::organizationName = "";
int Configuration::status = 0;
int Configuration::organizationStatus = 0;
QString Configuration::username = "";
QString Configuration::password = "";
int Configuration::posX = -1;
int Configuration::posY = -1;
int Configuration::width = -1;
int Configuration::height = -1;
QString Configuration::cloudConf = "";
int Configuration::autoUpdateTime = 15;
bool Configuration::onlineEnable = true;
bool Configuration::filterShow = true;
bool Configuration::infoShow = true;
bool Configuration::searchCaseSensitive = true;
bool Configuration::searchMatchPath = false;
bool Configuration::searchMatchFile = true;
bool Configuration::searcRegEx = false;
bool Configuration::runInBackground = true;
bool Configuration::trayShow = true;
bool Configuration::oneClickShow = true;
bool Configuration::selectAll = true;
bool Configuration::autoUpdate = false;
QSet<QString> Configuration::ignorePath = QSet<QString>();
QSet<QString> Configuration::monitorPath = QSet<QString>();
QSet<QString> Configuration::compressedSuffix = QSet<QString>();
QSet<QString> Configuration::documentSuffix = QSet<QString>();
QSet<QString> Configuration::picutreSuffix = QSet<QString>();
QSet<QString> Configuration::audioSuffix = QSet<QString>();
QSet<QString> Configuration::videoSuffix = QSet<QString>();
QMap<char, __int8> Configuration::volumeFileSystem = QMap<char, __int8>();

QString Configuration::MetaString()
{
	QString str;
	m.lockForRead();
	QSettings conf(QCoreApplication::applicationDirPath() + "/conf/ccs.ini", QSettings::IniFormat);
	conf.setIniCodec(QTextCodec::codecForName("UTF-8"));
	QStringList strList = conf.allKeys();
	foreach(QString key, strList)
	{
		if (!key.compare("username") || !key.compare("password") || key.contains("Suffix"))
			continue;
		str.append(key % "=" % conf.value(key).toString() % "\n");
	}
	m.unlock();
	return str;
}

void Configuration::Init()
{
	m.lockForWrite();
	QSettings conf(QCoreApplication::applicationDirPath() + "/conf/ccs.ini", QSettings::IniFormat);
	conf.setIniCodec(QTextCodec::codecForName("UTF-8"));

	//default
	if (!conf.contains("ignorePath"))
		ignorePath = { "C:\\Windows" };
	if (!conf.contains("compressedSuffix"))
		compressedSuffix = { "z","bz2","lz","rar","gz","xz","tar","7z","wim","zst","rs","ace","arj","lz4","lzma","lzo","rz","sfark","sz","afa","alz","apk","arc","ark","cdx","cab","car","jar","kgb","phar","qda","txz","tlz","uc","uc0","uc2","ucn","ur2","ue2","uca","uha","war","xar","xp3","yz1","zip","zipx","zpaq","zz" };
	if (!conf.contains("documentSuffix"))
		documentSuffix = { "csv","doc","dot","docm","docx","dotx","dbf","dif","xla","xlam","xls","xlsb","xlsm","xlsx","xlt","xltm","xltx","xlw","xml","xps","wps","wpp","et","ett","wpp","dps","rtf","txt","odp","ods","odt","uot","uos","uop","uof","pdf","pot","potm","potx","ppa","ppam","pps","ppsm","ppsx","pptm","thmx","prn","ppt","html","htm","js","php","py","cc","cpp","c","h","hpp","cxx","hxx","cs","java","class","proto","pm","py3","kt","asp","css","aspx","jsp","lua","go","ini","log","json","conf","sys","eml","ts","wxml","wxss","ui","md","yml" };
	if (!conf.contains("picutreSuffix"))
		picutreSuffix = { "bmp","gif","jpg","jpeg","png","cr","dib","pcp","wmf","tif","svg","psd","eps","cdr","iff","tga","pcd","mpt","ico","icon","ilbm","tiff","xpm","mng","sai","psp","ufo","xcf","pcx","ppm","webp","ps","eps","ai","fh","swf","fla","dxf","cgm","cpc","cpi","ima","lbm","jp2","j2c","pict","pic","pct","psb","pdd","tpic","wdp" };
	if (!conf.contains("audioSuffix"))
		audioSuffix = { "wav","wma","aac","adt","adts","aif","aifc","aiff","voc","au","m3u","cda","m4a","mp3","mid","ape","mflac","ncm","qmc","mgg","kgm","xm","kwm","bkcmp3","qmc0","qmc2","qmc3","qmcflac","qmcogg","tkm","tm0","tm2","tm3","tm6","mgg1","mggl","ofl_en","vpr","ra" };
	if (!conf.contains("videoSuffix"))
		videoSuffix = { "mp4","flv","vob","wmv","avi","rm","rmvb","mpg","mpeg","mov","swf","ram","mkv","mpe","asf","3gp" };

	if (conf.contains("autoSign"))
		autoSign = conf.value("autoSign").toBool();
	if (conf.contains("username"))
		username = conf.value("username").toString();
	if (conf.contains("password"))
		password = conf.value("password").toString();
	if (conf.contains("posX"))
		posX = conf.value("posX").toInt();
	if (conf.contains("posY"))
		posY = conf.value("posY").toInt();
	if (conf.contains("width"))
		width = conf.value("width").toInt();
	if (conf.contains("height"))
		height = conf.value("height").toInt();
	if (conf.contains("autoUpdateTime"))
		autoUpdateTime = conf.value("autoUpdateTime").toInt();
	if (conf.contains("onlineEnable"))
		onlineEnable = conf.value("onlineEnable").toBool();
	if (conf.contains("filterShow"))
		filterShow = conf.value("filterShow").toBool();
	if (conf.contains("infoShow"))
		infoShow = conf.value("infoShow").toBool();
	if (conf.contains("searchCaseSensitive"))
		searchCaseSensitive = conf.value("searchCaseSensitive").toBool();
	if (conf.contains("searchMatchPath"))
		searchMatchPath = conf.value("searchMatchPath").toBool();
	if (conf.contains("searchMatchFile"))
		searchMatchFile = conf.value("searchMatchFile").toBool();
	if (conf.contains("searcRegEx"))
		searcRegEx = conf.value("searcRegEx").toBool();
	if (conf.contains("runInBackground"))
		runInBackground = conf.value("runInBackground").toBool();
	if (conf.contains("trayShow"))
		trayShow = conf.value("trayShow").toBool();
	if (conf.contains("oneClickShow"))
		oneClickShow = conf.value("oneClickShow").toBool();
	if (conf.contains("selectAll"))
		selectAll = conf.value("selectAll").toBool();
	if (conf.contains("autoUpdate"))
		autoUpdate = conf.value("autoUpdate").toBool();
	if (conf.contains("ignorePath"))
	{
		QString path = conf.value("ignorePath").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			ignorePath.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("monitorPath"))
	{
		QString path = conf.value("monitorPath").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			monitorPath.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("compressedSuffix"))
	{
		QString path = conf.value("compressedSuffix").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			compressedSuffix.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("documentSuffix"))
	{
		QString path = conf.value("documentSuffix").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			documentSuffix.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("picutreSuffix"))
	{
		QString path = conf.value("picutreSuffix").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			picutreSuffix.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("audioSuffix"))
	{
		QString path = conf.value("audioSuffix").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			audioSuffix.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("videoSuffix"))
	{
		QString path = conf.value("videoSuffix").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			videoSuffix.insert(path.mid(start, pos - start));
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	if (conf.contains("volumeFileSystem"))
	{
		QString path = conf.value("volumeFileSystem").toString();
		auto pos = path.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			QString str = path.mid(start, pos - start);
			volumeFileSystem.insert(str[0].toLatin1(), str[1].toLatin1());
			start = pos + 1;
			pos = path.indexOf('*', pos + 1);
		}
	}
	m.unlock();
}

void Configuration::BeforeQuit()
{
	qDebug() << "Call BeforeQuit";
	m.lockForRead();
	QSettings conf(QCoreApplication::applicationDirPath() + "/conf/ccs.ini", QSettings::IniFormat);
	conf.setValue("autoSign", autoSign);
	conf.setValue("onlineEnable", onlineEnable);
	if (!onlineEnable)
	{
		username.clear();
		password.clear();
	}
	conf.setValue("username", username);
	conf.setValue("password", password);
	conf.setValue("posX", posX);
	conf.setValue("posY", posY);
	conf.setValue("width", width);
	conf.setValue("height", height);
	conf.setValue("autoUpdateTime", autoUpdateTime);
	conf.setValue("filterShow", filterShow);
	conf.setValue("infoShow", infoShow);
	conf.setValue("searchCaseSensitive", searchCaseSensitive);
	conf.setValue("searchMatchPath", searchMatchPath);
	conf.setValue("searchMatchFile", searchMatchFile);
	conf.setValue("searcRegEx", searcRegEx);
	conf.setValue("runInBackground", runInBackground);
	conf.setValue("trayShow", trayShow);
	conf.setValue("oneClickShow", oneClickShow);
	conf.setValue("selectAll", selectAll);
	conf.setValue("autoUpdate", autoUpdate);
	QString path;
	for (auto i : ignorePath)
	{
		path += i % '*';
	}
	conf.setValue("ignorePath", path);
	path.clear();
	for (auto i : monitorPath)
	{
		path += i % '*';
	}
	conf.setValue("monitorPath", path);
	path.clear();
	for (auto i : compressedSuffix)
	{
		path += i % '*';
	}
	conf.setValue("compressedSuffix", path);
	path.clear();
	for (auto i : documentSuffix)
	{
		path += i % '*';
	}
	conf.setValue("documentSuffix", path);
	path.clear();
	for (auto i : picutreSuffix)
	{
		path += i % '*';
	}
	conf.setValue("picutreSuffix", path);
	path.clear();
	for (auto i : audioSuffix)
	{
		path += i % '*';
	}
	conf.setValue("audioSuffix", path);
	path.clear();
	for (auto i : videoSuffix)
	{
		path += i % '*';
	}
	conf.setValue("videoSuffix", path);
	path.clear();
	for (auto i = volumeFileSystem.begin(); i != volumeFileSystem.end(); ++i)
	{
		path += QString("%1%2*").arg(i.key()).arg(i.value());
	}
	conf.setValue("volumeFileSystem", path);
	m.unlock();
}

bool Configuration::IsSigned()
{
	return isSigned;
}

void Configuration::SetIsSigned(bool res)
{
	m.lockForWrite();
	isSigned = res;
	m.unlock();
}

bool Configuration::AutoSign()
{
	return autoSign;
}

void Configuration::SetAutoSign(bool res)
{
	m.lockForWrite();
	autoSign = res;
	m.unlock();
}

QString Configuration::ServerAddress()
{
	return serverAddress;
}

int Configuration::UserId()
{
	return userid;
}

void Configuration::SetUserId(int id)
{
	m.lockForWrite();
	userid = id;
	m.unlock();
}

int Configuration::Power()
{
	return power;
}

void Configuration::SetPower(int pow)
{
	m.lockForWrite();
	power = pow;
	m.unlock();
}

int Configuration::OrganizationId()
{
	return organizationId;
}

void Configuration::SetOrganizationId(int id)
{
	m.lockForWrite();
	organizationId = id;
	m.unlock();
}

QString Configuration::OrganizationName()
{
	return organizationName;
}

void Configuration::SetOrganizationName(QString name)
{
	m.lockForWrite();
	organizationName = name;
	m.unlock();
}

int Configuration::Status()
{
	return status;
}

void Configuration::SetStatus(int sta)
{
	m.lockForWrite();
	status = sta;
	m.unlock();
}

int Configuration::OrganizationStatus()
{
	return organizationStatus;
}

void Configuration::SetOrganizationStatus(int sta)
{
	m.lockForWrite();
	organizationStatus = sta;
	m.unlock();
}

QString Configuration::Username()
{
	return username;
}

void Configuration::SetUsername(QString usn)
{
	m.lockForWrite();
	username = usn;
	m.unlock();
}

QString Configuration::Password()
{
	return password;
}

void Configuration::SetPassword(QString pwd)
{
	m.lockForWrite();
	password = pwd;
	m.unlock();
}

int Configuration::PosX()
{
	return posX;
}

void Configuration::SetPosX(int pos)
{
	m.lockForWrite();
	posX = pos;
	m.unlock();
}

int Configuration::PosY()
{
	return posY;
}

void Configuration::SetPosY(int pos)
{
	m.lockForWrite();
	posY = pos;
	m.unlock();
}

int Configuration::Width()
{
	return width;
}

void Configuration::SetWidth(int wid)
{
	m.lockForWrite();
	width = wid;
	m.unlock();
}

int Configuration::Height()
{
	return height;
}

void Configuration::SetHeight(int hei)
{
	m.lockForWrite();
	height = hei;
	m.unlock();
}

QString Configuration::CloudConf()
{
	return cloudConf;
}

void Configuration::SetCloudConf(QString clo)
{
	m.lockForWrite();
	cloudConf = clo;
	m.unlock();
}

int Configuration::AutoUpdateTime()
{
	return autoUpdateTime;
}

void Configuration::SetAutoUpdateTime(int time)
{
	m.lockForWrite();
	autoUpdateTime = time;
	m.unlock();
}

bool Configuration::OnlineEnable()
{
	return onlineEnable;
}

void Configuration::SetOnlineEnable(bool res)
{
	m.lockForWrite();
	onlineEnable = res;
	m.unlock();
}

bool Configuration::FilterShow()
{
	return filterShow;
}

void Configuration::SetFilterShow(bool res)
{
	m.lockForWrite();
	filterShow = res;
	m.unlock();
}

bool Configuration::InfoShow()
{
	return infoShow;
}

void Configuration::SetInfoShow(bool res)
{
	m.lockForWrite();
	infoShow = res;
	m.unlock();
}

bool Configuration::SearchCaseSensitive()
{
	return searchCaseSensitive;
}

void Configuration::SetSearchCaseSensitive(bool res)
{
	m.lockForWrite();
	searchCaseSensitive = res;
	m.unlock();
}

bool Configuration::SearchMatchPath()
{
	return searchMatchPath;
}

void Configuration::SetSearchMatchPath(bool res)
{
	m.lockForWrite();
	searchMatchPath = res;
	m.unlock();
}

bool Configuration::SearchMatchFile()
{
	return searchMatchFile;
}

void Configuration::SetSearchMatchFile(bool res)
{
	m.lockForWrite();
	searchMatchFile = res;
	m.unlock();
}

bool Configuration::SearcRegEx()
{
	return searcRegEx;
}

void Configuration::SetSearcRegEx(bool res)
{
	m.lockForWrite();
	searcRegEx = res;
	m.unlock();
}

bool Configuration::RunInBackground()
{
	return runInBackground;
}

void Configuration::SetRunInBackground(bool res)
{
	m.lockForWrite();
	runInBackground = res;
	m.unlock();
}

bool Configuration::TrayShow()
{
	return trayShow;
}

void Configuration::SetTrayShow(bool res)
{
	m.lockForWrite();
	trayShow = res;
	m.unlock();
}

bool Configuration::OneClickShow()
{
	return oneClickShow;
}

void Configuration::SetOneClickShow(bool res)
{
	m.lockForWrite();
	oneClickShow = res;
	m.unlock();
}

bool Configuration::SelectAll()
{
	return selectAll;
}

void Configuration::SetSelectAll(bool res)
{
	m.lockForWrite();
	selectAll = res;
	m.unlock();
}

bool Configuration::AutoUpdate()
{
	return autoUpdate;
}

void Configuration::SetAutoUpdate(bool res)
{
	m.lockForWrite();
	autoUpdate = res;
	m.unlock();
}

QSet<QString> Configuration::IgnorePath()
{
	return ignorePath;
}
void Configuration::ReSetIgnorePath()
{
	m.lockForWrite();
	ignorePath.clear();
	m.unlock();
}
;

void Configuration::SetIgnorePath(QStringList path)
{
	m.lockForWrite();
	ignorePath.clear();
	for (auto i : path)
		ignorePath.insert(i);
	m.unlock();
}

QSet<QString> Configuration::MonitorPath()
{
	return monitorPath;
}

void Configuration::ReSetMonitorPath()
{
	m.lockForWrite();
	monitorPath.clear();
	m.unlock();
}

void Configuration::SetMonitorPath(QStringList path)
{
	m.lockForWrite();
	monitorPath.clear();
	for (auto i : path)
		monitorPath.insert(i);
	m.unlock();
}

QSet<QString> Configuration::CompressedSuffix()
{
	return compressedSuffix;
}

QSet<QString> Configuration::DocumentSuffix()
{
	return documentSuffix;
}

QSet<QString> Configuration::PicutreSuffix()
{
	return picutreSuffix;
}

QSet<QString> Configuration::AudioSuffix()
{
	return audioSuffix;
}

QSet<QString> Configuration::VideoSuffix()
{
	return videoSuffix;
}

QMap<char, __int8> Configuration::VolumeFileSystem()
{
	return volumeFileSystem;
}

void Configuration::AddVolumeFileSystem(char vol, __int8 attr)
{
	if (volumeFileSystem.contains(vol))
		return;
	m.lockForWrite();
	volumeFileSystem.insert(vol, attr);
	m.unlock();
	return;
}

void Configuration::SetVolumeFileSystem(char vol, __int8 attr)
{
	if (!volumeFileSystem.contains(vol))
		return;
	m.lockForWrite();
	volumeFileSystem[vol] = attr;
	m.unlock();
	return;
}