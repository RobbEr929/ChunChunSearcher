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
#include "myserver.h"
#include "MyClient.h"
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
#include <QProgressBar>
#include <QStringListModel>
#include <QTextEdit>
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
	void InitPersonal();
	void InitOrganization();
	void InitAdmin();
	void InitUpLoad();
	void InitOperatorFile();
	void InitOperatorMember();
	void InitOperatorAppealMember();
	void InitOperatorAdminFile();
	void InitOperatorAdminUser();
	void InitOperatorAdminOrganization();
	void InitCommunicate();
	void InitChat();
	void InitServer();
	void InitClient();
	void InitConnect();
	void Show();
	QString Status(int num);
	QString Power(int num);
	Ui::MainWindow* ui;
	QMenu* menu1, * menu2, * menu3, * menu4, * menu5, * rightMenu;
	QAction* actiont_1, * actiont_2, * actiont_3, * actiont_4, * action1_1, * action1_2, * action1_3, * action2_1, * action2_2, * action3_1, * action3_2, * action3_3, * action3_4, * action4_1, * action4_2, * action4_3, * action4_4, * action4_5, * action4_6, * action5_1, * action5_2, * actionv_1, * actionv_2, * actionb_1, * actionb_2, * actiona_1, * actionr_1, * actionr_2, * actionr_3, * actionr_4, * actionr_5, * actionr_6, * actionr_7;
	QLabel* infoLabelLeft, * lab_q, * laba_7, * laba_8, * laba_9, * laba_10, * lab_s_f, * lab_r_f, * lab_a_u, * lab_a_s, * lab_a_p, * lab_a_o, * lab_o_i, * lab_o_n, * lab_o_s, * lab_o_p, * appealFileLab, * nowPoweLab, * belongToLab, * connectCountLab;
	QSystemTrayIcon* trayIcon;
	QComboBox* filter;
	QCheckBox* boxi_1, * boxi_2, * boxi_3, * boxi_4, * boxi_5, * boxs_1, * boxs_2, * boxs_3, * boxs_4, * boxs_5, * boxv_1, * boxv_2, * boxv_3;
	QSpinBox* autoTimeBox;
	QRadioButton* button_autosign;
	MyLineEdit* line;
	QLineEdit* nameLine, * passLine, * organizationLine, * joinOrganizationLine, * serverPortEdit, * clientAddressEdit, * clientPortEdit;
	QTextEdit* clientInputEdit;
	QTableView* tableView, * ntfsVolumeView, * otherVolumeView, * fileView, * userFileView, * organizationFileView, * organizationMemberView, * organizationAppealView, * fileAdminView, * userAdminView, * organizationAdminView;
	QListView* ignoreView, * monitorView, * serverView, * clientView;
	QPushButton* button_s, * button_r, * button_skip, * button_f, * buttonv_n_1, * buttonv_o_1, * buttoni_1, * buttonm_1, * buttonm_2, * buttoni_2, * optionButtonYes, * optionButtonNo, * upLoadUserButton, * upLoadOrganizationButton, * getConfButton, * writeConfButton, * downLoadFileButton, * appealFileButton, * deleteFileButton, * closeFileButton, * appealUserButton, * kickOutButton, * upPowerButton, * lowPowerButton, * createOrgizationButton, * leaveOrganizationButton, * dissolveOrganizationButton, * joinOrganizationButton, * closeMemberButton, * closeUpLoadButton, * appealJoinButton, * refuseJoinButton, * closeAppealButton, * downLoadFileAdminButton, * banFileAdminButton, * resetFileAdminButton, * closeFileAdminButton, * banUserAdminButton, * resetUserAdminButton, * closeUserAdminButton, * banOrganizationAdminButton, * resetOrganizationAdminButton, * closeOrganizationAdminButton, * openServerButton, * openClientButton, * serverPortButton, * clientButton, * sendMessageButton;
	MyTableModel* viewModel, * ntfsVolumeModel, * otherVolumeModel, * userFileModel, * organizationFileModel, * organizationMemberModel, * organizationAppealModel, * fileAdminModel, * userAdminModel, * organizationAdminModel;
	MyListModel* ignoreModel, * monitorModel;
	QStringListModel* serverModel, * clientModel;
	QWidget* sign, * about, * option, * options[3], * generalOptions[3], * indexOptions[3], * personal, * infoPersonal[3], * organization, * infoOrganization[5], * admin, * infoAdmin[3], * upLoad, * operatorFile, * operatorMember, * operatorAppealMember, * operatorAdminFile, * operatorAdminUser, * operatorAdminOrganization, * chatWidget, * serverWidget, * clientWidget;
	QTabWidget* optionTab, * generalOptionTab, * indexOptionTab, * personalTab, * organizationTab, * adminTab;
	QProgressBar* downLoadFileBar, * upLoadFileBar, * downLoadFileAdminBar;
	QVector<Volume*> volume;
	FileSystem* fileSystem;
	Info* infoLeft;
	QTimer* autoUpdate;
	Communicate* com;
	Monitor* monitor;
	QThread* fileThread, * infoThread, * monitorThread, * comThread, * serverThread, * clientThread;
	QVector<QThread*>volumeThread;
	quint8 nowType, totalTimes, nowTimes, reInitTimes, updateTimes;
	QTime time;
	QList<QStringList> list;
	qulonglong rightFileNumber;
	MyServer* server;
	MyClient* client;
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
	void GetUserInfo();
	void AppealUser();
	void UpLoadUserFile(QString path);
	void UpLoadOrganizationFile(QString path);
	void ShowUserFile();
	void ShowOrganizationFile();
	void GetOrganizationMembers();
	void ShowAppealOrganization();
	void ShowOrganization();
	void ShowUser();
	void ShowFile();
	void DownLoadFile(int id);
	void BanFile(int id);
	void AppealFile(int id);
	void ResetFile(int id);
	void DeleteUserFile(int id);
	void DeleteOrganizationFile(int id);
	void CreateOrganization(QString);
	void LeaveOrganization(int id);
	void DissolveOrganization(int id);
	void UpOrganizationMemberPower(int id);
	void LowOrganizationMemberPower(int id);
	void ApplyJoinOrganization(int id);
	void JoinOrganization(int id);
	void RefuseOrganization(int id);
	void BanUser(int id);
	void ResetUser(int id);
	void BanOrganization(int id);
	void ResetOrganization(int id);
	void ServerInit();
	void ServerClose();
	void ClientInit();
	void ClientClose();
	void SendMessageToServer(QString str);

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
	void UpLoadFile();
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
	void WriteConfEvent(bool res);
	void SkipTriggered();
	void UpdateMenu();
	void WriteToConf();
	void SignOut();
	void PersonalTriggered();
	void OrganizationTriggered();
	void AdminTriggered();
	void ChatTriggered();
	void GetUserInfoEvent(bool res);
	void LeaveOrganizationEvent(bool res);
	void AppealUserEvent(bool res);
	void AppealFileEvent(bool res);
	void UpLoadUserFile();
	void UpLoadOrganizationFile();
	void UpLoadUserFileEvent(bool res);
	void UpLoadOrganizationFileEvent(bool res);
	void WriteConfClicked();
	void GetConfClicked();
	void ShowUserFileEvent(QJsonArray obj);
	void ShowOrganizationFileEvent(QJsonArray obj);
	void GetOrganizationMembersEvent(QJsonArray obj);
	void OperatorFile();
	void DownLoadFileEvent(bool res);
	void DeleteUserFileEvent(bool res);
	void DeleteOrganizationFileEvent(bool res);
	void CloseFileOperatorEvent();
	void CloseMemberOperatorEvent();
	void DownLoadProgressEvent(qint64 bytesSent, qint64 bytesTotal);
	void UpLoadUserProgressEvent(qint64 bytesSent, qint64 bytesTotal);
	void DownLoadAdminProgressProgressEvent(qint64 bytesSent, qint64 bytesTotal);
	void AppealUserClicked();
	void UpdatePersonal();
	void OperatorOrganizationMembers();
	void CreateOrganization();
	void UpdateOrganization();
	void UpOrganizationMemberPowerEvent(bool res);
	void LowOrganizationMemberPowerEvent(bool res);
	void CloseUpLoadEvent();
	void ApplyJoinOrganization();
	void LeaveOrganization();
	void DissolveOrganization();
	void CreateOrgizationEvent(bool res);
	void ApplyJoinOrganizationEvent(bool res);
	void DissolveOrganizationEvnet(bool res);
	void ShowAppealOrganizationEvent(QJsonArray obj);
	void JoinOrganizationEvent(bool res);
	void RefuseOrganizationEvent(bool res);
	void CloseAppealMemberOperatorEvent();
	void CloseFileOperatorAdminEvent();
	void CloseUserOperatorAdminEvent();
	void CloseOrganizationOperatorAdminEvent();
	void OperatorAppealMembers();
	void ClearModelExcept(int index = 0, int tab = 0);
	void ShowFileEvent(QJsonObject obj);
	void ShowUserEvent(QJsonArray obj);
	void ShowOrganizationEvent(QJsonArray obj);
	void AdminOperatorFile();
	void AdminOperatorUser();
	void AdminOperatorOrganization();
	void BanFileEvent(bool res);
	void ResetFileEvent(bool res);
	void BanUserEvent(bool res);
	void ResetUserEvent(bool res);
	void BanOrganizationEvent(bool res);
	void ResetOrganizationEvent(bool res);
	void SetListenPort();
	void AddRowInServerModel(QString str);
	void UpdateConnectNum();
	void InitServerEvent(bool res);
	void CloseServerEvent(bool res);
	void SetClientHostAndPort();
	void AddRowInClientModel(QString str);
	void SendOutMessage();
	void BeginConversation();
	void ClientErrorEvent();
};

#endif // MAINWINDOW_H
