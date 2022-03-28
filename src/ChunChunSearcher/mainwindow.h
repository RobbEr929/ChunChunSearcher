#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "easylogging++.h"
#include "global.h"
#include "filehunter.h"
#include "info.h"
#include "identify.h"
#include "communicate.h"
#include "configuration.h"
#include "monitor.h"
#include "mylineedit.h"
#include "mytablemodel.h"
#include "mylistmodel.h"
#include <QApplication>
#include <QWidget>
#include <QThread>
#include <QMainWindow>
#include <QMenuBar>
#include <QCheckBox>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QLineEdit>
#include <QCloseEvent>
#include <QComboBox>
#include <QSpinBox>
#include <QDesktopWidget>
#include <QTableView>
#include <QListView>
#include <QRadioButton>
#include <QTime>
#include <QSystemTrayIcon>
#include <QVariant>
#include <QPushButton>
#include <QResizeEvent>
#include <QStringBuilder>

extern QReadWriteLock m;

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	void Init();
	void Start();
	~MainWindow();

protected:
	void closeEvent(QCloseEvent* event);
	void resizeEvent(QResizeEvent* event);
	bool eventFilter(QObject* obj, QEvent* event);

private:
	void InitWindow();
	void InitAutoUpdate();
	void InitTray();
	void InitMenu();
	void InitButton();
	void InitInput();
	void InitFilter();
	void InitBottomInfo();
	void InitMonitor();
	void InitData();
	void InitView();
	void InitViewRightMenu();
	void InitOption();
	void InitAbout();
	void InitSign();
	void InitCommunicate();
	void InitQuit();
	void InitConnect();
	void Show();
	Ui::MainWindow* ui;
	QMenu* menu1, * menu2, * menu3, * menu4, * menu5, * rightMenu;
	QAction* actiont_1, * actiont_2, * actiont_3, * actiont_4, * action1_1, * action1_2, * action1_3, * action2_1, * action2_2, * action3_1, * action3_2, * action3_3, * action3_4, * action4_1, * action4_2, * action5_1, * action5_2, * actionv_1, * actionv_2, * actionb_1, * actionb_2, * actiona_1, * actionr_1, * actionr_2, * actionr_3, * actionr_4, * actionr_5, * actionr_6;
	QLabel* infoLabelLeft, * lab_q, * laba_7, * laba_8, * laba_9, * laba_10, * lab_s_f, * lab_r_f;
	QSystemTrayIcon* trayIcon;
	QComboBox* filter;
	QCheckBox* boxi_1, * boxi_2, * boxi_3, * boxi_4, * boxi_5, * boxs_1, * boxs_2, * boxs_3, * boxs_4, * boxs_5, * boxv_1, * boxv_2, * boxv_3;
	QSpinBox* autoTimeBox;
	QRadioButton* button_autosign;
	MyLineEdit* line;
	QLineEdit* nameLine, * passLine;
	QTableView* tableView, * ntfsVolumeView, * otherVolumeView;
	QListView* ignoreView, * monitorView;
	QPushButton* button_s, * button_r, * button_skip, * button_f, * buttonv_n_1, * buttonv_o_1, * buttoni_1, * buttonm_1, * buttonm_2, * buttoni_2, * optionButtonYes, * optionButtonNo;
	MyTableModel* viewModel, * ntfsVolumeModel, * otherVolumeModel;
	MyListModel* ignoreModel, * monitorModel;
	QWidget* sign, * about, * option, * options[3], * generalOptions[3], * indexOptions[3], * quit;
	QTabWidget* optionTab, * generalOptionTab, * indexOptionTab;
	QVector<Volume*> volume;
	FileSystem* fileSystem;
	Info* infoLeft, * infoQuit;
	QTimer* autoUpdate;
	Communicate* com;
	Monitor* monitor;
	QThread* fileThread, * infoThread, * quitInfoThread, * monitorThread, * comThread;
	QVector<QThread*>volumeThread;
	quint8 nowType, totalTimes, nowTimes, reInitTimes, updateTimes;
	QTime time;
	QList<ModelItem> list;
	qulonglong rightFileNumber;
	bool PrepareOk;

signals:
	void Begin();
	void GetFileNameBegin();
	void FindBegin(QVariant str);
	void GetFileBegin(QVariant var);
	void ReInit(char c);
	void RemoveData(char c);
	void SomeDeleted(QString path);
	void EmitInfo(QString str);
	void RetryToOnline();
	void Sign();
	void Register();
	void GetConf();
	void WriteConf();

public slots:
	void InitVolume();
	void AfterInit();
	void AfterReInit(bool res);
	void AfterFind(char vol);
	void UpdateBegin();
	void UpdateEnd();
	void FindTriggered();
	void QuitEvent();
	void WriteSetting();
	void FilterTriggered();
	void InfoTriggered();
	void FilterEvent(int index);
	void TrayEvent(QSystemTrayIcon::ActivationReason res);
	void AboutTriggered();
	void OptionTriggered();
	void HelpTriggered();
	void OptionToSubmit();
	void OptionCancel();
	void SearchCaseSensitiveTriggered();
	void SearchMatchPathTriggered();
	void SearchMatchFileTriggered();
	void SearcRegExTriggered();
	void RightClicked(const QPoint& pos);
	void OpenFile();
	void OpenPath();
	void CopyFullPath();
	void CopyPath();
	void Delete();
	void Attribute();
	void VolumeNtfsStateChange();
	void VolumeOtherStateChange();
	void IgnorePathAdd();
	void IgnorePathRemove();
	void MonitorPathAdd();
	void MonitorPathRemove();
	void OneClickShowTriggered();
	void AutoUpdateTriggered();
	void Update();
	void SignWidgetTriggered();
	void SignTriggered();
	void RegisterTriggered();
	void OnlineEvent(bool res);
	void SignEvent(bool res);
	void RegisterEvent(bool res);
	void GetConfEvent(bool res);
	void WriteEvent(bool res);
	void SkipTriggered();
	void UpdateMenu();
	void WriteToConf();
	void SignOut();
};

#endif // MAINWINDOW_H
