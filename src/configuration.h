#ifndef CCS_SETTING_H
#define CCS_SETTING_H
#include "global.h"
#include <QSettings>
#include <QSet>

extern QReadWriteLock m;
using namespace ccs;
class Configuration
{
public:
	static void Init();
	static void BeforeQuit();
	static int PosX();
	static void SetPosX(int pos);
	static int PosY();
	static void SetPosY(int pos);
	static int Width();
	static void SetWidth(int wid);
	static int Height();
	static void SetHeight(int hei);
	static int AutoUpdateTime();
	static void SetAutoUpdateTime(int time);
	static bool FilterShow();
	static void SetFilterShow(bool res);
	static bool InfoShow();
	static void SetInfoShow(bool res);
	static bool SearchCaseSensitive();
	static void SetSearchCaseSensitive(bool res);
	static bool SearchMatchPath();
	static void SetSearchMatchPath(bool res);
	static bool SearchMatchFile();
	static void SetSearchMatchFile(bool res);
	static bool SearcRegEx();
	static void SetSearcRegEx(bool res);
	static bool RunInBackground();
	static void SetRunInBackground(bool res);
	static bool TrayShow();
	static void SetTrayShow(bool res);
	static bool OneClickShow();
	static void SetOneClickShow(bool res);
	static bool SelectAll();
	static void SetSelectAll(bool res);
	static bool AutoUpdate();
	static void SetAutoUpdate(bool res);
	static QSet<QString> IgnorePath();
	static void SetIgnorePath(QStringList path);
	static QSet<QString> MonitorPath();
	static void SetMonitorPath(QStringList path);
	static QSet<QString> CompressedSuffix();
	static QSet<QString> DocumentSuffix();
	static QSet<QString> PicutreSuffix();
	static QSet<QString> AudioSuffix();
	static QSet<QString> VideoSuffix();
	static QMap<char, __int8> VolumeFileSystem();
	static void AddVolumeFileSystem(char vol, __int8 attr);
	static void SetVolumeFileSystem(char vol, __int8 attr);

private:
	static int posX;
	static int posY;
	static int width;
	static int height;
	static int autoUpdateTime;
	static bool filterShow;
	static bool infoShow;
	static bool searchCaseSensitive;
	static bool searchMatchPath;
	static bool searchMatchFile;
	static bool searcRegEx;
	static bool runInBackground;
	static bool trayShow;
	static bool oneClickShow;
	static bool selectAll;
	static bool autoUpdate;
	static QSet<QString> ignorePath;
	static QSet<QString> monitorPath;
	static QSet<QString> compressedSuffix;
	static QSet<QString> documentSuffix;
	static QSet<QString> picutreSuffix;
	static QSet<QString> audioSuffix;
	static QSet<QString> videoSuffix;
	static QMap<char, __int8> volumeFileSystem;
};

#endif
