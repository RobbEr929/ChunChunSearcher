#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFileInfo>
#include <QDesktopServices>
#include <QClipboard>
#include <QDir>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
using namespace ccs;

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	nowType = FILTER_ALL;

	ui->setupUi(this);
	this->setWindowTitle("ChunChunSearcher");
	this->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	qApp->setQuitOnLastWindowClosed(false);
}

void MainWindow::Init()
{
	LOG(INFO) << "======== Chun Chun Searcher Logging ========";
	InitWindow();
	InitAutoUpdate();
	InitTray();
	InitMenu();
	InitButton();
	InitInput();
	InitFilter();
	InitBottomInfo();
	InitMonitor();
	InitData();
	InitView();
	InitViewRightMenu();
	InitOption();
	InitAbout();
	InitSign();
	InitPersonal();
	InitOrganization();
	InitAdmin();
	InitCommunicate();
	InitUpLoad();
	InitOperatorFile();
	InitOperatorMember();
	InitOperatorAppealMember();
	InitOperatorAdminFile();
	InitOperatorAdminUser();
	InitOperatorAdminOrganization();
	InitChat();
	InitServer();
	InitClient();
	InitConnect();
	Show();
}

void MainWindow::Start()
{
	qDebug() << "Call MainThread Start";
	emit Begin();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	qDebug() << "Call MainThread closeEvent";
	if (Configuration::RunInBackground())
	{
		hide();
		event->ignore();
	}
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	qDebug() << "Call MainThread resizeEvent";
	button_f->move(this->width() - 101, 30);

	line->move(this->width() * 0.005, 30);
	if (Configuration::FilterShow())
		line->resize((this->width() - 200) * 0.99, 30);
	else
		line->resize((this->width() - 100) * 0.99, 30);

	filter->move(this->width() - 202, 30);

	infoLabelLeft->move(0, this->height() - 30);

	tableView->move(0, 63);
	tableView->resize(this->width(), this->height() - 90);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == laba_7)
	{
		if (event->type() == QEvent::Enter)
		{
			if (!laba_9->isVisible())
			{
				laba_9->setVisible(true);
			}
		}
		else if (event->type() == QEvent::Leave)
		{
			if (laba_9->isVisible())
			{
				laba_9->setVisible(false);
			}
		}
	}
	else if (obj == laba_8)
	{
		if (event->type() == QEvent::Enter)
		{
			if (!laba_10->isVisible())
			{
				laba_10->setVisible(true);
			}
		}
		else if (event->type() == QEvent::Leave)
		{
			if (laba_10->isVisible())
			{
				laba_10->setVisible(false);
			}
		}
	}
	return QObject::eventFilter(obj, event);
}

void MainWindow::InitWindow()
{
	qDebug() << "Call MainThread InitWindow";
	int w = Configuration::Width();
	int h = Configuration::Height();
	if (w == -1)
	{
		w = QApplication::desktop()->width() * 0.5;
		Configuration::SetWidth(w);
	}
	if (h == -1)
	{
		h = QApplication::desktop()->height() * 0.7;
		Configuration::SetHeight(h);
	}
	this->resize(w, h);
	int x = Configuration::PosX();
	int y = Configuration::PosY();
	if (x == -1)
	{
		x = QApplication::desktop()->width() * 0.25;
		Configuration::SetPosX(x);
	}
	if (y == -1)
	{
		y = QApplication::desktop()->height() * 0.15;
		Configuration::SetPosY(y);
	}
	this->move(x, y);
}

void MainWindow::InitAutoUpdate()
{
	qDebug() << "Call MainThread InitAutoUpdate";
	autoUpdate = new QTimer;
}

void MainWindow::InitTray()
{
	qDebug() << "Call MainThread InitTray";
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	trayIcon->setToolTip(QStringLiteral("ChunChunSearcher"));

	QMenu* trayMenu = new QMenu(this);

	actiont_1 = new QAction(QStringLiteral("设置"));
	actiont_2 = new QAction(QStringLiteral("查看帮助"));
	actiont_3 = new QAction(QStringLiteral("关于"));
	actiont_4 = new QAction(QStringLiteral("退出"));

	trayMenu->addAction(actiont_1);
	trayMenu->addSeparator();
	trayMenu->addAction(actiont_2);
	trayMenu->addAction(actiont_3);
	trayMenu->addSeparator();
	trayMenu->addAction(actiont_4);

	trayIcon->setContextMenu(trayMenu);

	if (Configuration::TrayShow())
	{
		trayIcon->setVisible(true);
	}
	else
	{
		trayIcon->setVisible(false);
	}
}

void MainWindow::InitMenu()
{
	qDebug() << "Call MainThread InitMenu";
	menu1 = menuBar()->addMenu(QStringLiteral("系统"));
	menu2 = menuBar()->addMenu(QStringLiteral("视图"));
	menu3 = menuBar()->addMenu(QStringLiteral("搜索"));
	menu4 = menuBar()->addMenu(QStringLiteral("网络"));
	menu5 = menuBar()->addMenu(QStringLiteral("帮助"));

	action1_1 = new QAction(QStringLiteral("选项"));
	action1_2 = new QAction(QStringLiteral("关闭"));
	action1_3 = new QAction(QStringLiteral("退出"));
	action2_1 = new QAction(QStringLiteral("筛选器"));
	action2_2 = new	QAction(QStringLiteral("提示信息"));
	action3_1 = new QAction(QStringLiteral("大小写敏感"));
	action3_2 = new QAction(QStringLiteral("匹配路径"));
	action3_3 = new QAction(QStringLiteral("匹配文件"));
	action3_4 = new QAction(QStringLiteral("正则表达式"));
	action4_1 = new QAction(QStringLiteral("注册/登录"));
	action4_2 = new QAction(QStringLiteral("个人"));
	action4_3 = new QAction(QStringLiteral("组织"));
	action4_4 = new QAction(QStringLiteral("通信"));
	action4_5 = new QAction(QStringLiteral("管理"));
	action4_6 = new QAction(QStringLiteral("登出"));
	action5_1 = new QAction(QStringLiteral("查看帮助"));
	action5_2 = new QAction(QStringLiteral("关于 ChunChunSearcher"));

	action1_1->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	action1_2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
	action1_3->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
	action3_1->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
	action3_2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	action3_3->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
	action3_4->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
	action5_1->setShortcut(QKeySequence(Qt::Key_F1));
	action5_2->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1));

	action2_1->setCheckable(true);
	action2_2->setCheckable(true);
	action3_1->setCheckable(true);
	action3_2->setCheckable(true);
	action3_3->setCheckable(true);
	action3_4->setCheckable(true);

	action2_1->setChecked(Configuration::FilterShow());
	action2_2->setChecked(Configuration::InfoShow());
	action3_1->setChecked(Configuration::SearchCaseSensitive());
	action3_2->setChecked(Configuration::SearchMatchPath());
	action3_3->setChecked(Configuration::SearchMatchFile());
	action3_4->setChecked(Configuration::SearcRegEx());

	menu1->addAction(action1_1);
	menu1->addSeparator();
	menu1->addAction(action1_2);
	menu1->addAction(action1_3);
	menu2->addAction(action2_1);
	menu2->addAction(action2_2);
	menu3->addAction(action3_1);
	menu3->addAction(action3_2);
	menu3->addAction(action3_3);
	menu3->addAction(action3_4);
	menu4->addAction(action4_1);
	menu5->addAction(action5_1);
	menu5->addAction(action5_2);
}

void MainWindow::InitButton()
{
	qDebug() << "Call MainThread InitButton";
	button_f = new QPushButton(this);

	button_f->move(this->width() - 101, 30);
	button_f->resize(99, 30);
	button_f->setText(QStringLiteral("查找"));

	actionb_1 = new QAction;
	actionb_1->setShortcut(Qt::Key_Enter);
	actionb_2 = new QAction;
	actionb_2->setShortcut(Qt::Key_Return);

	button_f->addAction(actionb_1);
	button_f->addAction(actionb_2);

	button_f->show();
}

void MainWindow::InitInput()
{
	qDebug() << "Call MainThread InitInput";
	line = new MyLineEdit(this);

	line->setEchoMode(QLineEdit::Normal);
	line->setAlignment(Qt::AlignLeft);
	line->setMaxLength(1024);
	if (Configuration::FilterShow())
	{
		line->resize((this->width() - 200) * 0.99, 30);
	}
	else
	{
		line->resize((this->width() - 100) * 0.99, 30);
	}
	line->move(this->width() * 0.005, 30);

	line->show();
}

void MainWindow::InitFilter()
{
	qDebug() << "Call MainThread InitFilter";
	filter = new QComboBox(this);

	filter->addItem(QStringLiteral("所有"));
	filter->addItem(QStringLiteral("文件夹"));
	filter->addItem(QStringLiteral("压缩文件"));
	filter->addItem(QStringLiteral("文档"));
	filter->addItem(QStringLiteral("图片"));
	filter->addItem(QStringLiteral("音频"));
	filter->addItem(QStringLiteral("视频"));

	filter->setVisible(Configuration::FilterShow());
	filter->move(this->width() - 202, 30);
}

void MainWindow::InitBottomInfo()
{
	qDebug() << "Call MainThread InitBottomInfo";
	infoLabelLeft = new QLabel(this);
	infoLeft = new Info(infoLabelLeft);
	infoThread = new QThread;

	infoLeft->moveToThread(infoThread);

	infoLabelLeft->setFont(QFont("Microsoft YaHei", 10, 50));
	infoLabelLeft->move(0, this->height() - 30);
	infoLabelLeft->resize(this->width(), 30);
	infoLabelLeft->setText(QStringLiteral("正在获取磁盘信息..."));
	infoLabelLeft->setVisible(Configuration::InfoShow());

	infoThread->start();
}

void MainWindow::InitMonitor()
{
	qDebug() << "Call MainThread InitMonitor";
	monitor = new Monitor;
	monitorThread = new QThread;

	for (auto i : Configuration::MonitorPath())
		monitor->AddPath(i);
	monitor->moveToThread(monitorThread);

	monitorThread->start();
}

void MainWindow::InitData()
{
	qDebug() << "Call MainThread InitData";
	fileSystem = new FileSystem;
	fileThread = new QThread;

	volume.clear();
	volumeThread.clear();
	volumeThread.shrink_to_fit();

	fileSystem->moveToThread(fileThread);

	fileThread->start();
}

void MainWindow::InitView()
{
	qDebug() << "Call MainThread InitView";
	tableView = new QTableView(this);
	viewModel = new MyTableModel(this);

	QStringList header;
	header.append(QStringLiteral("名称"));
	header.append(QStringLiteral("路径"));
	viewModel->setHeader(header);

	tableView->move(0, menu1->height() + line->height() * 1.05);
	tableView->resize(this->width(), this->height() - 90);
	tableView->setModel(viewModel);
	tableView->setSortingEnabled(true);
	tableView->horizontalHeader()->setSectionsMovable(true);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	tableView->horizontalHeader()->setSectionsClickable(true);
	tableView->horizontalHeader()->setStretchLastSection(true);
	tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	tableView->horizontalHeader()->setHighlightSections(true);
	tableView->horizontalHeader()->setVisible(true);
	tableView->verticalHeader()->setVisible(false);
	tableView->verticalHeader()->setDefaultSectionSize(15);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	tableView->setWordWrap(Qt::ElideNone);
	tableView->setColumnWidth(0, this->width() * 0.4);
	tableView->setColumnWidth(1, this->width() * 0.6);

	actionv_1 = new QAction;
	actionv_1->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_C);
	actionv_2 = new QAction;
	actionv_2->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_C);
	tableView->addAction(actionv_1);
	tableView->addAction(actionv_2);

	tableView->setVisible(true);
}

void MainWindow::InitViewRightMenu()
{
	qDebug() << "Call MainThread InitViewRightMenu";
	rightMenu = new QMenu;
	actionr_1 = rightMenu->addAction(QStringLiteral("打开"));
	actionr_2 = rightMenu->addAction(QStringLiteral("打开路径"));
	actionr_3 = rightMenu->addAction(QStringLiteral("复制全路径"));
	actionr_4 = rightMenu->addAction(QStringLiteral("复制路径"));
	rightMenu->addSeparator();
	actionr_5 = rightMenu->addAction(QStringLiteral("删除"));
	rightMenu->addSeparator();
	actionr_6 = rightMenu->addAction(QStringLiteral("属性"));
	rightMenu->addSeparator();
	actionr_7 = rightMenu->addAction(QStringLiteral("上传到云"));
	rightMenu->setVisible(false);
}

void MainWindow::InitOption()
{
	qDebug() << "Call MainThread InitOption";
	option = new QWidget;
	option->resize(QApplication::desktop()->width() * 0.15, QApplication::desktop()->height() * 0.5);
	option->setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
	option->setWindowTitle(QStringLiteral("设置ChunChunSearcher"));
	option->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	option->setFixedSize(option->width(), option->height());

	optionButtonYes = new QPushButton(option);
	optionButtonYes->setText(QStringLiteral("应用"));
	optionButtonYes->move(option->width() * 0.1, option->height() * 0.9);

	optionButtonNo = new QPushButton(option);
	optionButtonNo->setText(QStringLiteral("取消"));
	optionButtonNo->move(option->width() * 0.9 - 100, option->height() * 0.9);

	optionTab = new QTabWidget(option);
	optionTab->resize(option->width() * 0.9, option->height() * 0.85);
	optionTab->move(option->x() + option->width() * 0.05, optionTab->y());

	//general
	options[0] = new QWidget(optionTab);
	options[0]->resize(optionTab->width(), optionTab->height());
	generalOptionTab = new QTabWidget(options[0]);
	generalOptionTab->resize(options[0]->width(), options[0]->height());

	//interface
	generalOptions[0] = new QWidget(generalOptionTab);
	generalOptions[0]->resize(generalOptionTab->width(), generalOptionTab->height());
	boxi_1 = new QCheckBox(generalOptions[0]);
	boxi_1->setText(QStringLiteral("后台运行"));
	boxi_1->setToolTip(QStringLiteral("程序后台运行.如果禁用此项，则当无窗口时自动退出."));
	boxi_1->resize(150, 30);
	boxi_1->move(generalOptions[0]->width() * 0.1, generalOptions[0]->height() * 0.1);

	boxi_2 = new QCheckBox(generalOptions[0]);
	boxi_2->setText(QStringLiteral("显示托盘图标"));
	boxi_2->setToolTip(QStringLiteral("托盘图标.如果禁用此项，则不会在右下角显示托盘图标."));
	boxi_2->resize(150, 30);
	boxi_2->move(generalOptions[0]->width() * 0.1, generalOptions[0]->height() * 0.1 + 35);

	boxi_3 = new QCheckBox(generalOptions[0]);
	boxi_3->setText(QStringLiteral("单击托盘图标打开搜索窗口"));
	boxi_3->setToolTip(QStringLiteral("单击ChunChunSearcher托盘图标就会打开搜索窗口."));
	boxi_3->resize(220, 30);
	boxi_3->move(generalOptions[0]->width() * 0.1, generalOptions[0]->height() * 0.1 + 70);

	boxi_4 = new QCheckBox(generalOptions[0]);
	boxi_4->setText(QStringLiteral("点击时选中所有文字"));
	boxi_4->setToolTip(QStringLiteral("点击输入框时，自动选中所有文字."));
	boxi_4->resize(200, 30);
	boxi_4->move(generalOptions[0]->width() * 0.1, generalOptions[0]->height() * 0.1 + 105);

	boxi_5 = new QCheckBox(generalOptions[0]);
	boxi_5->setText(QStringLiteral("关闭联网功能"));
	boxi_5->setToolTip(QStringLiteral("关闭后下次打开将不会出现任何联网功能"));
	boxi_5->resize(200, 30);
	boxi_5->move(generalOptions[0]->width() * 0.1, generalOptions[0]->height() * 0.1 + 140);

	//search
	generalOptions[1] = new QWidget(generalOptionTab);
	generalOptions[1]->resize(generalOptionTab->width(), generalOptionTab->height());
	boxs_1 = new QCheckBox(generalOptions[1]);
	boxs_1->setText(QStringLiteral("区分大小写"));
	boxs_1->setToolTip(QStringLiteral("区分大小写.如果禁用则不区分大小写."));
	boxs_1->resize(150, 30);
	boxs_1->move(generalOptions[1]->width() * 0.1, generalOptions[1]->height() * 0.1);

	boxs_2 = new QCheckBox(generalOptions[1]);
	boxs_2->setText(QStringLiteral("匹配路径"));
	boxs_2->setToolTip(QStringLiteral("搜索时仅匹配路径.如果禁用则在搜索时不匹配路径\n(开启时可能搜索速度会变慢)."));
	boxs_2->resize(150, 30);
	boxs_2->move(generalOptions[1]->width() * 0.1, generalOptions[1]->height() * 0.1 + 35);

	boxs_3 = new QCheckBox(generalOptions[1]);
	boxs_3->setText(QStringLiteral("匹配文件名"));
	boxs_3->setToolTip(QStringLiteral("搜索时仅匹配文件名.如果禁用则在搜索时不匹配文件名."));
	boxs_3->resize(150, 30);
	boxs_3->move(generalOptions[1]->width() * 0.1, generalOptions[1]->height() * 0.1 + 70);

	boxs_4 = new QCheckBox(generalOptions[1]);
	boxs_4->setText(QStringLiteral("正则表达式"));
	boxs_4->setToolTip(QStringLiteral("搜索时使用正则表达式.如果禁用则不启用正则表达式."));
	boxs_4->resize(150, 30);
	boxs_4->move(generalOptions[1]->width() * 0.1, generalOptions[1]->height() * 0.1 + 105);

	boxs_5 = new QCheckBox(generalOptions[1]);
	boxs_5->setText(QStringLiteral("自动更新数据"));
	boxs_5->setToolTip(QStringLiteral("每隔一段时间自动更新(仅限NTFS卷,在卷管理中启用)数据.如果禁用则不会自动更新."));
	boxs_5->resize(150, 30);
	boxs_5->move(generalOptions[1]->width() * 0.1, generalOptions[1]->height() * 0.1 + 140);

	autoTimeBox = new QSpinBox(generalOptions[1]);
	autoTimeBox->setToolTip(QStringLiteral("建议设置10-30分钟，以免影响正常使用"));
	autoTimeBox->setPrefix(QStringLiteral("间隔"));
	autoTimeBox->setSuffix(QStringLiteral("分钟"));
	autoTimeBox->setMinimum(5);
	autoTimeBox->setSingleStep(1);
	autoTimeBox->setDisplayIntegerBase(10);
	autoTimeBox->move(generalOptions[1]->width() * 0.1, generalOptions[1]->height() * 0.1 + 175);

	//clientView
	generalOptions[2] = new QWidget(generalOptionTab);
	generalOptions[2]->resize(generalOptionTab->width(), generalOptionTab->height());

	boxv_1 = new QCheckBox(generalOptions[2]);
	boxv_1->setText(QStringLiteral("筛选器"));
	boxv_1->setToolTip(QStringLiteral("类型筛选器.如果启用可以在搜索时根据文件类型进行筛选."));
	boxv_1->resize(150, 30);
	boxv_1->move(generalOptions[2]->width() * 0.1, generalOptions[2]->height() * 0.1);

	boxv_2 = new QCheckBox(generalOptions[2]);
	boxv_2->setText(QStringLiteral("底部信息"));
	boxv_2->setToolTip(QStringLiteral("底部提示信息."));
	boxv_2->resize(150, 30);
	boxv_2->move(generalOptions[2]->width() * 0.1, generalOptions[2]->height() * 0.1 + 35);

	generalOptionTab->addTab(generalOptions[0], QStringLiteral("界面"));
	generalOptionTab->addTab(generalOptions[1], QStringLiteral("搜索"));
	generalOptionTab->addTab(generalOptions[2], QStringLiteral("视图"));

	//index
	options[1] = new QWidget(optionTab);
	options[1]->resize(optionTab->width(), optionTab->height());
	indexOptionTab = new QTabWidget(options[1]);
	indexOptionTab->resize(options[1]->width(), options[1]->height());

	//volume manage
	indexOptions[0] = new QWidget(indexOptionTab);
	indexOptions[0]->resize(indexOptionTab->width(), indexOptionTab->height());

	ntfsVolumeView = new QTableView(indexOptions[0]);
	ntfsVolumeModel = new MyTableModel(indexOptions[0]);
	QStringList header;
	header.append(QStringLiteral("卷名"));
	header.append(QStringLiteral("状态"));
	ntfsVolumeModel->setHeader(header);
	ntfsVolumeView->resize(indexOptions[0]->width() * 0.5, indexOptions[0]->height() * 0.3);
	ntfsVolumeView->move(indexOptions[0]->width() * 0.1, indexOptions[0]->height() * 0.1);
	ntfsVolumeView->setModel(ntfsVolumeModel);
	ntfsVolumeView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ntfsVolumeView->horizontalHeader()->setStretchLastSection(true);
	ntfsVolumeView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ntfsVolumeView->horizontalHeader()->setVisible(true);
	ntfsVolumeView->verticalHeader()->setVisible(false);
	ntfsVolumeView->verticalHeader()->setDefaultSectionSize(20);
	ntfsVolumeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ntfsVolumeView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ntfsVolumeView->setSelectionMode(QAbstractItemView::SingleSelection);
	ntfsVolumeView->setWordWrap(Qt::ElideNone);
	ntfsVolumeView->setColumnWidth(0, ntfsVolumeView->width() * 0.4);
	ntfsVolumeView->setColumnWidth(1, ntfsVolumeView->width() * 0.6);
	ntfsVolumeView->setVisible(true);

	QLabel* labo_v = new QLabel(indexOptions[0]);
	labo_v->setText(QStringLiteral("本地NTFS："));
	labo_v->move(indexOptions[0]->width() * 0.1, indexOptions[0]->height() * 0.05);
	labo_v->setFont(QFont("Microsoft YaHei", 8, 50));

	buttonv_n_1 = new QPushButton(indexOptions[0]);
	buttonv_n_1->setText(QStringLiteral("启用\n——\n停用"));
	buttonv_n_1->move(indexOptions[0]->width() * 0.7, indexOptions[0]->height() * 0.15);
	buttonv_n_1->resize(indexOptions[0]->width() * 0.2, 90);

	otherVolumeView = new QTableView(indexOptions[0]);
	otherVolumeModel = new MyTableModel(indexOptions[0]);
	header.clear();
	header.append(QStringLiteral("卷名"));
	header.append(QStringLiteral("状态"));
	otherVolumeModel->setHeader(header);
	otherVolumeView->resize(indexOptions[0]->width() * 0.5, indexOptions[0]->height() * 0.3);
	otherVolumeView->move(indexOptions[0]->width() * 0.1, indexOptions[0]->height() * 0.5);
	otherVolumeView->setModel(otherVolumeModel);
	otherVolumeView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	otherVolumeView->horizontalHeader()->setStretchLastSection(true);
	otherVolumeView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	otherVolumeView->horizontalHeader()->setVisible(true);
	otherVolumeView->verticalHeader()->setVisible(false);
	otherVolumeView->verticalHeader()->setDefaultSectionSize(20);
	otherVolumeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	otherVolumeView->setSelectionBehavior(QAbstractItemView::SelectRows);
	otherVolumeView->setSelectionMode(QAbstractItemView::SingleSelection);
	otherVolumeView->setWordWrap(Qt::ElideNone);
	otherVolumeView->setColumnWidth(0, otherVolumeView->width() * 0.3);
	otherVolumeView->setColumnWidth(1, otherVolumeView->width() * 0.7);
	otherVolumeView->setVisible(true);

	QLabel* labo_v_o = new QLabel(indexOptions[0]);
	labo_v_o->setText(QStringLiteral("本地其他卷："));
	labo_v_o->move(indexOptions[0]->width() * 0.1, indexOptions[0]->height() * 0.45);
	labo_v_o->setFont(QFont("Microsoft YaHei", 8, 50));

	buttonv_o_1 = new QPushButton(indexOptions[0]);
	buttonv_o_1->setText(QStringLiteral("启用\n——\n停用"));
	buttonv_o_1->move(indexOptions[0]->width() * 0.7, indexOptions[0]->height() * 0.55);
	buttonv_o_1->resize(indexOptions[0]->width() * 0.2, 90);

	//ignore path
	indexOptions[1] = new QWidget(indexOptionTab);
	indexOptions[1]->resize(indexOptionTab->width(), indexOptionTab->height());

	ignoreView = new QListView(indexOptions[1]);
	ignoreModel = new MyListModel(indexOptions[1]);
	ignoreView->resize(indexOptions[1]->width() * 0.8, indexOptions[1]->height() * 0.5);
	ignoreView->move(indexOptions[1]->width() * 0.1, indexOptions[1]->height() * 0.1);
	ignoreView->setModel(ignoreModel);
	ignoreView->setFlow(QListView::TopToBottom);
	ignoreView->setWordWrap(false);
	ignoreView->setItemAlignment(Qt::AlignLeft);
	ignoreView->setSelectionMode(QAbstractItemView::SingleSelection);

	buttoni_1 = new QPushButton(indexOptions[1]);
	buttoni_1->setText(QStringLiteral("添加"));
	buttoni_1->move(indexOptions[1]->width() * 0.1, indexOptions[1]->height() * 0.65);
	buttoni_1->resize(indexOptions[1]->width() * 0.3, 30);

	buttoni_2 = new QPushButton(indexOptions[1]);
	buttoni_2->setText(QStringLiteral("删除"));
	buttoni_2->move(indexOptions[1]->width() * 0.6, indexOptions[1]->height() * 0.65);
	buttoni_2->resize(indexOptions[1]->width() * 0.3, 30);

	//monitor path
	indexOptions[2] = new QWidget(indexOptionTab);
	indexOptions[2]->resize(indexOptionTab->width(), indexOptionTab->height());

	monitorView = new QListView(indexOptions[2]);
	monitorModel = new MyListModel(indexOptions[2]);
	monitorView->resize(indexOptions[2]->width() * 0.8, indexOptions[2]->height() * 0.5);
	monitorView->move(indexOptions[2]->width() * 0.1, indexOptions[2]->height() * 0.1);
	monitorView->setModel(monitorModel);
	monitorView->setFlow(QListView::TopToBottom);
	monitorView->setWordWrap(false);
	monitorView->setItemAlignment(Qt::AlignLeft);
	monitorView->setSelectionMode(QAbstractItemView::SingleSelection);

	buttonm_1 = new QPushButton(indexOptions[2]);
	buttonm_1->setText(QStringLiteral("添加"));
	buttonm_1->move(indexOptions[2]->width() * 0.1, indexOptions[2]->height() * 0.65);
	buttonm_1->resize(indexOptions[2]->width() * 0.3, 30);

	buttonm_2 = new QPushButton(indexOptions[2]);
	buttonm_2->setText(QStringLiteral("删除"));
	buttonm_2->move(indexOptions[2]->width() * 0.6, indexOptions[2]->height() * 0.65);
	buttonm_2->resize(indexOptions[2]->width() * 0.3, 30);

	indexOptionTab->addTab(indexOptions[0], QStringLiteral("卷管理"));
	indexOptionTab->addTab(indexOptions[1], QStringLiteral("排除路径"));
	indexOptionTab->addTab(indexOptions[2], QStringLiteral("监视路径"));

	//about
	options[2] = new QWidget(optionTab);
	options[2]->resize(optionTab->width(), optionTab->height());

	QLabel* laba_1 = new QLabel(options[2]);
	laba_1->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() % "/source/icon.png")).scaled(options[2]->width() * 0.4, options[2]->width() * 0.4));
	laba_1->resize(options[2]->width() * 0.4, options[2]->width() * 0.4);
	laba_1->move(options[2]->width() * 0.05, options[2]->width() * 0.05);

	QLabel* laba_2 = new QLabel(options[2]);
	laba_2->setText("ChunChun\nSearcher");
	laba_2->setFont(QFont("Microsoft YaHei", 12, 75));
	laba_2->move(options[2]->width() * 0.5, options[2]->width() * 0.1);

	QLabel* laba_2_b = new QLabel(options[2]);
	laba_2_b->setText(QStringLiteral("成都东软学院\n信息工程18201毕业设计"));
	laba_2_b->setFont(QFont("Microsoft YaHei", 6, 50));
	laba_2_b->move(options[2]->width() * 0.5, options[2]->width() * 0.33);

	QLabel* laba_3 = new QLabel(options[2]);
	laba_3->setText(QStringLiteral("作者 : 钟淳"));
	laba_3->setOpenExternalLinks(true);
	laba_3->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_3->setAlignment(Qt::AlignCenter);
	laba_3->move(options[2]->width() * 0.3, options[2]->width() * 0.5);

	QLabel* laba_4 = new QLabel(options[2]);
	laba_4->setText("Github:");
	laba_4->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_4->setAlignment(Qt::AlignCenter);
	laba_4->move(options[2]->width() * 0.05, options[2]->width() * 0.65);

	QLabel* laba_4_p = new QLabel(options[2]);
	laba_4_p->setText(QString("<a href=\"https://github.com/RobbEr929\"><img src=%1 width=%2 height=%3></a>").arg("./source/github.png").arg(options[2]->width() * 0.19).arg(options[2]->width() * 0.19));
	laba_4_p->setOpenExternalLinks(true);
	laba_4_p->setToolTip(QStringLiteral("点击访问"));
	laba_4_p->move(options[2]->width() * 0.1 + 60, options[2]->width() * 0.58);

	QLabel* laba_5 = new QLabel(options[2]);
	laba_5->setText(QStringLiteral("博客:"));
	laba_5->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_5->setAlignment(Qt::AlignCenter);
	laba_5->move(options[2]->width() * 0.6, options[2]->width() * 0.65);

	QLabel* laba_5_p = new QLabel(options[2]);
	laba_5_p->setText(QString("<a href=\"https://robber.ltd/\"><img src=%1 width=%2 height=%3></a>").arg("./source/blog.png").arg(options[2]->width() * 0.19).arg(options[2]->width() * 0.19));
	laba_5_p->setOpenExternalLinks(true);
	laba_5_p->setToolTip(QStringLiteral("点击访问"));
	laba_5_p->move(options[2]->width() * 0.6 + 40, options[2]->width() * 0.6);

	QLabel* laba_6 = new QLabel(options[2]);
	laba_6->setText(QStringLiteral("鼓励开发者~感谢!"));
	laba_6->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_6->setAlignment(Qt::AlignCenter);
	laba_6->move(options[2]->width() * 0.2, options[2]->width() * 0.8);

	laba_7 = new QLabel(options[2]);
	laba_7->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() % "/source/ali.png")).scaled(options[2]->width() * 0.12, options[2]->width() * 0.12));
	laba_7->setOpenExternalLinks(true);
	laba_7->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_7->setAlignment(Qt::AlignCenter);
	laba_7->move(options[2]->width() * 0.3, options[2]->width() * 0.9);
	laba_7->installEventFilter(this);

	laba_8 = new QLabel(options[2]);
	laba_8->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() % "/source/wechat.png")).scaled(options[2]->width() * 0.12, options[2]->width() * 0.12));
	laba_8->setOpenExternalLinks(true);
	laba_8->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_8->setAlignment(Qt::AlignCenter);
	laba_8->move(options[2]->width() * 0.6, options[2]->width() * 0.9);
	laba_8->installEventFilter(this);

	laba_9 = new QLabel(options[2]);
	laba_9->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() % "/source/alipay.png")).scaled(options[2]->width() * 0.6, options[2]->width() * 0.6));
	laba_9->setOpenExternalLinks(true);
	laba_9->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_9->setAlignment(Qt::AlignCenter);
	laba_9->move(options[2]->width() * 0.2, options[2]->width());
	laba_9->installEventFilter(this);
	laba_9->setVisible(false);

	laba_10 = new QLabel(options[2]);
	laba_10->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() % "/source/wechatpay.png")).scaled(options[2]->width() * 0.6, options[2]->width() * 0.6));
	laba_10->setOpenExternalLinks(true);
	laba_10->setFont(QFont("Microsoft YaHei", 10, 75));
	laba_10->setAlignment(Qt::AlignCenter);
	laba_10->move(options[2]->width() * 0.2, options[2]->width());
	laba_10->installEventFilter(this);
	laba_10->setVisible(false);

	optionTab->addTab(options[0], QStringLiteral("常规"));
	optionTab->addTab(options[1], QStringLiteral("索引"));
	optionTab->addTab(options[2], QStringLiteral("关于"));

	this->setVisible(false);
}

void MainWindow::InitAbout()
{
	qDebug() << "Call MainThread InitAbout";
	about = new QWidget(this);
	about->resize(QApplication::desktop()->width() * 0.2, QApplication::desktop()->height() * 0.2);
	about->setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
	about->setWindowTitle(QStringLiteral("关于ChunChunSearcher"));
	about->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	about->setFixedSize(about->width(), about->height());

	QLabel* label1 = new QLabel(about);
	label1->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() % "/source/icon.png")).scaled(about->height() * 0.6, about->height() * 0.6));
	label1->resize(about->height() * 0.6, about->height() * 0.6);
	label1->move(0, about->height() * 0.1);

	QLabel* label2 = new QLabel(about);
	label2->move(about->height() * 0.6, about->height() * 0.1);
	label2->setText("ChunChunSearcher");
	label2->setFont(QFont("Microsoft YaHei", 12, 75));

	QLabel* label3 = new QLabel(about);
	label3->move(about->height() * 0.6, about->height() * 0.1 + label2->height());
	label3->setText(QStringLiteral("版本 1.1.0"));
	label3->setFont(QFont("Microsoft YaHei", 10, 50));
	label3->setWordWrap(true);

	QLabel* label4 = new QLabel(about);
	label4->setOpenExternalLinks(true);
	label4->move(about->height() * 0.6, about->height() * 0.1 + label2->height() + label3->height());
	ushort* s = new ushort[2];
	s[0] = 0x00A9;
	s[1] = 0;
	label4->setText("<a href = \"https://robber.ltd/\"> Copyright " % QString::fromUtf16(s) % " 2021-2022 ZhongChun.\nAll rights reserved.</a>");
	label4->setFont(QFont("Microsoft YaHei", 10, 50));
	label4->setWordWrap(true);

	actiona_1 = new	QAction;
	actiona_1->setShortcut(Qt::Key_Escape);
	about->addAction(actiona_1);

	about->setVisible(false);
}

void MainWindow::InitSign()
{
	qDebug() << "Call MainThread InitSign";
	sign = new QWidget;
	lab_s_f = new QLabel(sign);
	lab_r_f = new QLabel(sign);
	QLabel* nameLab = new QLabel(sign);
	QLabel* passLab = new QLabel(sign);
	nameLine = new QLineEdit(sign);
	passLine = new QLineEdit(sign);
	button_autosign = new QRadioButton(sign);
	button_s = new QPushButton(sign);
	button_r = new QPushButton(sign);
	button_skip = new QPushButton(sign);

	sign->setFixedSize(300, 200);
	sign->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	lab_s_f->setText(QStringLiteral("账号或密码错误，请重试！"));
	lab_s_f->setPalette(QPalette(QPalette::WindowText, Qt::red));
	lab_s_f->move(sign->width() * 0.1, sign->height() * 0.1);
	lab_s_f->setVisible(false);
	lab_r_f->setText(QStringLiteral("注册失败，请重试！"));
	lab_r_f->setPalette(QPalette(QPalette::WindowText, Qt::red));
	lab_r_f->move(sign->width() * 0.1, sign->height() * 0.1);
	lab_r_f->setVisible(false);

	nameLab->setText(QStringLiteral("用户名"));
	nameLab->move(sign->width() * 0.1, sign->height() * 0.2);
	passLab->setText(QStringLiteral("密码"));
	passLab->move(sign->width() * 0.1, sign->height() * 0.35);

	nameLine->move(sign->width() * 0.2 + 40, sign->height() * 0.2);
	passLine->move(sign->width() * 0.2 + 40, sign->height() * 0.35);
	passLine->setEchoMode(QLineEdit::Password);

	button_autosign->setText(QStringLiteral("自动登录"));
	button_autosign->resize(120, 30);
	button_autosign->move(sign->width() * 0.1, sign->height() * 0.5);

	QAction* signAction = new QAction(sign);
	signAction->setShortcut(Qt::Key_Enter);
	button_s->setText(QStringLiteral("登录"));
	button_s->resize(50, 30);
	button_s->move(sign->width() * 0.1, sign->height() * 0.7);
	button_s->addAction(signAction);

	button_r->setText(QStringLiteral("注册"));
	button_r->resize(50, 30);
	button_r->move(sign->width() * 0.3, sign->height() * 0.7);

	button_skip->setText(QStringLiteral("游客进入"));
	button_skip->resize(100, 30);
	button_skip->move(sign->width() * 0.5, sign->height() * 0.7);

	sign->setVisible(false);
}

void MainWindow::InitPersonal()
{
	qDebug() << "Call MainThread InitPersonal";
	personal = new QWidget;
	personal->resize(QApplication::desktop()->width() * 0.5, QApplication::desktop()->height() * 0.7);
	personal->move(QApplication::desktop()->width() * 0.25, QApplication::desktop()->height() * 0.15);
	personal->setWindowTitle(QStringLiteral("个人管理"));
	personal->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	personal->setFixedSize(personal->width(), personal->height());

	personalTab = new QTabWidget(personal);
	personalTab->resize(personal->width() * 0.9, personal->height() * 0.9);
	personalTab->move(personal->width() * 0.05, personal->y() * 0.05);

	//Info
	infoPersonal[0] = new QWidget(personalTab);
	infoPersonal[0]->resize(personalTab->width(), personalTab->height());

	QLabel* labp_1 = new QLabel(infoPersonal[0]);
	labp_1->setText(QStringLiteral("您好！"));
	labp_1->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_1->setAlignment(Qt::AlignCenter);
	labp_1->move(infoPersonal[0]->width() * 0.2, infoPersonal[0]->height() * 0.1);

	QLabel* labp_2 = new QLabel(infoPersonal[0]);
	labp_2->setText(QStringLiteral("当前状态："));
	labp_2->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_2->setAlignment(Qt::AlignCenter);
	labp_2->move(infoPersonal[0]->width() * 0.2, infoPersonal[0]->height() * 0.1 + 50);

	QLabel* labp_3 = new QLabel(infoPersonal[0]);
	labp_3->setText(QStringLiteral("当前权限："));
	labp_3->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_3->setAlignment(Qt::AlignCenter);
	labp_3->move(infoPersonal[0]->width() * 0.2, infoPersonal[0]->height() * 0.1 + 100);

	QLabel* labp_4 = new QLabel(infoPersonal[0]);
	labp_4->setText(QStringLiteral("当前组织："));
	labp_4->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_4->setAlignment(Qt::AlignCenter);
	labp_4->move(infoPersonal[0]->width() * 0.2, infoPersonal[0]->height() * 0.1 + 150);

	lab_a_u = new QLabel(infoPersonal[0]);
	lab_a_u->setText(QStringLiteral("                   "));
	lab_a_u->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_a_u->setAlignment(Qt::AlignLeft);
	lab_a_u->move(infoPersonal[0]->width() * 0.2 + 60, infoPersonal[0]->height() * 0.1);
	lab_a_u->resize(infoPersonal[0]->width() * 0.6, lab_a_u->height());

	lab_a_s = new QLabel(infoPersonal[0]);
	lab_a_s->setText(QStringLiteral("                   "));
	lab_a_s->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_a_s->setAlignment(Qt::AlignLeft);
	lab_a_s->move(infoPersonal[0]->width() * 0.2 + 120, infoPersonal[0]->height() * 0.1 + 50);
	lab_a_s->resize(infoPersonal[0]->width() * 0.6, lab_a_s->height());

	lab_a_p = new QLabel(infoPersonal[0]);
	lab_a_p->setText(QStringLiteral("                   "));
	lab_a_p->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_a_p->setAlignment(Qt::AlignLeft);
	lab_a_p->move(infoPersonal[0]->width() * 0.2 + 120, infoPersonal[0]->height() * 0.1 + 100);
	lab_a_p->resize(infoPersonal[0]->width() * 0.6, lab_a_p->height());

	lab_a_o = new QLabel(infoPersonal[0]);
	lab_a_o->setText(QStringLiteral("                   "));
	lab_a_o->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_a_o->setAlignment(Qt::AlignLeft);
	lab_a_o->move(infoPersonal[0]->width() * 0.2 + 120, infoPersonal[0]->height() * 0.1 + 150);
	lab_a_o->resize(infoPersonal[0]->width() * 0.6, lab_a_o->height());

	//File
	infoPersonal[1] = new QWidget(personalTab);
	infoPersonal[1]->resize(personalTab->width(), personalTab->height());

	QStringList fileHeader;
	fileHeader << QStringLiteral("文件名")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	userFileModel = new MyTableModel(infoPersonal[1]);
	userFileModel->setHeader(fileHeader);
	userFileView = new QTableView(infoPersonal[1]);
	userFileView->setModel(userFileModel);
	userFileView->move(0, 0);
	userFileView->resize(infoPersonal[1]->width(), infoPersonal[1]->height());
	userFileView->setSortingEnabled(false);
	userFileView->horizontalHeader()->setSectionsMovable(true);
	userFileView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	userFileView->horizontalHeader()->setSectionsClickable(true);
	userFileView->horizontalHeader()->setStretchLastSection(true);
	userFileView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	userFileView->horizontalHeader()->setHighlightSections(true);
	userFileView->horizontalHeader()->setVisible(true);
	userFileView->verticalHeader()->setVisible(false);
	userFileView->verticalHeader()->setDefaultSectionSize(15);
	userFileView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	userFileView->setSelectionBehavior(QAbstractItemView::SelectRows);
	userFileView->setSelectionMode(QAbstractItemView::SingleSelection);
	userFileView->setWordWrap(Qt::ElideNone);
	userFileView->setColumnWidth(0, userFileView->width() * 0.6);
	userFileView->setColumnWidth(1, userFileView->width() * 0.2);
	userFileView->setColumnWidth(2, userFileView->width() * 0.2);

	infoPersonal[2] = new QWidget(personalTab);
	infoPersonal[2]->resize(personalTab->width(), personalTab->height());

	QLabel* laba_c = new QLabel(infoPersonal[2]);
	laba_c->setText(QStringLiteral("个人配置相关"));
	laba_c->setFont(QFont("Microsoft YaHei", 12, 75));
	laba_c->setAlignment(Qt::AlignCenter);
	laba_c->move(infoPersonal[2]->width() * 0.3, infoPersonal[2]->height() * 0.1);

	writeConfButton = new QPushButton(infoPersonal[2]);
	writeConfButton->setText(QStringLiteral("上传"));
	writeConfButton->move(infoPersonal[2]->width() * 0.2, infoPersonal[2]->height() * 0.1 + 50);
	writeConfButton->resize(infoPersonal[2]->width() * 0.2, writeConfButton->height());

	getConfButton = new QPushButton(infoPersonal[2]);
	getConfButton->setText(QStringLiteral("下载"));
	getConfButton->move(infoPersonal[2]->width() * 0.6, infoPersonal[2]->height() * 0.1 + 50);
	getConfButton->resize(infoPersonal[2]->width() * 0.2, getConfButton->height());

	QLabel* lab_a_a = new QLabel(infoPersonal[2]);
	lab_a_a->setText(QStringLiteral("个人申诉相关"));
	lab_a_a->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_a_a->setAlignment(Qt::AlignCenter);
	lab_a_a->move(infoPersonal[2]->width() * 0.3, infoPersonal[2]->height() * 0.1 + 100);

	appealUserButton = new QPushButton(infoPersonal[2]);
	appealUserButton->setText(QStringLiteral("发起申诉"));
	appealUserButton->move(infoPersonal[2]->width() * 0.2, infoPersonal[2]->height() * 0.1 + 150);
	appealUserButton->resize(infoPersonal[2]->width() * 0.2, appealUserButton->height());

	personalTab->addTab(infoPersonal[0], QStringLiteral("基本信息"));
	personalTab->addTab(infoPersonal[1], QStringLiteral("云盘文件"));
	personalTab->addTab(infoPersonal[2], QStringLiteral("管理"));
	personal->setVisible(false);
}

void MainWindow::InitOrganization()
{
	qDebug() << "Call MainThread InitOrganization";
	organization = new QWidget;
	organization->resize(QApplication::desktop()->width() * 0.5, QApplication::desktop()->height() * 0.7);
	organization->move(QApplication::desktop()->width() * 0.25, QApplication::desktop()->height() * 0.15);
	organization->setWindowTitle(QStringLiteral("组织管理"));
	organization->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	organization->setFixedSize(organization->width(), organization->height());

	organizationTab = new QTabWidget(organization);
	organizationTab->resize(organization->width() * 0.9, organization->height() * 0.9);
	organizationTab->move(organization->width() * 0.05, organization->y() * 0.05);

	//Info
	infoOrganization[0] = new QWidget(organizationTab);
	infoOrganization[0]->resize(organizationTab->width(), organizationTab->height());

	QLabel* labp_1 = new QLabel(infoOrganization[0]);
	labp_1->setText(QStringLiteral("您好！"));
	labp_1->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_1->setAlignment(Qt::AlignCenter);
	labp_1->move(infoOrganization[0]->width() * 0.2, infoOrganization[0]->height() * 0.1);

	QLabel* labp_2 = new QLabel(infoOrganization[0]);
	labp_2->setText(QStringLiteral("组织状态："));
	labp_2->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_2->setAlignment(Qt::AlignCenter);
	labp_2->move(infoOrganization[0]->width() * 0.2, infoOrganization[0]->height() * 0.1 + 50);

	QLabel* labp_3 = new QLabel(infoOrganization[0]);
	labp_3->setText(QStringLiteral("当前权限："));
	labp_3->setFont(QFont("Microsoft YaHei", 12, 75));
	labp_3->setAlignment(Qt::AlignCenter);
	labp_3->move(infoOrganization[0]->width() * 0.2, infoOrganization[0]->height() * 0.1 + 100);

	lab_o_i = new QLabel(infoOrganization[0]);
	lab_o_i->setText(QStringLiteral("您还未加入任何组织，请到组织管理处加入或创建一个组织"));
	lab_o_i->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_o_i->setAlignment(Qt::AlignCenter);
	lab_o_i->move(infoOrganization[0]->width() * 0.2 + 60, infoOrganization[0]->height() * 0.1);

	lab_o_n = new QLabel(infoOrganization[0]);
	lab_o_n->setText(QStringLiteral("                   "));
	lab_o_n->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_o_n->setAlignment(Qt::AlignLeft);
	lab_o_n->move(infoOrganization[0]->width() * 0.2 + 60, infoOrganization[0]->height() * 0.1);
	lab_o_n->resize(infoOrganization[0]->width() * 0.6, lab_o_n->height());
	lab_o_n->setVisible(false);

	lab_o_s = new QLabel(infoOrganization[0]);
	lab_o_s->setText(QStringLiteral("                   "));
	lab_o_s->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_o_s->setAlignment(Qt::AlignLeft);
	lab_o_s->move(infoOrganization[0]->width() * 0.2 + 120, infoOrganization[0]->height() * 0.1 + 50);
	lab_o_s->resize(infoOrganization[0]->width() * 0.6, lab_o_s->height());

	lab_o_p = new QLabel(infoOrganization[0]);
	lab_o_p->setText(QStringLiteral("                   "));
	lab_o_p->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_o_p->setAlignment(Qt::AlignLeft);
	lab_o_p->move(infoOrganization[0]->width() * 0.2 + 120, infoOrganization[0]->height() * 0.1 + 100);
	lab_o_p->resize(infoOrganization[0]->width() * 0.6, lab_o_p->height());

	//File
	infoOrganization[1] = new QWidget(organizationTab);
	infoOrganization[1]->resize(organizationTab->width(), organizationTab->height());

	QStringList fileHeader;
	fileHeader << QStringLiteral("文件名")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	organizationFileModel = new MyTableModel(infoOrganization[1]);
	organizationFileModel->setHeader(fileHeader);

	organizationFileView = new QTableView(infoOrganization[1]);
	organizationFileView->setModel(organizationFileModel);
	organizationFileView->move(0, 0);
	organizationFileView->resize(infoOrganization[1]->width(), infoOrganization[1]->height());
	organizationFileView->setSortingEnabled(false);
	organizationFileView->horizontalHeader()->setSectionsMovable(true);
	organizationFileView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	organizationFileView->horizontalHeader()->setSectionsClickable(true);
	organizationFileView->horizontalHeader()->setStretchLastSection(true);
	organizationFileView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	organizationFileView->horizontalHeader()->setHighlightSections(true);
	organizationFileView->horizontalHeader()->setVisible(true);
	organizationFileView->verticalHeader()->setVisible(false);
	organizationFileView->verticalHeader()->setDefaultSectionSize(15);
	organizationFileView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	organizationFileView->setSelectionBehavior(QAbstractItemView::SelectRows);
	organizationFileView->setSelectionMode(QAbstractItemView::SingleSelection);
	organizationFileView->setWordWrap(Qt::ElideNone);
	organizationFileView->setColumnWidth(0, infoOrganization[1]->width() * 0.6);
	organizationFileView->setColumnWidth(1, infoOrganization[1]->width() * 0.2);
	organizationFileView->setColumnWidth(2, infoOrganization[1]->width() * 0.2);

	//Member
	infoOrganization[2] = new QWidget(organizationTab);
	infoOrganization[2]->resize(organizationTab->width(), organizationTab->height());

	QStringList memberHeader;
	memberHeader << QStringLiteral("成员名")
		<< QStringLiteral("权限")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	organizationMemberModel = new MyTableModel(infoOrganization[2]);
	organizationMemberModel->setHeader(memberHeader);

	organizationMemberView = new QTableView(infoOrganization[2]);
	organizationMemberView->setModel(organizationMemberModel);
	organizationMemberView->move(0, 0);
	organizationMemberView->resize(infoOrganization[2]->width(), infoOrganization[2]->height());
	organizationMemberView->setSortingEnabled(false);
	organizationMemberView->horizontalHeader()->setSectionsMovable(true);
	organizationMemberView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	organizationMemberView->horizontalHeader()->setSectionsClickable(true);
	organizationMemberView->horizontalHeader()->setStretchLastSection(true);
	organizationMemberView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	organizationMemberView->horizontalHeader()->setHighlightSections(true);
	organizationMemberView->horizontalHeader()->setVisible(true);
	organizationMemberView->verticalHeader()->setVisible(false);
	organizationMemberView->verticalHeader()->setDefaultSectionSize(15);
	organizationMemberView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	organizationMemberView->setSelectionBehavior(QAbstractItemView::SelectRows);
	organizationMemberView->setSelectionMode(QAbstractItemView::SingleSelection);
	organizationMemberView->setWordWrap(Qt::ElideNone);
	organizationMemberView->setColumnWidth(0, infoOrganization[2]->width() * 0.6);
	organizationMemberView->setColumnWidth(1, infoOrganization[2]->width() * 0.1);
	organizationMemberView->setColumnWidth(2, infoOrganization[2]->width() * 0.1);
	organizationMemberView->setColumnWidth(3, infoOrganization[2]->width() * 0.2);

	//Appeal
	infoOrganization[3] = new QWidget(organizationTab);
	infoOrganization[3]->resize(organizationTab->width(), organizationTab->height());

	QStringList appealHeader;
	memberHeader << QStringLiteral("成员名")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	organizationAppealModel = new MyTableModel(infoOrganization[3]);
	organizationAppealModel->setHeader(memberHeader);

	organizationAppealView = new QTableView(infoOrganization[3]);
	organizationAppealView->setModel(organizationAppealModel);
	organizationAppealView->move(0, 0);
	organizationAppealView->resize(infoOrganization[3]->width(), infoOrganization[3]->height());
	organizationAppealView->setSortingEnabled(false);
	organizationAppealView->horizontalHeader()->setSectionsMovable(true);
	organizationAppealView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	organizationAppealView->horizontalHeader()->setSectionsClickable(true);
	organizationAppealView->horizontalHeader()->setStretchLastSection(true);
	organizationAppealView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	organizationAppealView->horizontalHeader()->setHighlightSections(true);
	organizationAppealView->horizontalHeader()->setVisible(true);
	organizationAppealView->verticalHeader()->setVisible(false);
	organizationAppealView->verticalHeader()->setDefaultSectionSize(15);
	organizationAppealView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	organizationAppealView->setSelectionBehavior(QAbstractItemView::SelectRows);
	organizationAppealView->setSelectionMode(QAbstractItemView::SingleSelection);
	organizationAppealView->setWordWrap(Qt::ElideNone);
	organizationAppealView->setColumnWidth(0, infoOrganization[3]->width() * 0.6);
	organizationAppealView->setColumnWidth(1, infoOrganization[3]->width() * 0.2);
	organizationAppealView->setColumnWidth(3, infoOrganization[3]->width() * 0.2);

	//Setting
	infoOrganization[4] = new QWidget(organizationTab);
	infoOrganization[4]->resize(organizationTab->width(), organizationTab->height());

	organizationLine = new QLineEdit(infoOrganization[4]);
	organizationLine->move(infoOrganization[4]->width() * 0.2, infoOrganization[4]->height() * 0.1);
	organizationLine->resize(infoOrganization[4]->width() * 0.4, organizationLine->height());

	createOrgizationButton = new QPushButton(infoOrganization[4]);
	createOrgizationButton->setText(QStringLiteral("创建组织"));
	createOrgizationButton->move(infoOrganization[4]->width() * 0.7, infoOrganization[4]->height() * 0.1);
	createOrgizationButton->resize(infoOrganization[4]->width() * 0.15, createOrgizationButton->height());

	joinOrganizationLine = new QLineEdit(infoOrganization[4]);
	joinOrganizationLine->move(infoOrganization[4]->width() * 0.2, infoOrganization[4]->height() * 0.1 + 50);
	joinOrganizationLine->resize(infoOrganization[4]->width() * 0.4, organizationLine->height());
	QIntValidator* intVal = new QIntValidator();
	joinOrganizationLine->setValidator(intVal);

	joinOrganizationButton = new QPushButton(infoOrganization[4]);
	joinOrganizationButton->setText(QStringLiteral("加入组织"));
	joinOrganizationButton->move(infoOrganization[4]->width() * 0.7, infoOrganization[4]->height() * 0.1 + 50);
	joinOrganizationButton->resize(infoOrganization[4]->width() * 0.15, joinOrganizationButton->height());

	leaveOrganizationButton = new QPushButton(infoOrganization[4]);
	leaveOrganizationButton->setText(QStringLiteral("离开组织"));
	leaveOrganizationButton->move(infoOrganization[4]->width() * 0.2, infoOrganization[4]->height() * 0.1 + 150);
	leaveOrganizationButton->resize(infoOrganization[4]->width() * 0.15, leaveOrganizationButton->height());

	dissolveOrganizationButton = new QPushButton(infoOrganization[4]);
	dissolveOrganizationButton->setText(QStringLiteral("解散组织"));
	dissolveOrganizationButton->move(infoOrganization[4]->width() * 0.4, infoOrganization[4]->height() * 0.1 + 150);
	dissolveOrganizationButton->resize(infoOrganization[4]->width() * 0.15, dissolveOrganizationButton->height());

	organizationTab->addTab(infoOrganization[0], QStringLiteral("基本信息"));
	organizationTab->addTab(infoOrganization[1], QStringLiteral("云盘文件"));
	organizationTab->addTab(infoOrganization[2], QStringLiteral("成员管理"));
	organizationTab->addTab(infoOrganization[3], QStringLiteral("申请管理"));
	organizationTab->addTab(infoOrganization[4], QStringLiteral("组织管理"));
	organization->setVisible(false);
}

void MainWindow::InitAdmin()
{
	qDebug() << "Call MainThread InitAdmin";
	admin = new QWidget;
	admin->resize(QApplication::desktop()->width() * 0.5, QApplication::desktop()->height() * 0.7);
	admin->move(QApplication::desktop()->width() * 0.25, QApplication::desktop()->height() * 0.15);
	admin->setWindowTitle(QStringLiteral("超级管理员界面"));
	admin->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	admin->setFixedSize(admin->width(), admin->height());

	adminTab = new QTabWidget(admin);
	adminTab->resize(admin->width() * 0.9, admin->height() * 0.9);
	adminTab->move(admin->width() * 0.05, admin->y() * 0.05);

	//User
	infoAdmin[0] = new QWidget(adminTab);
	infoAdmin[0]->resize(adminTab->width(), adminTab->height());

	QStringList fileHeader;
	fileHeader << QStringLiteral("文件名")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	fileAdminModel = new MyTableModel(infoAdmin[0]);
	fileAdminModel->setHeader(fileHeader);

	fileAdminView = new QTableView(infoAdmin[0]);
	fileAdminView->setModel(fileAdminModel);
	fileAdminView->move(0, 0);
	fileAdminView->resize(infoAdmin[0]->width(), infoAdmin[0]->height());
	fileAdminView->setSortingEnabled(false);
	fileAdminView->horizontalHeader()->setSectionsMovable(true);
	fileAdminView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	fileAdminView->horizontalHeader()->setSectionsClickable(true);
	fileAdminView->horizontalHeader()->setStretchLastSection(true);
	fileAdminView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	fileAdminView->horizontalHeader()->setHighlightSections(true);
	fileAdminView->horizontalHeader()->setVisible(true);
	fileAdminView->verticalHeader()->setVisible(false);
	fileAdminView->verticalHeader()->setDefaultSectionSize(15);
	fileAdminView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	fileAdminView->setSelectionBehavior(QAbstractItemView::SelectRows);
	fileAdminView->setSelectionMode(QAbstractItemView::SingleSelection);
	fileAdminView->setWordWrap(Qt::ElideNone);
	fileAdminView->setColumnWidth(0, infoAdmin[0]->width() * 0.6);
	fileAdminView->setColumnWidth(1, infoAdmin[0]->width() * 0.2);
	fileAdminView->setColumnWidth(2, infoAdmin[0]->width() * 0.2);

	//File
	infoAdmin[1] = new QWidget(adminTab);
	infoAdmin[1]->resize(adminTab->width(), adminTab->height());

	QStringList userHeader;
	userHeader << QStringLiteral("用户名")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	userAdminModel = new MyTableModel(infoAdmin[1]);
	userAdminModel->setHeader(userHeader);

	userAdminView = new QTableView(infoAdmin[1]);
	userAdminView->setModel(userAdminModel);
	userAdminView->move(0, 0);
	userAdminView->resize(infoAdmin[1]->width(), infoAdmin[1]->height());
	userAdminView->setSortingEnabled(false);
	userAdminView->horizontalHeader()->setSectionsMovable(true);
	userAdminView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	userAdminView->horizontalHeader()->setSectionsClickable(true);
	userAdminView->horizontalHeader()->setStretchLastSection(true);
	userAdminView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	userAdminView->horizontalHeader()->setHighlightSections(true);
	userAdminView->horizontalHeader()->setVisible(true);
	userAdminView->verticalHeader()->setVisible(false);
	userAdminView->verticalHeader()->setDefaultSectionSize(15);
	userAdminView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	userAdminView->setSelectionBehavior(QAbstractItemView::SelectRows);
	userAdminView->setSelectionMode(QAbstractItemView::SingleSelection);
	userAdminView->setWordWrap(Qt::ElideNone);
	userAdminView->setColumnWidth(0, infoAdmin[1]->width() * 0.6);
	userAdminView->setColumnWidth(1, infoAdmin[1]->width() * 0.2);
	userAdminView->setColumnWidth(2, infoAdmin[1]->width() * 0.2);

	//Organization
	infoAdmin[2] = new QWidget(adminTab);
	infoAdmin[2]->resize(adminTab->width(), adminTab->height());

	QStringList orgizationHeader;
	orgizationHeader << QStringLiteral("组织名")
		<< QStringLiteral("状态")
		<< QStringLiteral("操作");

	organizationAdminModel = new MyTableModel(infoAdmin[2]);
	organizationAdminModel->setHeader(orgizationHeader);

	organizationAdminView = new QTableView(infoAdmin[2]);
	organizationAdminView->setModel(organizationAdminModel);
	organizationAdminView->move(0, 0);
	organizationAdminView->resize(infoAdmin[2]->width(), infoAdmin[2]->height());
	organizationAdminView->setSortingEnabled(false);
	organizationAdminView->horizontalHeader()->setSectionsMovable(true);
	organizationAdminView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	organizationAdminView->horizontalHeader()->setSectionsClickable(true);
	organizationAdminView->horizontalHeader()->setStretchLastSection(true);
	organizationAdminView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	organizationAdminView->horizontalHeader()->setHighlightSections(true);
	organizationAdminView->horizontalHeader()->setVisible(true);
	organizationAdminView->verticalHeader()->setVisible(false);
	organizationAdminView->verticalHeader()->setDefaultSectionSize(15);
	organizationAdminView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	organizationAdminView->setSelectionBehavior(QAbstractItemView::SelectRows);
	organizationAdminView->setSelectionMode(QAbstractItemView::SingleSelection);
	organizationAdminView->setWordWrap(Qt::ElideNone);
	organizationAdminView->setColumnWidth(0, infoAdmin[2]->width() * 0.6);
	organizationAdminView->setColumnWidth(1, infoAdmin[2]->width() * 0.2);
	organizationAdminView->setColumnWidth(2, infoAdmin[2]->width() * 0.2);

	adminTab->addTab(infoAdmin[0], QStringLiteral("文件管理"));
	adminTab->addTab(infoAdmin[1], QStringLiteral("用户管理"));
	adminTab->addTab(infoAdmin[2], QStringLiteral("组织管理"));
	admin->setVisible(false);
}

void MainWindow::InitUpLoad()
{
	qDebug() << "Call MainThread InitUpLoad";
	upLoad = new QWidget;
	upLoad->resize(this->width() * 0.3, this->height() * 0.3);
	upLoad->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	upLoad->setFixedSize(upLoad->width(), upLoad->height());
	upLoad->setProperty("doing", false);
	upLoad->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	upLoad->setProperty("doing", false);

	upLoadUserButton = new QPushButton(upLoad);
	upLoadUserButton->setText(QStringLiteral("上传到个人云盘"));
	upLoadUserButton->move(upLoad->width() * 0.05, upLoad->height() * 0.2);
	upLoadUserButton->resize(upLoad->width() * 0.4, upLoadUserButton->height());

	upLoadOrganizationButton = new QPushButton(upLoad);
	upLoadOrganizationButton->setText(QStringLiteral("上传到组织云盘"));
	upLoadOrganizationButton->move(upLoad->width() * 0.55, upLoad->height() * 0.2);
	upLoadOrganizationButton->resize(upLoad->width() * 0.4, upLoadOrganizationButton->height());

	QLabel* upLoadUserLab = new QLabel(upLoad);
	upLoadUserLab->move(upLoad->width() * 0.1, upLoad->height() * 0.5);
	upLoadUserLab->resize(upLoad->width() * 0.2, upLoadUserLab->height());
	upLoadUserLab->setText(QStringLiteral("进度:"));

	upLoadFileBar = new QProgressBar(upLoad);
	upLoadFileBar->move(upLoad->width() * 0.35, upLoad->height() * 0.5);
	upLoadFileBar->resize(upLoad->width() * 0.55, upLoadFileBar->height());

	closeUpLoadButton = new QPushButton(upLoad);
	closeUpLoadButton->move(upLoad->width() * 0.3, upLoad->height() * 0.8);
	closeUpLoadButton->resize(upLoad->width() * 0.3, closeUpLoadButton->height());
	closeUpLoadButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitOperatorFile()
{
	operatorFile = new QWidget;
	operatorFile->resize(personal->width() * 0.3, personal->height() * 0.3);
	operatorFile->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	operatorFile->setFixedSize(operatorFile->width(), operatorFile->height());
	operatorFile->setProperty("doing", false);
	operatorFile->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	downLoadFileButton = new QPushButton(operatorFile);
	downLoadFileButton->move(operatorFile->width() * 0.1, operatorFile->height() * 0.2);
	downLoadFileButton->resize(operatorFile->width() * 0.15, downLoadFileButton->height());
	downLoadFileButton->setText(QStringLiteral("下载"));
	downLoadFileButton->show();

	QLabel* downLoadLab = new QLabel(operatorFile);
	downLoadLab->move(operatorFile->width() * 0.3, operatorFile->height() * 0.2);
	downLoadLab->resize(operatorFile->width() * 0.2, downLoadLab->height());
	downLoadLab->setText(QStringLiteral("进度:"));

	downLoadFileBar = new QProgressBar(operatorFile);
	downLoadFileBar->move(operatorFile->width() * 0.5, operatorFile->height() * 0.2);
	downLoadFileBar->resize(operatorFile->width() * 0.5, downLoadFileBar->height());

	appealFileLab = new QLabel(operatorFile);
	appealFileLab->move(operatorFile->width() * 0.1, operatorFile->height() * 0.5);
	appealFileLab->resize(operatorFile->width() * 0.4, appealFileLab->height());

	appealFileButton = new QPushButton(operatorFile);
	appealFileButton->move(operatorFile->width() * 0.5, operatorFile->height() * 0.5);
	appealFileButton->resize(operatorFile->width() * 0.15, appealFileButton->height());
	appealFileButton->setText(QStringLiteral("申诉"));

	deleteFileButton = new QPushButton(operatorFile);
	deleteFileButton->move(operatorFile->width() * 0.7, operatorFile->height() * 0.5);
	deleteFileButton->resize(operatorFile->width() * 0.15, deleteFileButton->height());
	deleteFileButton->setText(QStringLiteral("删除"));

	closeFileButton = new QPushButton(operatorFile);
	closeFileButton->move(operatorFile->width() * 0.3, operatorFile->height() * 0.8);
	closeFileButton->resize(operatorFile->width() * 0.3, closeFileButton->height());
	closeFileButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitOperatorMember()
{
	qDebug() << "Call MainThread InitOperatorMember";
	operatorMember = new QWidget;
	operatorMember->resize(organization->width() * 0.3, organization->height() * 0.3);
	operatorMember->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	operatorMember->setFixedSize(operatorMember->width(), operatorMember->height());
	operatorMember->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	QLabel* powerLab = new QLabel(operatorMember);
	powerLab->move(operatorMember->width() * 0.1, operatorMember->height() * 0.2);
	powerLab->resize(operatorMember->width() * 0.4, powerLab->height());
	powerLab->setText(QStringLiteral("当前权限:"));

	nowPoweLab = new QLabel(operatorMember);
	nowPoweLab->move(operatorMember->width() * 0.5, operatorMember->height() * 0.2);
	nowPoweLab->resize(operatorMember->width() * 0.4, nowPoweLab->height());

	kickOutButton = new QPushButton(operatorMember);
	kickOutButton->move(operatorMember->width() * 0.1, operatorMember->height() * 0.5);
	kickOutButton->resize(operatorMember->width() * 0.2, kickOutButton->height());
	kickOutButton->setText(QStringLiteral("踢出"));
	kickOutButton->show();

	upPowerButton = new QPushButton(operatorMember);
	upPowerButton->move(operatorMember->width() * 0.4, operatorMember->height() * 0.5);
	upPowerButton->resize(operatorMember->width() * 0.2, upPowerButton->height());
	upPowerButton->setText(QStringLiteral("升职"));

	lowPowerButton = new QPushButton(operatorMember);
	lowPowerButton->move(operatorMember->width() * 0.7, operatorMember->height() * 0.5);
	lowPowerButton->resize(operatorMember->width() * 0.2, lowPowerButton->height());
	lowPowerButton->setText(QStringLiteral("降职"));

	closeMemberButton = new QPushButton(operatorMember);
	closeMemberButton->move(operatorFile->width() * 0.3, operatorFile->height() * 0.8);
	closeMemberButton->resize(operatorFile->width() * 0.3, closeMemberButton->height());
	closeMemberButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitOperatorAppealMember()
{
	qDebug() << "Call MainThread InitOperatorAppealMember";
	operatorAppealMember = new QWidget;
	operatorAppealMember->resize(organization->width() * 0.3, organization->height() * 0.3);
	operatorAppealMember->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	operatorAppealMember->setFixedSize(operatorAppealMember->width(), operatorAppealMember->height());
	operatorAppealMember->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	appealJoinButton = new QPushButton(operatorAppealMember);
	appealJoinButton->move(operatorAppealMember->width() * 0.1, operatorAppealMember->height() * 0.5);
	appealJoinButton->resize(operatorAppealMember->width() * 0.3, appealJoinButton->height() * 2);
	appealJoinButton->setText(QStringLiteral("同意"));
	appealJoinButton->show();

	refuseJoinButton = new QPushButton(operatorAppealMember);
	refuseJoinButton->move(operatorAppealMember->width() * 0.6, operatorAppealMember->height() * 0.5);
	refuseJoinButton->resize(operatorAppealMember->width() * 0.3, refuseJoinButton->height() * 2);
	refuseJoinButton->setText(QStringLiteral("拒绝"));

	closeAppealButton = new QPushButton(operatorAppealMember);
	closeAppealButton->move(operatorFile->width() * 0.3, operatorFile->height() * 0.8);
	closeAppealButton->resize(operatorFile->width() * 0.3, closeAppealButton->height());
	closeAppealButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitOperatorAdminFile()
{
	qDebug() << "Call MainThread InitOperatorMember";
	operatorAdminFile = new QWidget;
	operatorAdminFile->resize(admin->width() * 0.2, admin->height() * 0.4);
	operatorAdminFile->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	operatorAdminFile->setFixedSize(operatorAdminFile->width(), operatorAdminFile->height());
	operatorAdminFile->setProperty("doing", false);
	operatorAdminFile->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	QLabel* belongLab = new QLabel(operatorAdminFile);
	belongLab->move(operatorAdminFile->width() * 0.1, operatorAdminFile->height() * 0.1);
	belongLab->resize(operatorAdminFile->width() * 0.4, belongLab->height());
	belongLab->setText(QStringLiteral("文件所属:"));

	belongToLab = new QLabel(operatorAdminFile);
	belongToLab->move(operatorAdminFile->width() * 0.5, operatorAdminFile->height() * 0.1);
	belongToLab->resize(operatorAdminFile->width() * 0.4, belongToLab->height());

	downLoadFileAdminButton = new QPushButton(operatorAdminFile);
	downLoadFileAdminButton->move(operatorAdminFile->width() * 0.1, operatorAdminFile->height() * 0.3);
	downLoadFileAdminButton->resize(operatorAdminFile->width() * 0.2, downLoadFileAdminButton->height());
	downLoadFileAdminButton->setText(QStringLiteral("下载"));
	downLoadFileAdminButton->show();

	QLabel* downLoadLab = new QLabel(operatorAdminFile);
	downLoadLab->move(operatorAdminFile->width() * 0.35, operatorAdminFile->height() * 0.3);
	downLoadLab->resize(operatorAdminFile->width() * 0.2, downLoadLab->height());
	downLoadLab->setText(QStringLiteral("进度:"));

	downLoadFileAdminBar = new QProgressBar(operatorAdminFile);
	downLoadFileAdminBar->move(operatorAdminFile->width() * 0.6, operatorAdminFile->height() * 0.3);
	downLoadFileAdminBar->resize(operatorAdminFile->width() * 0.4, downLoadFileAdminBar->height());

	banFileAdminButton = new QPushButton(operatorAdminFile);
	banFileAdminButton->move(operatorAdminFile->width() * 0.1, operatorAdminFile->height() * 0.5);
	banFileAdminButton->resize(operatorAdminFile->width() * 0.3, banFileAdminButton->height());
	banFileAdminButton->setText(QStringLiteral("封禁"));

	resetFileAdminButton = new QPushButton(operatorAdminFile);
	resetFileAdminButton->move(operatorAdminFile->width() * 0.6, operatorAdminFile->height() * 0.5);
	resetFileAdminButton->resize(operatorAdminFile->width() * 0.3, resetFileAdminButton->height());
	resetFileAdminButton->setText(QStringLiteral("解封"));

	closeFileAdminButton = new QPushButton(operatorAdminFile);
	closeFileAdminButton->move(operatorAdminFile->width() * 0.3, operatorAdminFile->height() * 0.7);
	closeFileAdminButton->resize(operatorAdminFile->width() * 0.3, closeFileAdminButton->height());
	closeFileAdminButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitOperatorAdminUser()
{
	qDebug() << "Call MainThread InitOperatorAdminUser";
	operatorAdminUser = new QWidget;
	operatorAdminUser->resize(admin->width() * 0.2, admin->height() * 0.2);
	operatorAdminUser->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	operatorAdminUser->setFixedSize(operatorAdminUser->width(), operatorAdminUser->height());
	operatorAdminUser->setProperty("doing", false);
	operatorAdminUser->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	banUserAdminButton = new QPushButton(operatorAdminUser);
	banUserAdminButton->move(operatorAdminUser->width() * 0.1, operatorAdminUser->height() * 0.2);
	banUserAdminButton->resize(operatorAdminUser->width() * 0.3, banUserAdminButton->height());
	banUserAdminButton->setText(QStringLiteral("封禁"));

	resetUserAdminButton = new QPushButton(operatorAdminUser);
	resetUserAdminButton->move(operatorAdminUser->width() * 0.6, operatorAdminUser->height() * 0.2);
	resetUserAdminButton->resize(operatorAdminUser->width() * 0.3, resetUserAdminButton->height());
	resetUserAdminButton->setText(QStringLiteral("解封"));

	closeUserAdminButton = new QPushButton(operatorAdminUser);
	closeUserAdminButton->move(operatorAdminUser->width() * 0.3, operatorAdminUser->height() * 0.6);
	closeUserAdminButton->resize(operatorAdminUser->width() * 0.3, closeUserAdminButton->height());
	closeUserAdminButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitOperatorAdminOrganization()
{
	qDebug() << "Call MainThread InitOperatorAdminUser";
	operatorAdminOrganization = new QWidget;
	operatorAdminOrganization->resize(admin->width() * 0.2, admin->height() * 0.2);
	operatorAdminOrganization->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));
	operatorAdminOrganization->setFixedSize(operatorAdminOrganization->width(), operatorAdminOrganization->height());
	operatorAdminOrganization->setProperty("doing", false);
	operatorAdminOrganization->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	banOrganizationAdminButton = new QPushButton(operatorAdminOrganization);
	banOrganizationAdminButton->move(operatorAdminOrganization->width() * 0.1, operatorAdminOrganization->height() * 0.2);
	banOrganizationAdminButton->resize(operatorAdminOrganization->width() * 0.3, banOrganizationAdminButton->height());
	banOrganizationAdminButton->setText(QStringLiteral("封禁"));

	resetOrganizationAdminButton = new QPushButton(operatorAdminOrganization);
	resetOrganizationAdminButton->move(operatorAdminOrganization->width() * 0.6, operatorAdminOrganization->height() * 0.2);
	resetOrganizationAdminButton->resize(operatorAdminOrganization->width() * 0.3, resetOrganizationAdminButton->height());
	resetOrganizationAdminButton->setText(QStringLiteral("解封"));

	closeOrganizationAdminButton = new QPushButton(operatorAdminOrganization);
	closeOrganizationAdminButton->move(operatorAdminOrganization->width() * 0.3, operatorAdminOrganization->height() * 0.6);
	closeOrganizationAdminButton->resize(operatorAdminOrganization->width() * 0.3, closeOrganizationAdminButton->height());
	closeOrganizationAdminButton->setText(QStringLiteral("关闭"));
}

void MainWindow::InitCommunicate()
{
	com = new Communicate;
	comThread = new QThread;
	com->moveToThread(comThread);
	comThread->start();
}

void MainWindow::InitChat()
{
	chatWidget = new QWidget;
	chatWidget->resize(this->width() * 0.2, this->height() * 0.2);
	chatWidget->setWindowTitle(QStringLiteral("通信设置"));
	chatWidget->setWindowIcon(QIcon(QApplication::applicationDirPath() % "/source/icon.png"));

	openServerButton = new QPushButton(chatWidget);
	openServerButton->setText(QStringLiteral("服务端设置"));
	openServerButton->move(chatWidget->width() * 0.2, chatWidget->height() * 0.2);
	openServerButton->resize(chatWidget->width() * 0.6, chatWidget->height() * 0.2);

	openClientButton = new QPushButton(chatWidget);
	openClientButton->setText(QStringLiteral("客户端设置"));
	openClientButton->move(chatWidget->width() * 0.2, chatWidget->height() * 0.5);
	openClientButton->resize(chatWidget->width() * 0.6, chatWidget->height() * 0.2);

	chatWidget->setVisible(false);
}

void MainWindow::InitServer()
{
	serverWidget = new QWidget;
	serverWidget->resize(600, 400);
	serverWidget->setWindowTitle(QStringLiteral("服务端设置"));

	QLabel* portLab = new QLabel(serverWidget);
	portLab->setText(QStringLiteral("监听端口"));
	portLab->setFont(QFont("Microsoft YaHei", 10, 50));
	portLab->move(30, 30);

	serverPortEdit = new QLineEdit(serverWidget);
	serverPortEdit->setText("929");
	serverPortEdit->resize(80, 30);
	serverPortEdit->move(120, 30);

	serverPortButton = new QPushButton(serverWidget);
	serverPortButton->setText(QStringLiteral("监听"));
	serverPortButton->resize(120, 30);
	serverPortButton->move(220, 30);

	QLabel* numLab = new QLabel(serverWidget);
	portLab->setText(QStringLiteral("当前连接用户"));
	portLab->setFont(QFont("Microsoft YaHei", 10, 50));
	portLab->move(360, 30);

	connectCountLab = new QLabel(serverWidget);
	connectCountLab->setText("0");
	connectCountLab->setFont(QFont("Microsoft YaHei", 10, 75));
	connectCountLab->setPalette(QPalette(QPalette::WindowText, Qt::red));
	connectCountLab->resize(80, 30);
	connectCountLab->move(500, 30);

	serverModel = new QStringListModel;
	serverView = new QListView(serverWidget);
	serverView->resize(540, 300);
	serverView->move(30, 80);
	serverView->setModel(serverModel);
	serverView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	server = new MyServer;
	serverThread = new QThread;
	server->moveToThread(serverThread);
	serverThread->start();

	serverWidget->setVisible(false);
}

void MainWindow::InitClient()
{
	clientWidget = new QWidget;
	clientWidget->resize(600, 400);
	clientWidget->setWindowTitle(QStringLiteral("客户端设置"));

	QLabel* hostLab = new QLabel(clientWidget);
	hostLab->setText(QStringLiteral("地址"));
	hostLab->setFont(QFont("Microsoft YaHei", 10, 50));
	hostLab->move(30, 30);

	clientAddressEdit = new QLineEdit(clientWidget);
	clientAddressEdit->setText("127.0.0.1");
	clientAddressEdit->resize(150, 30);
	clientAddressEdit->move(80, 30);
	QRegExp rx("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
	QRegExpValidator* ip = new QRegExpValidator(rx, clientWidget);
	clientAddressEdit->setValidator(ip);

	QLabel* portLab = new QLabel(clientWidget);
	portLab->setText(QStringLiteral("端口"));
	portLab->setFont(QFont("Microsoft YaHei", 10, 50));
	portLab->move(240, 30);

	clientPortEdit = new QLineEdit(clientWidget);
	clientPortEdit->setText("929");
	clientPortEdit->resize(80, 30);
	clientPortEdit->move(300, 30);

	clientButton = new QPushButton(clientWidget);
	clientButton->setText(QStringLiteral("连接"));
	clientButton->move(400, 30);

	clientModel = new QStringListModel;
	clientView = new QListView(clientWidget);
	clientView->resize(540, 200);
	clientView->move(30, 80);
	clientView->setModel(clientModel);
	clientView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	clientInputEdit = new QTextEdit(clientWidget);
	clientInputEdit->resize(440, 80);
	clientInputEdit->move(30, 300);

	sendMessageButton = new QPushButton(clientWidget);
	sendMessageButton->setText(QStringLiteral("发送"));
	sendMessageButton->resize(80, 80);
	sendMessageButton->move(490, 300);
	sendMessageButton->setEnabled(false);

	client = new MyClient;
	clientThread = new QThread;
	client->moveToThread(clientThread);
	clientThread->start();

	clientWidget->setVisible(false);
}

void MainWindow::InitConnect()
{
	qDebug() << "Call MainThread InitConnect";
	// SystemTray
	connect(actiont_1, SIGNAL(triggered()), this, SLOT(OptionTriggered()));
	connect(actiont_2, SIGNAL(triggered()), this, SLOT(HelpTriggered()));
	connect(actiont_3, SIGNAL(triggered()), this, SLOT(AboutTriggered()));
	connect(actiont_4, SIGNAL(triggered()), this, SLOT(QuitEvent()));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(TrayEvent(QSystemTrayIcon::ActivationReason)));

	//MenuBar
	connect(action1_1, SIGNAL(triggered()), this, SLOT(OptionTriggered()));
	connect(action1_2, SIGNAL(triggered()), this, SLOT(hide()));
	connect(action1_3, SIGNAL(triggered()), this, SLOT(QuitEvent()));
	connect(action2_1, SIGNAL(triggered()), this, SLOT(FilterTriggered()));
	connect(action2_2, SIGNAL(triggered()), this, SLOT(InfoTriggered()));
	connect(action3_1, SIGNAL(triggered()), this, SLOT(SearchCaseSensitiveTriggered()));
	connect(action3_2, SIGNAL(triggered()), this, SLOT(SearchMatchPathTriggered()));
	connect(action3_3, SIGNAL(triggered()), this, SLOT(SearchMatchFileTriggered()));
	connect(action3_4, SIGNAL(triggered()), this, SLOT(SearcRegExTriggered()));
	connect(action4_1, SIGNAL(triggered()), this, SLOT(SignWidgetTriggered()));
	connect(action4_2, SIGNAL(triggered()), this, SLOT(PersonalTriggered()));
	connect(action4_3, SIGNAL(triggered()), this, SLOT(OrganizationTriggered()));
	connect(action4_4, SIGNAL(triggered()), this, SLOT(ChatTriggered()));
	connect(action4_5, SIGNAL(triggered()), this, SLOT(AdminTriggered()));
	connect(action4_6, SIGNAL(triggered()), this, SLOT(SignOut()));

	connect(action5_1, SIGNAL(triggered()), this, SLOT(HelpTriggered()));
	connect(action5_2, SIGNAL(triggered()), this, SLOT(AboutTriggered()));

	//Button
	connect(actionb_1, SIGNAL(triggered()), button_f, SLOT(click()));
	connect(actionb_2, SIGNAL(triggered()), button_f, SLOT(click()));
	connect(button_f, SIGNAL(clicked()), this, SLOT(FindTriggered()));

	//Filter
	connect(filter, SIGNAL(currentIndexChanged(int)), this, SLOT(FilterEvent(int)));

	//ButtonInfo
	connect(fileSystem, SIGNAL(EmitInfo(QString)), infoLeft, SLOT(ShowInfo(QString)));
	connect(this, SIGNAL(EmitInfo(QString)), infoLeft, SLOT(ShowInfo(QString)));

	//FileSystem
	connect(this, SIGNAL(Begin()), fileSystem, SLOT(Init()));
	connect(fileSystem, SIGNAL(InitRes(bool)), this, SLOT(InitVolume()));

	//RightMenu
	connect(actionv_1, SIGNAL(triggered()), this, SLOT(CopyFullPath()));
	connect(actionv_2, SIGNAL(triggered()), this, SLOT(CopyPath()));
	connect(tableView, SIGNAL(doubleClicked(const QModelIndex&)), viewModel, SLOT(rowDoubleClicked(const QModelIndex&)));
	connect(tableView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(RightClicked(const QPoint&)));
	connect(actionr_1, SIGNAL(triggered()), this, SLOT(OpenFile()));
	connect(actionr_2, SIGNAL(triggered()), this, SLOT(OpenPath()));
	connect(actionr_3, SIGNAL(triggered()), this, SLOT(CopyFullPath()));
	connect(actionr_4, SIGNAL(triggered()), this, SLOT(CopyPath()));
	connect(actionr_5, SIGNAL(triggered()), this, SLOT(Delete()));
	connect(actionr_6, SIGNAL(triggered()), this, SLOT(Attribute()));
	connect(actionr_7, SIGNAL(triggered()), this, SLOT(UpLoadFile()));

	//About
	connect(actiona_1, SIGNAL(triggered()), this, SLOT(AboutTriggered()));

	//Option
	connect(buttonv_n_1, SIGNAL(clicked()), this, SLOT(VolumeNtfsStateChange()));
	connect(buttonv_o_1, SIGNAL(clicked()), this, SLOT(VolumeOtherStateChange()));
	connect(buttoni_1, SIGNAL(clicked()), this, SLOT(IgnorePathAdd()));
	connect(buttoni_2, SIGNAL(clicked()), this, SLOT(IgnorePathRemove()));
	connect(buttonm_1, SIGNAL(clicked()), this, SLOT(MonitorPathAdd()));
	connect(buttonm_2, SIGNAL(clicked()), this, SLOT(MonitorPathRemove()));
	connect(boxi_2, SIGNAL(stateChanged(int)), this, SLOT(OneClickShowTriggered()));
	connect(boxs_5, SIGNAL(stateChanged(int)), this, SLOT(AutoUpdateTriggered()));
	connect(optionButtonYes, SIGNAL(clicked()), this, SLOT(OptionToSubmit()));
	connect(optionButtonNo, SIGNAL(clicked()), this, SLOT(OptionCancel()));

	//Sign
	connect(button_s, SIGNAL(clicked()), this, SLOT(SignTriggered()));
	connect(button_r, SIGNAL(clicked()), this, SLOT(RegisterTriggered()));
	connect(button_skip, SIGNAL(clicked()), this, SLOT(SkipTriggered()));
	if (Configuration::OnlineEnable())
		connect(this, SIGNAL(Begin()), com, SLOT(AbleToOnline()));
	connect(this, SIGNAL(RetryToOnline()), com, SLOT(AbleToOnline()));
	connect(com, SIGNAL(Online(bool)), this, SLOT(OnlineEvent(bool)));
	connect(this, SIGNAL(Sign()), com, SLOT(Sign()));
	connect(com, SIGNAL(SignRes(bool)), this, SLOT(SignEvent(bool)));
	connect(this, SIGNAL(Register()), com, SLOT(Register()));
	connect(com, SIGNAL(RegisterRes(bool)), this, SLOT(RegisterEvent(bool)));
	connect(this, SIGNAL(GetUserInfo()), com, SLOT(GetUserInfo()));
	connect(com, SIGNAL(GetUserInfoRes(bool)), this, SLOT(GetUserInfoEvent(bool)));

	//Personal
	connect(this, SIGNAL(ShowUserFile()), com, SLOT(ShowUserFile()));
	connect(com, SIGNAL(ShowUserFileRes(QJsonArray)), this, SLOT(ShowUserFileEvent(QJsonArray)));
	connect(getConfButton, SIGNAL(clicked()), this, SLOT(GetConfClicked()));
	connect(this, SIGNAL(GetConf()), com, SLOT(GetConf()));
	connect(com, SIGNAL(GetConfRes(bool)), this, SLOT(GetConfEvent(bool)));
	connect(writeConfButton, SIGNAL(clicked()), this, SLOT(WriteConfClicked()));
	connect(this, SIGNAL(WriteConf()), com, SLOT(WriteConf()));
	connect(com, SIGNAL(WriteConfRes(bool)), this, SLOT(WriteConfEvent(bool)));
	connect(appealUserButton, SIGNAL(clicked()), this, SLOT(AppealUserClicked()));
	connect(this, SIGNAL(AppealUser()), com, SLOT(AppealUser()));
	connect(com, SIGNAL(AppealUserRes(bool)), this, SLOT(AppealUserEvent(bool)));
	connect(personalTab, &QTabWidget::currentChanged, this, [this](int index)->void
		{
			if (index == 1)
			{
				emit ShowUserFile();
				ClearModelExcept(1);
			}
			else
				ClearModelExcept();
		});

	//Organization
	connect(this, SIGNAL(ShowOrganizationFile()), com, SLOT(ShowOrganizationFile()));
	connect(com, SIGNAL(ShowOrganizationFileRes(QJsonArray)), this, SLOT(ShowOrganizationFileEvent(QJsonArray)));
	connect(this, SIGNAL(GetOrganizationMembers()), com, SLOT(GetOrganizationMembers()));
	connect(com, SIGNAL(GetOrganizationMembersRes(QJsonArray)), this, SLOT(GetOrganizationMembersEvent(QJsonArray)));
	connect(this, SIGNAL(ShowAppealOrganization()), com, SLOT(ShowAppealOrganization()));
	connect(com, SIGNAL(ShowAppealOrganizationRes(QJsonArray)), this, SLOT(ShowAppealOrganizationEvent(QJsonArray)));
	connect(createOrgizationButton, SIGNAL(clicked()), this, SLOT(CreateOrganization()));
	connect(this, SIGNAL(CreateOrganization(QString)), com, SLOT(CreateOrganization(QString)));
	connect(com, SIGNAL(CreateOrganizationRes(bool)), this, SLOT(CreateOrgizationEvent(bool)));
	connect(joinOrganizationButton, SIGNAL(clicked()), this, SLOT(ApplyJoinOrganization()));
	connect(this, SIGNAL(ApplyJoinOrganization(int)), com, SLOT(ApplyJoinOrganization(int)));
	connect(com, SIGNAL(ApplyJoinOrganizationRes(bool)), this, SLOT(ApplyJoinOrganizationEvent(bool)));
	connect(leaveOrganizationButton, SIGNAL(clicked()), this, SLOT(LeaveOrganization()));
	connect(this, SIGNAL(LeaveOrganization(int)), com, SLOT(LeaveOrganization(int)));
	connect(com, SIGNAL(LeaveOrganizationRes(bool)), this, SLOT(LeaveOrganizationEvent(bool)));
	connect(dissolveOrganizationButton, SIGNAL(clicked()), this, SLOT(DissolveOrganization()));
	connect(this, SIGNAL(DissolveOrganization(int)), com, SLOT(DissolveOrganization(int)));
	connect(com, SIGNAL(DissolveOrganizationRes(bool)), this, SLOT(DissolveOrganizationEvnet(bool)));
	connect(organizationTab, &QTabWidget::currentChanged, this, [this](int index)->void
		{
			switch (index)
			{
			case 1:
				ClearModelExcept(2, 1);
				emit ShowOrganizationFile();
				break;
			case 2:
				ClearModelExcept(2, 2);
				emit GetOrganizationMembers();
				break;
			case 3:
				ClearModelExcept(2, 3);
				emit ShowAppealOrganization();
				break;
			default:
				ClearModelExcept();
				break;
			}
		});

	//OperatorMember
	connect(this, SIGNAL(UpOrganizationMemberPower(int)), com, SLOT(UpOrganizationMemberPower(int)));
	connect(com, SIGNAL(UpOrganizationMemberPowerRes(bool)), this, SLOT(UpOrganizationMemberPowerEvent(bool)));
	connect(this, SIGNAL(LowOrganizationMemberPower(int)), com, SLOT(LowOrganizationMemberPower(int)));
	connect(com, SIGNAL(LowOrganizationMemberPowerRes(bool)), this, SLOT(LowOrganizationMemberPowerEvent(bool)));
	connect(closeMemberButton, SIGNAL(clicked()), this, SLOT(CloseMemberOperatorEvent()));

	//OperatorAppeal
	connect(this, SIGNAL(JoinOrganization(int)), com, SLOT(JoinOrganization(int)));
	connect(com, SIGNAL(JoinOrganizationRes(bool)), this, SLOT(JoinOrganizationEvent(bool)));
	connect(this, SIGNAL(RefuseOrganization(int)), com, SLOT(RefuseOrganization(int)));
	connect(com, SIGNAL(RefuseOrganizationRes(bool)), this, SLOT(RefuseOrganizationEvent(bool)));
	connect(closeAppealButton, SIGNAL(clicked()), this, SLOT(CloseAppealMemberOperatorEvent()));

	//OperatorFile
	connect(upLoadUserButton, SIGNAL(clicked()), this, SLOT(UpLoadUserFile()));
	connect(this, SIGNAL(UpLoadUserFile(QString)), com, SLOT(UpLoadUserFile(QString)));
	connect(com, SIGNAL(UpLoadUserFileRes(bool)), this, SLOT(UpLoadUserFileEvent(bool)));
	connect(upLoadOrganizationButton, SIGNAL(clicked()), this, SLOT(UpLoadOrganizationFile()));
	connect(this, SIGNAL(UpLoadOrganizationFile(QString)), com, SLOT(UpLoadOrganizationFile(QString)));
	connect(com, SIGNAL(UpLoadOrganizationFileRes(bool)), this, SLOT(UpLoadOrganizationFileEvent(bool)));
	connect(closeUpLoadButton, SIGNAL(clicked()), this, SLOT(CloseUpLoadEvent()));
	connect(this, SIGNAL(DownLoadFile(int)), com, SLOT(DownLoadFile(int)));
	connect(com, SIGNAL(DownLoadFileRes(bool)), this, SLOT(DownLoadFileEvent(bool)));
	connect(this, SIGNAL(AppealFile(int)), com, SLOT(AppealFile(int)));
	connect(com, SIGNAL(AppealFileRes(bool)), this, SLOT(AppealFileEvent(bool)));
	connect(this, SIGNAL(DeleteUserFile(int)), com, SLOT(DeleteUserFile(int)));
	connect(com, SIGNAL(DeleteUserFileRes(bool)), this, SLOT(DeleteUserFileEvent(bool)));
	connect(closeFileButton, SIGNAL(clicked()), this, SLOT(CloseFileOperatorEvent()));

	//Admin
	connect(this, SIGNAL(ShowFile()), com, SLOT(ShowFile()));
	connect(com, SIGNAL(ShowFileRes(QJsonObject)), this, SLOT(ShowFileEvent(QJsonObject)));
	connect(this, SIGNAL(ShowUser()), com, SLOT(ShowUser()));
	connect(com, SIGNAL(ShowUserRes(QJsonArray)), this, SLOT(ShowUserEvent(QJsonArray)));
	connect(this, SIGNAL(ShowOrganization()), com, SLOT(ShowOrganization()));
	connect(com, SIGNAL(ShowOrganizationRes(QJsonArray)), this, SLOT(ShowOrganizationEvent(QJsonArray)));
	connect(adminTab, &QTabWidget::currentChanged, this, [this](int index)->void
		{
			switch (index)
			{
			case 0:
				ClearModelExcept(3, 1);
				emit ShowFile();
				break;
			case 1:
				ClearModelExcept(3, 2);
				emit ShowUser();
				break;
			case 2:
				ClearModelExcept(3, 3);
				emit ShowOrganization();
				break;
			default:
				ClearModelExcept();
				break;
			}
		});

	//AdminOperatorFile
	connect(this, SIGNAL(BanFile(int)), com, SLOT(BanFile(int)));
	connect(com, SIGNAL(BanFileRes(bool)), this, SLOT(BanFileEvent(bool)));
	connect(this, SIGNAL(ResetFile(int)), com, SLOT(ResetFile(int)));
	connect(com, SIGNAL(ResetFileRes(bool)), this, SLOT(ResetFileEvent(bool)));
	connect(closeFileAdminButton, SIGNAL(clicked()), this, SLOT(CloseFileOperatorAdminEvent()));

	//AdminOperatorUser
	connect(this, SIGNAL(BanUser(int)), com, SLOT(BanUser(int)));
	connect(com, SIGNAL(BanUserRes(bool)), this, SLOT(BanUserEvent(bool)));
	connect(this, SIGNAL(ResetUser(int)), com, SLOT(ResetUser(int)));
	connect(com, SIGNAL(ResetUserRes(bool)), this, SLOT(ResetUserEvent(bool)));
	connect(closeUserAdminButton, SIGNAL(clicked()), this, SLOT(CloseUserOperatorAdminEvent()));

	//AdminOperatorOrganization
	connect(this, SIGNAL(BanOrganization(int)), com, SLOT(BanOrganization(int)));
	connect(com, SIGNAL(BanOrganizationRes(bool)), this, SLOT(BanOrganizationEvent(bool)));
	connect(this, SIGNAL(ResetOrganization(int)), com, SLOT(ResetOrganization(int)));
	connect(com, SIGNAL(ResetOrganizationRes(bool)), this, SLOT(ResetOrganizationEvent(bool)));
	connect(closeOrganizationAdminButton, SIGNAL(clicked()), this, SLOT(CloseOrganizationOperatorAdminEvent()));

	//Chat
	connect(openClientButton, &QPushButton::clicked, this, [this]()
		{
			if (clientWidget->isVisible())
				clientWidget->raise();
			else
				clientWidget->setVisible(true);
		});
	connect(openServerButton, &QPushButton::clicked, this, [this]()
		{
			if (serverWidget->isVisible())
				serverWidget->raise();
			else
				serverWidget->setVisible(true);
		});

	//ChatServer
	connect(this, SIGNAL(ServerInit()), server, SLOT(Init()));
	connect(this, SIGNAL(ServerClose()), server, SLOT(Close()));
	connect(serverPortButton, SIGNAL(clicked()), this, SLOT(SetListenPort()));
	connect(server, SIGNAL(InitRes(bool)), this, SLOT(InitServerEvent(bool)));
	connect(server, SIGNAL(CloseRes(bool)), this, SLOT(CloseServerEvent(bool)));
	connect(server, SIGNAL(ReciveData(QString)), this, SLOT(AddRowInServerModel(QString)));
	connect(server, SIGNAL(ConnectChanged()), this, SLOT(UpdateConnectNum()));

	//ChatClient
	connect(this, SIGNAL(ClientInit()), client, SLOT(Init()));
	connect(this, SIGNAL(ClientClose()), client, SLOT(DisConnect()));
	connect(this, SIGNAL(SendMessageToServer(QString)), client, SLOT(SendOutMessage(QString)));
	connect(clientButton, SIGNAL(clicked()), this, SLOT(SetClientHostAndPort()));
	connect(sendMessageButton, SIGNAL(clicked()), this, SLOT(SendOutMessage()));
	connect(client, SIGNAL(Connected()), this, SLOT(BeginConversation()));
	connect(client, SIGNAL(Message(QString)), this, SLOT(AddRowInClientModel(QString)));
}

void MainWindow::Show()
{
	this->setVisible(true);
	sign->setVisible(!Configuration::AutoSign() && Configuration::OnlineEnable());
}

void MainWindow::InitVolume()
{
	qDebug() << "Call MainThread MainThread InitVolume";
	auto vec = Configuration::VolumeFileSystem();
	PrepareOk = false;
	totalTimes = vec.size();
	nowTimes = 0;
	reInitTimes = 0;
	int j = 0;
	for (auto i = vec.begin(); i != vec.end(); ++i)
	{
		Volume* v = new Volume(i.key(), i.value());
		QThread* th = new QThread;

		volume.push_back(std::move(v));
		volumeThread.push_back(std::move(th));
		volume[j]->moveToThread(volumeThread[j]);

		connect(volume[j], SIGNAL(EmitInfo(QString)), infoLeft, SLOT(ShowInfo(QString)));
		connect(autoUpdate, SIGNAL(timeout()), volume[j], SLOT(AutoUpdate()));
		connect(volume[j], SIGNAL(BeginUpdate()), this, SLOT(UpdateBegin()));
		connect(volume[j], SIGNAL(EndUpdate()), this, SLOT(UpdateEnd()));
		connect(this, SIGNAL(GetFileNameBegin()), volume[j], SLOT(Init()));
		connect(volume[j], SIGNAL(InitRes(bool)), this, SLOT(AfterInit()));
		connect(this, SIGNAL(FindBegin(QVariant)), volume[j], SLOT(FindFile(QVariant)));
		connect(volume[j], SIGNAL(FindRes(char)), this, SLOT(AfterFind(char)));
		connect(this, SIGNAL(ReInit(char)), volume[j], SLOT(ReInit(char)));
		connect(volume[j], SIGNAL(ReInitRes(bool)), this, SLOT(AfterReInit(bool)));
		connect(this, SIGNAL(RemoveData(char)), volume[j], SLOT(RemoveData(char)));
		connect(monitor, SIGNAL(SomeCreated(QString)), volume[j], SLOT(SomeCreated(QString)));
		connect(monitor, SIGNAL(SomeDeleted(QString)), volume[j], SLOT(SomeDeleted(QString)));
		connect(this, SIGNAL(SomeDeleted(QString)), volume[j], SLOT(SomeDeleted(QString)));
		connect(monitor, SIGNAL(SomeRenamed(QString)), volume[j], SLOT(SomeRenamed(QString)));

		volumeThread[j]->start();
		++j;
	}
	emit GetFileNameBegin();
	time.start();
}

void MainWindow::AfterInit()
{
	qDebug() << "Call MainThread AfterInit";
	if (PrepareOk != true)
		++nowTimes;
	if (nowTimes == totalTimes)
	{
		if (autoUpdate->isActive())
			autoUpdate->stop();
		if (Configuration::AutoUpdate())
		{
			updateTimes = 0;
			autoUpdate->start(Configuration::AutoUpdateTime() * 60 * 1000);
		}
		qulonglong fileNumber = 0;
		for (auto i : volume)
			fileNumber += i->FileNumber();
		emit EmitInfo(QStringLiteral("读取完成，总共找到 %1 个条目，用时 %2 秒").arg(fileNumber).arg(time.elapsed() / 1000.0));
		PrepareOk = true;
	}
}

void MainWindow::AfterReInit(bool res)
{
	--reInitTimes;
	if (reInitTimes == 0)
	{
		qulonglong fileNumber = 0;
		for (auto i : volume)
			fileNumber += i->FileNumber();
		emit EmitInfo(QStringLiteral("重新读取完成，加上之前总共找到 %1 个条目，用时 %2 秒").arg(fileNumber).arg(time.elapsed() / 1000.0));
	}
}

void MainWindow::AfterFind(char vol)
{
	qDebug() << "Call MainThread AfterFind";
	++nowTimes;
	for (auto i : volume)
	{
		if (i->VolumeName() == vol)
		{
			rightFileNumber += i->RightFileNumber();
			for (auto j : i->RightFile())
			{
				QStringList it;
				it << j.first << j.second;
				list.push_back(it);
			}
			i->RightFile().clear();
		}
	}
	if (nowTimes == totalTimes)
	{
		emit EmitInfo(QStringLiteral("查找完成，总共找到 %1 个条目，用时 %2 秒").arg(rightFileNumber).arg(time.elapsed() / 1000.0));
		viewModel->setData(list);
		button_f->setEnabled(true);
	}
}

void MainWindow::UpdateBegin()
{
	++updateTimes;
	button_f->setEnabled(false);
	emit EmitInfo(QStringLiteral("自动更新中...请稍等"));
}

void MainWindow::UpdateEnd()
{
	--updateTimes;
	if (updateTimes == 0)
	{
		button_f->setEnabled(true);
		emit EmitInfo(QStringLiteral("自动更新完成"));
	}
}

void MainWindow::FindTriggered()
{
	qDebug() << "Call MainThread FindTriggered";
	if (PrepareOk)
	{
		if (line->text().size() <= 2)
		{
			auto res = QMessageBox::information(this, QStringLiteral("输入字符数小于2!"), QStringLiteral("输入字符过少，可能结果会巨多!\n是否确定？"), QMessageBox::Yes | QMessageBox::No);
			switch (res)
			{
			case QMessageBox::Yes:
				break;
			default:
				return;
			}
		}
		button_f->setEnabled(false);
		list.clear();
		rightFileNumber = 0;
		nowTimes = 0;
		QVariant va;
		va.setValue<FindStruct>({ line->text(),nowType });
		emit FindBegin(va);
		time.start();
	}
}

void MainWindow::QuitEvent()
{
	qDebug() << "Call MainThread QuitEvent";
	trayIcon->setVisible(false);
	WriteSetting();
	qApp->quit();
}

void MainWindow::WriteSetting()
{
	qDebug() << "Call MainThread WriteSetting";
	Configuration::BeforeQuit();
}

void MainWindow::FilterTriggered()
{
	qDebug() << "Call MainThread FilterTriggered";
	if (filter->isVisible())
	{
		line->resize((this->width() - 100) * 0.99, 30);
		Configuration::SetFilterShow(false);
		filter->setVisible(Configuration::FilterShow());
	}
	else
	{
		filter->move(this->width() - 202, 30);
		line->resize((this->width() - 200) * 0.99, 30);
		Configuration::SetFilterShow(true);
		filter->setVisible(Configuration::FilterShow());
	}
}

void MainWindow::InfoTriggered()
{
	qDebug() << "Call MainThread InfoTriggered";
	if (infoLabelLeft->isVisible())
	{
		Configuration::SetInfoShow(false);
		infoLabelLeft->setVisible(Configuration::InfoShow());
	}
	else
	{
		Configuration::SetInfoShow(true);
		infoLabelLeft->setVisible(Configuration::InfoShow());
	}
}

void MainWindow::FilterEvent(int index)
{
	qDebug() << "Call MainThread FilterEvent";
	switch (index)
	{
	case 0:
		nowType = FILTER_ALL;
		break;
	case 1:
		nowType = FILTER_DIRECTORY;
		break;
	case 2:
		nowType = FILTER_COMPRESSED_ARCHIVE;
		break;
	case 3:
		nowType = FILTER_DOCUMENT;
		break;
	case 4:
		nowType = FILTER_PICTURE;
		break;
	case 5:
		nowType = FILTER_AUDIO;
		break;
	case 6:
		nowType = FILTER_VIDEO;
		break;
	}
}

void MainWindow::TrayEvent(QSystemTrayIcon::ActivationReason res)
{
	qDebug() << "Call MainThread TrayEvent";
	if (res == QSystemTrayIcon::DoubleClick || (Configuration::OneClickShow() && res == QSystemTrayIcon::Trigger))
		if (this->isVisible())
			this->activateWindow();
		else
		{
			this->show();
			this->activateWindow();
		}
}

void MainWindow::AboutTriggered()
{
	qDebug() << "Call MainThread AboutTriggered";
	if (about->isVisible())
	{
		about->setVisible(false);
	}
	else
	{
		about->setVisible(true);
	}
}

void MainWindow::OptionTriggered()
{
	qDebug() << "Call MainThread OptionTriggered";
	if (option->isVisible())
	{
		option->activateWindow();
	}
	else
	{
		boxi_1->setChecked(Configuration::RunInBackground());
		boxi_2->setChecked(Configuration::TrayShow());
		boxi_3->setChecked(Configuration::OneClickShow());
		boxi_3->setEnabled(boxi_2->isChecked());
		boxi_4->setChecked(Configuration::SelectAll());
		boxi_5->setChecked(!Configuration::OnlineEnable());
		boxs_1->setChecked(Configuration::SearchCaseSensitive());
		boxs_2->setChecked(Configuration::SearchMatchPath());
		boxs_3->setChecked(Configuration::SearchMatchFile());
		boxs_4->setChecked(Configuration::SearcRegEx());
		boxs_5->setChecked(Configuration::AutoUpdate());
		autoTimeBox->setValue(Configuration::AutoUpdateTime());
		autoTimeBox->setEnabled(boxs_5->isChecked());
		boxv_1->setChecked(Configuration::FilterShow());
		boxv_2->setChecked(Configuration::InfoShow());
		QList<QStringList> list_ntfs;
		QList<QStringList> list_other;
		auto volVec = Configuration::VolumeFileSystem();
		for (auto i = volVec.begin(); i != volVec.end(); ++i)
		{
			QStringList it;
			if (i.value() & VOLUME_IS_NTFS)
			{
				it << QString("%1:").arg(i.key());
				if (i.value() & VOLUME_USEING)
				{
					it << QStringLiteral("启用");
				}
				else
				{
					it << QStringLiteral("停用");
				}
				list_ntfs.push_back(it);
			}
			else if (i.value() & VOLUME_NOT_NTFS)
			{
				it << QString(i.key() + ':');
				if (i.value() & VOLUME_USEING)
				{
					it << QStringLiteral("启用");
				}
				else
				{
					it << QStringLiteral("停用");
				}
				list_other.push_back(it);
			}
		}
		ntfsVolumeModel->setData(list_ntfs);
		otherVolumeModel->setData(list_other);
		QStringList list_ignore;
		for (auto i : Configuration::IgnorePath())
		{
			list_ignore.append(i);
		}
		ignoreModel->setData(list_ignore);
		QStringList list_monitor;
		for (auto i : Configuration::MonitorPath())
		{
			list_monitor.append(i);
		}
		monitorModel->setData(list_monitor);
		option->setVisible(true);
	}
}

void MainWindow::HelpTriggered()
{
	QDesktopServices::openUrl(QUrl(QLatin1String("https://robber.ltd/2022/01/18/chunchunsearcher-help/")));
}

void MainWindow::OptionToSubmit()
{
	qDebug() << "Call MainThread OptionToSubmit";
	option->setVisible(false);
	Configuration::SetRunInBackground(boxi_1->isChecked());
	Configuration::SetTrayShow(boxi_2->isChecked());
	Configuration::SetOneClickShow(boxi_3->isChecked());
	Configuration::SetSelectAll(boxi_4->isChecked());
	Configuration::SetOnlineEnable(!boxi_5->isChecked());
	if (Configuration::OnlineEnable())
		emit RetryToOnline();
	Configuration::SetSearchCaseSensitive(boxs_1->isChecked());
	Configuration::SetSearchMatchPath(boxs_2->isChecked());
	Configuration::SetSearchMatchFile(boxs_3->isChecked());
	Configuration::SetSearcRegEx(boxs_4->isChecked());
	Configuration::SetAutoUpdate(boxs_5->isChecked());
	Configuration::SetAutoUpdateTime(autoTimeBox->value());
	if (Configuration::AutoUpdate())
	{
		if (autoUpdate->isActive())
		{
			autoUpdate->stop();
		}
		autoUpdate->setInterval(Configuration::AutoUpdateTime() * 60 * 1000);
		autoUpdate->start();
		updateTimes = 0;
	}
	else
	{
		if (autoUpdate->isActive())
		{
			autoUpdate->stop();
		}
	}
	Configuration::SetFilterShow(boxv_1->isChecked());
	Configuration::SetInfoShow(boxv_2->isChecked());
	auto ntfsVec = Configuration::VolumeFileSystem();
	for (auto i : ntfsVolumeModel->getData())
	{
		char c = i[0][0].toLatin1();
		if (i[1].compare(QStringLiteral("启用")) == 0)
		{
			if (ntfsVec.find(c).value() & VOLUME_DISCARD)
			{
				__int8 attr = VOLUME_IS_NTFS | VOLUME_USEING;
				emit ReInit(c);
				Configuration::SetVolumeFileSystem(c, attr);
				++reInitTimes;
			}
		}
		else if (i[1].compare(QStringLiteral("停用")) == 0)
		{
			if (ntfsVec.find(c).value() & VOLUME_USEING)
			{
				__int8 attr = VOLUME_IS_NTFS | VOLUME_DISCARD;
				emit RemoveData(c);
				Configuration::SetVolumeFileSystem(c, attr);
			}
		}
	}
	ntfsVec = Configuration::VolumeFileSystem();
	for (auto i : otherVolumeModel->getData())
	{
		char c = i[0][0].toLatin1();
		if (i[1].compare(QStringLiteral("启用")) == 0)
		{
			if (ntfsVec.find(c).value() & VOLUME_DISCARD)
			{
				__int8 attr = VOLUME_NOT_NTFS | VOLUME_USEING;
				emit ReInit(c);
				Configuration::SetVolumeFileSystem(c, attr);
				++reInitTimes;
			}
		}
		else if (i[1].compare(QStringLiteral("停用")) == 0)
		{
			if (ntfsVec.find(c).value() & VOLUME_USEING)
			{
				__int8 attr = VOLUME_NOT_NTFS | VOLUME_DISCARD;
				emit RemoveData(c);
				Configuration::SetVolumeFileSystem(c, attr);
			}
		}
	}
	Configuration::SetIgnorePath(ignoreModel->getData());
	auto vecMonitor = monitorModel->getData();
	auto vecConfMonitor = Configuration::MonitorPath();
	for (auto i : vecConfMonitor)
	{
		if (!vecMonitor.contains(i))
		{
			monitor->RemovePath(i);
		}
	}
	for (auto i : vecMonitor)
	{
		if (!vecConfMonitor.contains(i))
		{
			monitor->AddPath(i);
		}
	}
	Configuration::SetMonitorPath(vecMonitor);
	time.start();
	Update();
}

void MainWindow::OptionCancel()
{
	qDebug() << "Call MainThread OptionCancel";
	option->setVisible(false);
}

void MainWindow::SearchCaseSensitiveTriggered()
{
	qDebug() << "Call MainThread SearchCaseSensitiveTriggered" << !Configuration::SearchCaseSensitive();
	auto res = Configuration::SearchCaseSensitive();
	Configuration::SetSearchCaseSensitive(!res);
	action3_1->setChecked(Configuration::SearchCaseSensitive());
}

void MainWindow::SearchMatchPathTriggered()
{
	qDebug() << "Call MainThread SearchMatchPathTriggered" << !Configuration::SearchMatchPath();
	auto res = Configuration::SearchMatchPath();
	Configuration::SetSearchMatchPath(!res);
	action3_2->setChecked(Configuration::SearchMatchPath());
}

void MainWindow::SearchMatchFileTriggered()
{
	qDebug() << "Call MainThread SearchMatchFileTriggered" << !Configuration::SearchMatchFile();
	auto res = Configuration::SearchMatchFile();
	Configuration::SetSearchMatchFile(!res);
	action3_3->setChecked(Configuration::SearchMatchFile());
}

void MainWindow::SearcRegExTriggered()
{
	qDebug() << "Call MainThread SearcRegExTriggered" << !Configuration::SearcRegEx();
	auto res = Configuration::SearcRegEx();
	Configuration::SetSearcRegEx(!res);
	action3_4->setChecked(Configuration::SearcRegEx());
}

void MainWindow::RightClicked(const QPoint& pos)
{
	qDebug() << "Call MainThread RightClicked" << tableView->selectionModel()->currentIndex();
	rightMenu->exec(mapToGlobal(pos));
}

void MainWindow::OpenFile()
{
	auto index = tableView->currentIndex();
	qDebug() << "Call MainThread OpenFile" % viewModel->FullPath(index);
	QFileInfo fileInfo(viewModel->FullPath(index));
	if (fileInfo.exists())
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
	}
}

void MainWindow::OpenPath()
{
	auto index = tableView->currentIndex();
	qDebug() << "Call MainThread OpenPath" % viewModel->Path(index);
	QFileInfo fileInfo(viewModel->Path(index));
	if (fileInfo.exists())
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
	}
}

void MainWindow::CopyFullPath()
{
	qDebug() << "Call MainThread CopyFullPath" % viewModel->FullPath(tableView->currentIndex());
	QApplication::clipboard()->setText(viewModel->FullPath(tableView->currentIndex()));
}

void MainWindow::CopyPath()
{
	qDebug() << "Call MainThread CopyPath";
	QApplication::clipboard()->setText(viewModel->Path(tableView->currentIndex()));
}

void MainWindow::Delete()
{
	auto res = QMessageBox::information(this, QStringLiteral("是否继续？"), QStringLiteral("是否继续?\n删除的文件/文件夹无法通过回收站找回"), QMessageBox::Yes | QMessageBox::No);
	if (res != QMessageBox::Yes)
	{
		return;
	}
	auto index = tableView->currentIndex();
	qDebug() << "Call MainThread Delete" % viewModel->FullPath(index);
	QFileInfo fileInfo(viewModel->FullPath(index));
	if (fileInfo.isDir())
	{
		QDir dir(viewModel->FullPath(index));
		if (dir.removeRecursively())
		{
			viewModel->deleteData(index);
			emit SomeDeleted(viewModel->Path(index) % '*' % viewModel->Name(index));
		}
	}
	else if (fileInfo.isFile())
	{
		QFile file(viewModel->FullPath(index));
		if (file.remove())
		{
			viewModel->deleteData(index);
		}
	}
}

void MainWindow::Attribute()
{
	auto index = tableView->currentIndex();
	qDebug() << "Call MainThread Attribute" % viewModel->FullPath(index);
	std::wstring fullPath = viewModel->FullPath(index).toStdWString();
	SHELLEXECUTEINFOW sei;
	sei.hwnd = NULL;
	sei.lpVerb = L"properties";
	sei.lpFile = fullPath.c_str();
	sei.lpDirectory = NULL;
	sei.lpParameters = NULL;
	sei.nShow = SW_SHOWNORMAL;
	sei.fMask = SEE_MASK_INVOKEIDLIST;
	sei.lpIDList = NULL;
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	ShellExecuteExW(&sei);
}

void MainWindow::UpLoadFile()
{
	upLoadUserButton->setEnabled(true);
	upLoadOrganizationButton->setEnabled(true);
	upLoad->setVisible(true);
	upLoad->setWindowTitle(viewModel->Name(tableView->currentIndex()));

	upLoadFileBar->setValue(0);

	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(DownLoadProgressEvent(qint64, qint64))));
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(UpLoadUserProgressEvent(qint64, qint64))));
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(DownLoadAdminProgressProgressEvent(qint64, qint64))));
	connect(com, SIGNAL(LoadProgressRes(qint64, qint64)), this, SLOT(UpLoadUserProgressEvent(qint64, qint64)));
}

void MainWindow::VolumeNtfsStateChange()
{
	auto current = ntfsVolumeView->currentIndex();
	qDebug() << "Call MainThread VolumeNtfsStateChange" << current;
	if (!current.isValid())
	{
		QMessageBox::information(indexOptions[0], QStringLiteral("未选中!"), QStringLiteral("错误!\n未选择任何卷!"));
		return;
	}
	if (ntfsVolumeModel->isVaild(current))
	{
		auto it = ntfsVolumeModel->getRowData(current);
		if (it[1].compare(QStringLiteral("启用")) == 0)
		{
			it[1] = QStringLiteral("停用");
		}
		else
		{
			it[1] = QStringLiteral("启用");
		}
		ntfsVolumeModel->updateData(current, it);
	}
}

void MainWindow::VolumeOtherStateChange()
{
	auto current = ntfsVolumeView->currentIndex();
	qDebug() << "Call MainThread VolumeNtfsStateChange" << current;
	if (!current.isValid())
	{
		QMessageBox::information(indexOptions[0], QStringLiteral("未选中!"), QStringLiteral("错误!\n未选择任何卷!"));
		return;
	}
	if (otherVolumeModel->isVaild(current))
	{
		auto it = otherVolumeModel->getRowData(current);
		if (it[1].compare(QStringLiteral("启用")) == 0)
		{
			it[1] = QStringLiteral("停用");
		}
		else
		{
			it[1] = QStringLiteral("启用");
		}
		otherVolumeModel->updateData(current, it);
	}
}

void MainWindow::IgnorePathAdd()
{
	qDebug() << "Call MainThread IgnorePathAdd";
	QFileDialog* fileDialog = new QFileDialog(indexOptions[1]);
	fileDialog->setFileMode(QFileDialog::DirectoryOnly);
	if (fileDialog->exec() == QFileDialog::Accepted)
	{
		auto it = QDir::toNativeSeparators(fileDialog->selectedFiles().at(0));
		ignoreModel->addData(it);
	}
}

void MainWindow::IgnorePathRemove()
{
	auto current = ignoreView->currentIndex();
	qDebug() << "IgnorePathRemove" << current;
	if (!current.isValid())
	{
		QMessageBox::information(indexOptions[0], QStringLiteral("未选中!"), QStringLiteral("错误!\n未选择任何卷!"));
		return;
	}
	if (ignoreModel->isVaild(current))
	{
		auto it = ignoreModel->getRowData(current);
		ignoreModel->deleteData(current);
	}
}

void MainWindow::MonitorPathAdd()
{
	qDebug() << "Call MainThread MonitorPathAdd";
	QFileDialog* fileDialog = new QFileDialog(indexOptions[2]);
	fileDialog->setFileMode(QFileDialog::DirectoryOnly);
	if (fileDialog->exec() == QFileDialog::Accepted)
	{
		auto it = QDir::toNativeSeparators(fileDialog->selectedFiles().at(0));
		monitorModel->addData(it);
	}
}

void MainWindow::MonitorPathRemove()
{
	auto current = monitorView->currentIndex();
	qDebug() << "MonitorPathRemove" << current;
	if (!current.isValid())
	{
		QMessageBox::information(indexOptions[0], QStringLiteral("未选中!"), QStringLiteral("错误!\n未选择任何卷!"));
		return;
	}
	if (monitorModel->isVaild(current))
	{
		auto it = monitorModel->getRowData(current);
		monitorModel->deleteData(current);
	}
}

void MainWindow::OneClickShowTriggered()
{
	qDebug() << "Call MainThread OneClickShowTriggered";
	if (boxi_2->isChecked())
		boxi_3->setEnabled(true);
	else
		boxi_3->setEnabled(false);
}

void MainWindow::AutoUpdateTriggered()
{
	qDebug() << "Call MainThread AutoUpdateTriggered";
	if (boxs_5->isChecked())
		autoTimeBox->setEnabled(true);
	else
		autoTimeBox->setEnabled(false);
}

void MainWindow::Update()
{
	qDebug() << "Call MainThread Update";
	if (trayIcon->isVisible() != Configuration::TrayShow())
	{
		trayIcon->setVisible(true);
	}
	if (filter->isVisible() != Configuration::FilterShow())
	{
		FilterTriggered();
	}
	if (infoLabelLeft->isVisible() != Configuration::InfoShow())
	{
		InfoTriggered();
	}
	action2_1->setChecked(Configuration::FilterShow());
	action2_2->setChecked(Configuration::InfoShow());
	action3_1->setChecked(Configuration::SearchCaseSensitive());
	action3_2->setChecked(Configuration::SearchMatchPath());
	action3_3->setChecked(Configuration::SearchMatchFile());
	action3_4->setChecked(Configuration::SearcRegEx());
}

void MainWindow::SignWidgetTriggered()
{
	qDebug() << "Call MainThread SignWidgetTriggered";
	if (!Configuration::OnlineEnable())
	{
		QMessageBox::information(this, QStringLiteral("本地模式"), QStringLiteral("当前为本地模式，请于设置中开启网络"), QMessageBox::Ok);
		return;
	}
	if (!sign->isVisible())
		sign->setVisible(true);
	else
		sign->raise();
}

void MainWindow::SignTriggered()
{
	qDebug() << "Call MainThread SignTriggered";
	Configuration::SetUsername(nameLine->text());
	Configuration::SetPassword(QCryptographicHash::hash(passLine->text().toLatin1(), QCryptographicHash::Md5).toHex());
	nameLine->setEnabled(false);
	passLine->setEnabled(false);
	button_autosign->setEnabled(false);
	button_s->setEnabled(false);
	button_r->setEnabled(false);
	button_skip->setEnabled(false);
	emit Sign();
}

void MainWindow::RegisterTriggered()
{
	qDebug() << "Call MainThread RegisterTriggered";
	Configuration::SetUsername(nameLine->text());
	Configuration::SetPassword(QCryptographicHash::hash(passLine->text().toLatin1(), QCryptographicHash::Md5).toHex());
	nameLine->setEnabled(false);
	passLine->setEnabled(false);
	button_s->setEnabled(false);
	button_r->setEnabled(false);
	button_skip->setEnabled(false);
	emit Register();
}

void MainWindow::OnlineEvent(bool res)
{
	qDebug() << "Call MainThread OnlineEvent";
	if (res)
	{
		if (Configuration::AutoSign() && !Configuration::Username().isEmpty() && !Configuration::Password().isEmpty())
		{
			emit Sign();
		}
	}
	else
	{
		LOG(INFO) << QStringLiteral("无法连接到服务器");
		auto res = QMessageBox::information(this, QStringLiteral("无法连接到服务器"), QStringLiteral("无法连接到服务器，是否重试？"), QMessageBox::Yes | QMessageBox::No);
		switch (res)
		{
		case QMessageBox::Yes:
			emit RetryToOnline();
			break;
		case QMessageBox::No:
		default:
			break;
		}
	}
}

void MainWindow::SignEvent(bool res)
{
	qDebug() << "Call MainThread SignEvent";
	nameLine->setEnabled(true);
	passLine->setEnabled(true);
	button_s->setEnabled(true);
	button_r->setEnabled(true);
	button_skip->setEnabled(true);
	lab_s_f->setVisible(false);
	lab_r_f->setVisible(false);
	if (res)
	{
		qDebug() << "Sign Success";
		if (sign->isVisible())
			sign->setVisible(false);
		Configuration::SetIsSigned(true);
		Configuration::SetAutoSign(button_autosign->isChecked());
		emit GetUserInfo();
	}
	else
	{
		qDebug() << "Sign Fail";
		if (!sign->isVisible())
			sign->raise();
		lab_s_f->setVisible(true);
		passLine->setText("");
		button_autosign->setEnabled(true);
		button_autosign->setChecked(false);
		Configuration::SetUsername("");
		Configuration::SetPassword("");
	}
}

void MainWindow::RegisterEvent(bool res)
{
	qDebug() << "Call MainThread RegisterEvent";
	nameLine->setEnabled(true);
	passLine->setEnabled(true);
	button_s->setEnabled(true);
	button_r->setEnabled(true);
	button_skip->setEnabled(true);
	lab_s_f->setVisible(false);
	lab_r_f->setVisible(false);
	if (res)
	{
		qDebug() << "Register Success";
		if (sign->isVisible())
			sign->setVisible(false);
		Configuration::SetIsSigned(true);
		Configuration::SetAutoSign(button_autosign->isChecked());
		UpdateMenu();
	}
	else
	{
		qDebug() << "Register Fail";
		if (!sign->isVisible())
			sign->raise();
		lab_r_f->setVisible(true);
		nameLine->setText("");
		passLine->setText("");
		Configuration::SetUsername("");
		Configuration::SetPassword("");
	}
}

void MainWindow::GetConfEvent(bool res)
{
	qDebug() << "Call MainThread GetConfEvent";
	if (res)
	{
		qDebug() << "Get Conf Success";
		auto res = QMessageBox::information(infoPersonal[2], QStringLiteral("获取到云端设置"), QStringLiteral("获取到云端设置，是否覆盖？"), QMessageBox::Yes | QMessageBox::No);
		switch (res)
		{
		case QMessageBox::Yes:
			WriteToConf();
			Update();
			break;
		case QMessageBox::No:
		default:
			break;
		}
	}
	else
	{
		qDebug() << "Get Conf Fail";
		QMessageBox::information(infoPersonal[2], QStringLiteral("获取云端设置失败"), QStringLiteral("获取云端设置失败，请检查网络或重试"), QMessageBox::Ok);
	}
}

void MainWindow::WriteConfEvent(bool res)
{
	qDebug() << "Call MainThread WriteConfEvent";
	if (res)
	{
		qDebug() << "Write Conf Success";
		QMessageBox::information(personal, QStringLiteral("写入成功"), QStringLiteral("写入成功"), QMessageBox::Ok);
	}
	else
	{
		qDebug() << "Write Fail";
		QMessageBox::information(personal, QStringLiteral("写入失败"), QStringLiteral("写入失败，请检测网络是否有问题以及与上次上传是否有改动"), QMessageBox::Ok);
	}
}

void MainWindow::SkipTriggered()
{
	qDebug() << "Call MainThread SkipTriggered";
	sign->setVisible(false);
	Configuration::SetIsSigned(false);
	Configuration::SetUsername("");
	Configuration::SetPassword("");
	Configuration::SetAutoSign(false);
	this->raise();
}

void MainWindow::UpdateMenu()
{
	qDebug() << "Call MainThread UpdateMenu";
	if (Configuration::IsSigned())
	{
		menu4->removeAction(action4_1);
		menu4->addAction(action4_2);
		menu4->addAction(action4_3);
		menu4->addAction(action4_4);
		if (Configuration::Power() == 5)
			menu4->addAction(action4_5);
		menu4->addAction(action4_6);
	}
	else
	{
		menu4->removeAction(action4_2);
		menu4->removeAction(action4_3);
		menu4->removeAction(action4_4);
		menu4->removeAction(action4_5);
		menu4->removeAction(action4_6);
		menu4->addAction(action4_1);
	}
}

void SetValueToKey(QString str)
{
	auto pos = str.indexOf("=");
	QString key = str.mid(0, pos);
	QString value = str.mid(pos + 1);
	if (!key.compare("autoSign"))
		Configuration::SetAutoSign(!value.compare("true"));
	if (!key.compare("onlineEnable"))
		Configuration::SetOnlineEnable(!value.compare("true"));
	if (!key.compare("posX"))
		Configuration::SetPosX(value.toInt());
	if (!key.compare("posY"))
		Configuration::SetPosY(value.toInt());
	if (!key.compare("width"))
		Configuration::SetWidth(value.toInt());
	if (!key.compare("height"))
		Configuration::SetHeight(value.toInt());
	if (!key.compare("autoUpdateTime"))
		Configuration::SetAutoUpdateTime(value.toInt());
	if (!key.compare("infoShow"))
		Configuration::SetInfoShow(!value.compare("true"));
	if (!key.compare("searchCaseSensitive"))
		Configuration::SetSearchCaseSensitive(!value.compare("true"));
	if (!key.compare("searchMatchPath"))
		Configuration::SetSearchMatchPath(!value.compare("true"));
	if (!key.compare("searchMatchFile"))
		Configuration::SetSearchMatchFile(!value.compare("true"));
	if (!key.compare("searcRegEx"))
		Configuration::SetSearcRegEx(!value.compare("true"));
	if (!key.compare("runInBackground"))
		Configuration::SetRunInBackground(!value.compare("true"));
	if (!key.compare("trayShow"))
		Configuration::SetTrayShow(!value.compare("true"));
	if (!key.compare("oneClickShow"))
		Configuration::SetOneClickShow(!value.compare("true"));
	if (!key.compare("selectAll"))
		Configuration::SetSelectAll(!value.compare("true"));
	if (!key.compare("autoUpdate"))
		Configuration::SetAutoUpdate(!value.compare("true"));
	if (!key.compare("ignorePath"))
	{
		QStringList path;
		auto pos = value.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			path.push_back(value.mid(start, pos - start));
			start = pos + 1;
			pos = value.indexOf('*', pos + 1);
		}
		Configuration::ReSetIgnorePath();
		Configuration::SetIgnorePath(path);
	}
	if (!key.compare("ignorePath"))
	{
		QStringList path;
		auto pos = value.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			path.push_back(value.mid(start, pos - start));
			start = pos + 1;
			pos = value.indexOf('*', pos + 1);
		}
		Configuration::ReSetMonitorPath();
		Configuration::SetMonitorPath(path);
	}
	if (!key.compare("volumeFileSystem"))
	{
		auto pos = value.indexOf('*');
		auto start = 0;
		while (pos != -1)
		{
			QString line = value.mid(start, pos - start);
			start = pos + 1;
			pos = value.indexOf('*', pos + 1);
			Configuration::SetVolumeFileSystem(line[0].toLatin1(), line[1].toLatin1());
		}
	}
}

void MainWindow::WriteToConf()
{
	qDebug() << "Call MainThread WriteToConf";
	if (!Configuration::CloudConf().isEmpty())
	{
		auto pos = Configuration::CloudConf().indexOf('\n');
		auto start = 0;
		while (pos != -1)
		{
			QString line = Configuration::CloudConf().mid(start, pos - start);
			start = pos + 1;
			pos = Configuration::CloudConf().indexOf('\n', pos + 1);
			SetValueToKey(line);
		}
	}
	emit EmitInfo(QStringLiteral("更新完成"));
}

void MainWindow::SignOut()
{
	qDebug() << "Call MainThread SignOut";
	Configuration::SetIsSigned(false);
	Configuration::SetUsername("");
	Configuration::SetPassword("");
	Configuration::SetAutoSign(false);
	Configuration::SetUserId(0);
	Configuration::SetStatus(0);
	Configuration::SetPower(0);
	Configuration::SetOrganizationId(0);
	Configuration::SetOrganizationName("");
	Configuration::SetOrganizationStatus(0);
	button_autosign->setEnabled(true);
	button_autosign->setChecked(false);
	nameLine->setText("");
	passLine->setText("");
	ClearModelExcept();
	UpdateMenu();
}

void MainWindow::PersonalTriggered()
{
	qDebug() << "Call MainThread PersonalTriggered";
	if (personal->isVisible())
		personal->raise();
	else
	{
		UpdatePersonal();
		emit ShowUserFile();
		personal->setVisible(true);
	}
}

void MainWindow::OrganizationTriggered()
{
	qDebug() << "Call MainThread OrganizationTriggered";
	if (organization->isVisible())
		organization->raise();
	else
	{
		UpdateOrganization();
		organization->setVisible(true);
		emit ShowOrganizationFile();
		emit GetOrganizationMembers();
		emit ShowAppealOrganization();
	}
}

void MainWindow::AdminTriggered()
{
	qDebug() << "Call MainThread AdminTriggered";
	if (admin->isVisible())
		admin->raise();
	else
	{
		emit ShowUser();
		emit ShowOrganization();
		emit ShowFile();
		admin->setVisible(true);
	}
}

void MainWindow::ChatTriggered()
{
	qDebug() << "Call MainThread ChatTriggered";
	if (admin->isVisible())
		chatWidget->raise();
	else
		chatWidget->setVisible(true);
}

void MainWindow::GetUserInfoEvent(bool res)
{
	qDebug() << "Call MainThread GetUserInfoEvent";
	if (res)
		UpdateMenu();
	else
		QMessageBox::information(this, QStringLiteral("获取用户信息失败"), QStringLiteral("获取用户信息失败，请重新登录"), QMessageBox::Ok);
}

void MainWindow::LeaveOrganizationEvent(bool res)
{
	if (res)
	{
		emit GetOrganizationMembers();
		QMessageBox::information(personal, QStringLiteral("用户离开组织成功"), QStringLiteral("用户离开组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(personal, QStringLiteral("用户离开组织失败"), QStringLiteral("用户离开组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::AppealUserEvent(bool res)
{
	appealUserButton->setEnabled(true);
	if (res)
	{
		QMessageBox::information(operatorFile, QStringLiteral("申诉成功"), QStringLiteral("申诉成功"), QMessageBox::Ok);
		emit GetUserInfo();
	}
	else
	{
		QMessageBox::information(operatorFile, QStringLiteral("申诉失败"), QStringLiteral("申诉失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::AppealFileEvent(bool res)
{
	operatorFile->setProperty("doing", false);
	if (res)
	{
		appealFileLab->setText(QStringLiteral("当前状态:") % Status(1));
		downLoadFileButton->setEnabled(true);
		emit ShowUserFile();
		if (Configuration::OrganizationId() != 0)
			emit ShowOrganizationFile();
		QMessageBox::information(operatorFile, QStringLiteral("申诉成功"), QStringLiteral("申诉成功"), QMessageBox::Ok);
	}
	else
	{
		appealFileLab->setEnabled(true);
		QMessageBox::information(operatorFile, QStringLiteral("申诉失败"), QStringLiteral("申诉失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::UpLoadUserFile()
{
	qDebug() << "Call MainThread UpLoadUserFile";
	upLoad->setProperty("doing", true);
	auto index = tableView->currentIndex();
	qDebug() << viewModel->FullPath(index);
	emit UpLoadUserFile(viewModel->FullPath(index));
	upLoadUserButton->setEnabled(false);
}

void MainWindow::UpLoadOrganizationFile()
{
	qDebug() << "Call MainThread UpLoadOrganizationFile";
	upLoad->setProperty("doing", true);
	auto index = tableView->currentIndex();
	qDebug() << viewModel->FullPath(index);
	emit UpLoadOrganizationFile(viewModel->FullPath(index));
	upLoadOrganizationButton->setEnabled(false);
}

void MainWindow::UpLoadUserFileEvent(bool res)
{
	qDebug() << "Call MainThread UpLoadUserFileEvent";
	upLoad->setProperty("doing", false);
	if (res)
	{
		emit ShowUserFile();
		QMessageBox::information(upLoad, QStringLiteral("上传成功"), QStringLiteral("上传成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(upLoad, QStringLiteral("上传失败"), QStringLiteral("上传失败，请重试"), QMessageBox::Ok);
		upLoadUserButton->setEnabled(true);
	}
}

void MainWindow::UpLoadOrganizationFileEvent(bool res)
{
	qDebug() << "Call MainThread UpLoadOrganizationFileEvent";
	upLoad->setProperty("doing", false);
	if (res)
	{
		emit ShowOrganizationFile();
		QMessageBox::information(upLoad, QStringLiteral("上传成功"), QStringLiteral("上传成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(upLoad, QStringLiteral("上传失败"), QStringLiteral("上传失败，请重试"), QMessageBox::Ok);
		upLoadOrganizationButton->setEnabled(true);
	}
}

void MainWindow::WriteConfClicked()
{
	qDebug() << "Call MainThread WriteConfClicked";
	emit WriteConf();
}

void MainWindow::GetConfClicked()
{
	qDebug() << "Call MainThread GetConfClicked";
	emit GetConf();
}

QString MainWindow::Status(int num)
{
	switch (num)
	{
	case 0:
		return QStringLiteral("正常");
	case 1:
		return QStringLiteral("申诉中");
	case 2:
		return QStringLiteral("封禁");
	}
}

QString MainWindow::Power(int num)
{
	switch (num)
	{
	case 0:
		return QStringLiteral("普通会员");
	case 1:
		return QStringLiteral("组织成员");
	case 2:
		return QStringLiteral("组织文件管理员");
	case 3:
		return QStringLiteral("组织成员管理员");
	case 4:
		return QStringLiteral("组织创建者");
	case 5:
		return QStringLiteral("超级管理员");
	}
}

void MainWindow::ShowUserFileEvent(QJsonArray obj)
{
	qDebug() << "Call MainThread ShowUserFileEvent";
	userFileModel->clear();
	for (auto i = 0; i < obj.size(); ++i)
	{
		QStringList it;
		auto ob = obj.at(i).toObject();
		it << ob.value("filename").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		userFileModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userfile", 1);
		operatorButton->setProperty("fileid", ob.value("fileid").toInt());
		operatorButton->setProperty("filename", ob.value("filename").toString());
		operatorButton->setProperty("status", ob.value("status").toInt());
		if (Configuration::Status() != 0)
			operatorButton->setEnabled(false);
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(OperatorFile()));
		userFileView->setIndexWidget(userFileModel->index(i, 2), operatorButton);
	}
}

void MainWindow::ShowOrganizationFileEvent(QJsonArray obj)
{
	qDebug() << "Call MainThread ShowOrganizationFileEvent";
	organizationFileModel->clear();
	for (auto i = 0; i < obj.size(); ++i)
	{
		QStringList it;
		auto ob = obj.at(i).toObject();
		it << ob.value("filename").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		organizationFileModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userfile", 0);
		operatorButton->setProperty("fileid", ob.value("fileid").toInt());
		operatorButton->setProperty("filename", ob.value("filename").toString());
		operatorButton->setProperty("status", ob.value("status").toInt());
		if (Configuration::Power() < 2)
			operatorButton->setEnabled(false);
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(OperatorFile()));
		organizationFileView->setIndexWidget(organizationFileModel->index(i, 2), operatorButton);
	}
}

void MainWindow::GetOrganizationMembersEvent(QJsonArray obj)
{
	qDebug() << "Call MainThread GetOrganizationMembersEvent";
	organizationMemberModel->clear();
	for (auto i = 0; i < obj.size(); ++i)
	{
		QStringList it;
		auto ob = obj.at(i).toObject();
		it << ob.value("username").toString()
			<< Power(ob.value("power").toInt())
			<< Status(ob.value("status").toInt())
			<< QString();
		organizationMemberModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userid", ob.value("userid").toInt());
		operatorButton->setProperty("username", ob.value("username").toString());
		operatorButton->setProperty("power", ob.value("power").toInt());
		if (Configuration::Power() < 3 || Configuration::UserId() == ob.value("userid").toInt())
			operatorButton->setEnabled(false);
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(OperatorOrganizationMembers()));
		organizationMemberView->setIndexWidget(organizationMemberModel->index(i, 3), operatorButton);
	}
}

void MainWindow::OperatorFile()
{
	QPushButton* button = (QPushButton*)sender();
	int fileid = button->property("fileid").toInt();
	QString filename = button->property("filename").toString();
	int status = button->property("status").toInt();

	downLoadFileBar->setValue(0);
	operatorFile->setWindowTitle(filename);
	downLoadFileButton->setEnabled(status == 0);
	appealFileButton->setEnabled(status == 2);
	appealFileLab->setText(QStringLiteral("当前状态:") % Status(status));

	disconnect(downLoadFileButton, 0, 0, 0);
	disconnect(appealFileButton, 0, 0, 0);
	disconnect(deleteFileButton, 0, 0, 0);
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(DownLoadProgressEvent(qint64, qint64))));
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(UpLoadUserProgressEvent(qint64, qint64))));
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(DownLoadAdminProgressProgressEvent(qint64, qint64))));
	connect(com, SIGNAL(LoadProgressRes(qint64, qint64)), this, SLOT(DownLoadProgressEvent(qint64, qint64)));
	connect(downLoadFileButton, &QPushButton::clicked, this, [fileid, this]()
		{
			operatorFile->setProperty("doing", true);
			downLoadFileButton->setEnabled(false);
			emit DownLoadFile(fileid);
		});
	connect(appealFileButton, &QPushButton::clicked, this, [fileid, this]()
		{
			operatorFile->setProperty("doing", true);
			appealFileButton->setEnabled(false);
			emit AppealFile(fileid);
		});
	if (button->property("userfile").toBool())
	{
		connect(deleteFileButton, &QPushButton::clicked, this, [fileid, this]()
			{
				auto res = QMessageBox::information(operatorFile, QStringLiteral("是否删除"), QStringLiteral("是否删除，删除后无法找回"), QMessageBox::Yes | QMessageBox::No);
				switch (res)
				{
				case QMessageBox::Yes:
					operatorFile->setProperty("doing", true);
					emit DeleteUserFile(fileid);
					downLoadFileButton->setEnabled(false);
					appealFileButton->setEnabled(false);
				}
			});
	}
	else
	{
		connect(deleteFileButton, &QPushButton::clicked, this, [fileid, this]()
			{
				auto res = QMessageBox::information(operatorFile, QStringLiteral("是否删除"), QStringLiteral("是否删除，删除后无法找回"), QMessageBox::Yes | QMessageBox::No);
				switch (res)
				{
				case QMessageBox::Yes:
					operatorFile->setProperty("doing", true);
					emit DeleteUserFile(fileid);
					downLoadFileButton->setEnabled(false);
					appealFileButton->setEnabled(false);
				}
			});
	}
	operatorFile->setVisible(true);
}

void MainWindow::DownLoadFileEvent(bool res)
{
	operatorFile->setProperty("doing", false);
	operatorAdminFile->setProperty("doing", false);
	if (res)
	{
		QMessageBox::information(operatorFile->isVisible() ? operatorFile : operatorAdminFile, QStringLiteral("下载成功"), QStringLiteral("下载成功，文件保存在 \"") % QApplication::applicationDirPath() % "/download/" % Configuration::Username() % QStringLiteral("\" 目录下"), QMessageBox::Ok);
	}
	else
	{
		downLoadFileButton->setEnabled(true);
		downLoadFileAdminButton->setEnabled(true);
		QMessageBox::information(operatorFile->isVisible() ? operatorFile : operatorAdminFile, QStringLiteral("下载失败"), QStringLiteral("下载失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::DeleteUserFileEvent(bool res)
{
	operatorFile->setProperty("doing", false);
	if (res)
	{
		emit ShowUserFile();
		operatorFile->setVisible(false);
		QMessageBox::information(personal, QStringLiteral("删除成功"), QStringLiteral("删除成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(personal, QStringLiteral("删除失败"), QStringLiteral("删除失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::CloseFileOperatorEvent()
{
	qDebug() << "Call MainThread CloseFileOperatorEvent";
	if (operatorFile->property("doing").toBool())
	{
		QMessageBox::information(operatorFile, QStringLiteral("正在执行任务"), QStringLiteral("正在执行任务，请等待任务结束"), QMessageBox::Ok);
	}
	else
	{
		operatorFile->setVisible(false);
	}
}

void MainWindow::CloseMemberOperatorEvent()
{
	qDebug() << "Call MainThread CloseMemberOperatorEvent";
	operatorMember->setVisible(false);
}

void MainWindow::DownLoadProgressEvent(qint64 bytesSent, qint64 bytesTotal)
{
	downLoadFileBar->setMaximum(bytesTotal);
	downLoadFileBar->setValue(bytesSent);
}

void MainWindow::UpLoadUserProgressEvent(qint64 bytesSent, qint64 bytesTotal)
{
	upLoadFileBar->setMaximum(bytesTotal);
	upLoadFileBar->setValue(bytesSent);
}

void MainWindow::DownLoadAdminProgressProgressEvent(qint64 bytesSent, qint64 bytesTotal)
{
	downLoadFileAdminBar->setMaximum(bytesTotal);
	downLoadFileAdminBar->setValue(bytesSent);
}

void MainWindow::AppealUserClicked()
{
	if (Configuration::Status() == 0)
	{
		QMessageBox::information(personal, QStringLiteral("当前用户状态正常"), QStringLiteral("当前用户状态正常，不需要申诉"), QMessageBox::Ok);
	}
	else if (Configuration::Status() == 1)
	{
		QMessageBox::information(personal, QStringLiteral("当前用户正在申诉中"), QStringLiteral("当前用户正在申诉中，请等待管理员审核"), QMessageBox::Ok);
	}
	else
	{
		appealUserButton->setEnabled(false);
		emit AppealUser();
	}
}

void MainWindow::UpdatePersonal()
{
	lab_a_u->setText(Configuration::Username());
	lab_a_s->setText(Status(Configuration::Status()));
	lab_a_p->setText(Power(Configuration::Power()));
	lab_a_o->setText(Configuration::OrganizationName());
}

void MainWindow::OperatorOrganizationMembers()
{
	QPushButton* button = (QPushButton*)sender();
	int userid = button->property("userid").toInt();
	QString username = button->property("username").toString();
	int power = button->property("power").toInt();

	operatorMember->setWindowTitle(username);
	nowPoweLab->setText(Power(power));

	if (Configuration::Power() < 4)
	{
		upPowerButton->setEnabled(false);
		lowPowerButton->setEnabled(false);
	}
	connect(kickOutButton, &QPushButton::clicked, this, [userid, this]()
		{
			emit LeaveOrganization(userid);
		});
	connect(upPowerButton, &QPushButton::clicked, this, [userid, this]()
		{
			if (userid == Configuration::UserId())
			{
				QMessageBox::information(operatorMember, QStringLiteral("不能对自己操作权限"), QStringLiteral("不能对自己操作权限"), QMessageBox::Ok);
				return;
			}
			emit UpOrganizationMemberPower(userid);
		});
	connect(lowPowerButton, &QPushButton::clicked, this, [userid, this]()
		{
			if (userid == Configuration::UserId())
			{
				QMessageBox::information(operatorMember, QStringLiteral("不能对自己操作权限"), QStringLiteral("不能对自己操作权限"), QMessageBox::Ok);
				return;
			}
			emit LowOrganizationMemberPower(userid);
		});
	operatorMember->setVisible(true);
}

void MainWindow::CreateOrganization()
{
	QString str = organizationLine->text();
	if (str.isEmpty())
		QMessageBox::information(operatorFile, QStringLiteral("组织名不能为空"), QStringLiteral("组织名不能为空，请重试"), QMessageBox::Ok);
	emit CreateOrganization(str);
}

void MainWindow::UpdateOrganization()
{
	if (Configuration::OrganizationId() == 0)
	{
		lab_o_i->setVisible(true);
		lab_o_n->setVisible(false);
		lab_o_n->setText("");
		lab_o_s->setText("");
		lab_o_p->setText("");
	}
	else
	{
		lab_o_i->setVisible(false);
		lab_o_n->setVisible(true);
		lab_o_n->setText(QStringLiteral("欢迎回到 ") % Configuration::OrganizationName());
		lab_o_s->setText(Status(Configuration::OrganizationStatus()));
		lab_o_p->setText(Power(Configuration::Power()));
	}
}

void MainWindow::UpOrganizationMemberPowerEvent(bool res)
{
	qDebug() << "Call MainThread UpOrganizationMemberPowerEvent";
	if (res)
	{
		emit GetOrganizationMembers();
		QMessageBox::information(operatorFile, QStringLiteral("提升权限成功"), QStringLiteral("提升权限成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorFile, QStringLiteral("提升权限失败"), QStringLiteral("提升权限失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::LowOrganizationMemberPowerEvent(bool res)
{
	qDebug() << "Call MainThread LowOrganizationMemberPowerEvent";
	if (res)
	{
		emit GetOrganizationMembers();
		QMessageBox::information(operatorFile, QStringLiteral("降低权限成功"), QStringLiteral("降低权限成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorFile, QStringLiteral("降低权限失败"), QStringLiteral("降低权限失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::CloseUpLoadEvent()
{
	qDebug() << "Call MainThread CloseUpLoadEvent";
	if (upLoad->property("doing").toBool())
	{
		QMessageBox::information(upLoad, QStringLiteral("正在执行任务"), QStringLiteral("正在执行任务，请等待任务结束"), QMessageBox::Ok);
	}
	else
	{
		upLoad->setVisible(false);
	}
}

void MainWindow::ApplyJoinOrganization()
{
	qDebug() << "Call MainThread ApplyJoinOrganization";
	QString str = joinOrganizationLine->text();
	if (str.isEmpty())
		QMessageBox::information(operatorFile, QStringLiteral("组织号不能为空"), QStringLiteral("组织号不能为空，请重试"), QMessageBox::Ok);
	emit ApplyJoinOrganization(str.toInt());
}

void MainWindow::LeaveOrganization()
{
	qDebug() << "Call MainThread LeaveOrganization";
	auto res = QMessageBox::information(operatorFile, QStringLiteral("是否离开组织"), QStringLiteral("是否离开组织，组织所有者离开将会解散组织"), QMessageBox::Yes | QMessageBox::No);
	switch (res)
	{
	case QMessageBox::Yes:
		if (Configuration::Power() == 4)
			emit DissolveOrganization(Configuration::OrganizationId());
		else
			emit LeaveOrganization(Configuration::UserId());
		break;
	default:
		break;
	}
}

void MainWindow::DissolveOrganization()
{
	qDebug() << "Call MainThread DissolveOrganization";
	auto res = QMessageBox::information(operatorFile, QStringLiteral("是否解散组织"), QStringLiteral("是否解散组织"), QMessageBox::Yes | QMessageBox::No);
	switch (res)
	{
	case QMessageBox::Yes:
		emit DissolveOrganization(Configuration::OrganizationId());
		break;
	default:
		break;
	}
}

void MainWindow::CreateOrgizationEvent(bool res)
{
	qDebug() << "Call MainThread CreateOrgizationButtonEvent";
	if (res)
	{
		emit GetUserInfo();
		QMessageBox::information(personal, QStringLiteral("创建组织成功"), QStringLiteral("创建组织成功"), QMessageBox::Ok);
		UpdateOrganization();
	}
	else
	{
		QMessageBox::information(personal, QStringLiteral("创建组织失败"), QStringLiteral("创建组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::ApplyJoinOrganizationEvent(bool res)
{
	qDebug() << "Call MainThread ApplyJoinOrganizationEvent";
	if (res)
	{
		emit GetUserInfo();
		QMessageBox::information(personal, QStringLiteral("申请加入组织成功"), QStringLiteral("申请加入组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(personal, QStringLiteral("申请加入组织失败"), QStringLiteral("申请加入组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::DissolveOrganizationEvnet(bool res)
{
	qDebug() << "Call MainThread DissolveOrganizationEvnet";
	if (res)
	{
		emit GetUserInfo();
		QMessageBox::information(personal, QStringLiteral("解散组织成功"), QStringLiteral("解散组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(personal, QStringLiteral("解散组织失败"), QStringLiteral("解散组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::ShowAppealOrganizationEvent(QJsonArray obj)
{
	qDebug() << "Call MainThread ShowAppealOrganizationEvent";
	organizationAppealModel->clear();
	for (auto i = 0; i < obj.size(); ++i)
	{
		QStringList it;
		auto ob = obj.at(i).toObject();
		it << ob.value("username").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		organizationAppealModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userid", ob.value("userid").toInt());
		operatorButton->setProperty("username", ob.value("username").toString());
		if (Configuration::Power() < 3)
			operatorButton->setEnabled(false);
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(OperatorAppealMembers()));
		organizationAppealView->setIndexWidget(organizationAppealModel->index(i, 2), operatorButton);
	}
}

void MainWindow::JoinOrganizationEvent(bool res)
{
	qDebug() << "Call MainThread JoinOrganizationEvent";
	if (res)
	{
		emit ShowAppealOrganization();
		emit GetOrganizationMembers();
		QMessageBox::information(operatorAppealMember, QStringLiteral("同意加入组织成功"), QStringLiteral("同意加入组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAppealMember, QStringLiteral("同意加入组织失败"), QStringLiteral("同意加入组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::RefuseOrganizationEvent(bool res)
{
	qDebug() << "Call MainThread RefuseOrganizationEvent";
	if (res)
	{
		emit ShowAppealOrganization();
		QMessageBox::information(operatorAppealMember, QStringLiteral("拒绝加入组织成功"), QStringLiteral("拒绝加入组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAppealMember, QStringLiteral("拒绝加入组织失败"), QStringLiteral("拒绝加入组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::CloseAppealMemberOperatorEvent()
{
	qDebug() << "Call MainThread CloseMemberOperatorEvent";
	operatorAppealMember->setVisible(false);
}

void MainWindow::CloseFileOperatorAdminEvent()
{
	qDebug() << "Call MainThread CloseFileOperatorAdminEvent";
	if (operatorAdminFile->property("doing").toBool())
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("正在执行任务"), QStringLiteral("正在执行任务，请等待任务结束"), QMessageBox::Ok);
	}
	else
	{
		operatorAdminFile->setVisible(false);
	}
}

void MainWindow::CloseUserOperatorAdminEvent()
{
	qDebug() << "Call MainThread CloseUserOperatorAdminEvent";
	operatorAdminUser->setVisible(false);
}

void MainWindow::CloseOrganizationOperatorAdminEvent()
{
	qDebug() << "Call MainThread CloseUserOperatorAdminEvent";
	operatorAdminOrganization->setVisible(false);
}

void MainWindow::OperatorAppealMembers()
{
	qDebug() << "Call MainThread JoinOrganization";
	QPushButton* button = (QPushButton*)sender();
	int userid = button->property("userid").toInt();
	QString username = button->property("username").toString();

	operatorAppealMember->setWindowTitle(username);

	disconnect(appealJoinButton, 0, 0, 0);
	disconnect(refuseJoinButton, 0, 0, 0);
	connect(appealJoinButton, &QPushButton::clicked, this, [userid, this]()
		{
			emit JoinOrganization(userid);
		});
	connect(refuseJoinButton, &QPushButton::clicked, this, [userid, this]()
		{
			emit RefuseOrganization(userid);
		});

	operatorAppealMember->setVisible(true);
}

void MainWindow::ClearModelExcept(int index, int tab)
{
	if (index == 0)
	{
		userFileModel->clear();
		organizationFileModel->clear();
		organizationMemberModel->clear();
		organizationAppealModel->clear();
		fileAdminModel->clear();
		userAdminModel->clear();
		organizationAdminModel->clear();
	}
	else if (index == 1)
	{
		organizationFileModel->clear();
		organizationMemberModel->clear();
		organizationAppealModel->clear();
		fileAdminModel->clear();
		userAdminModel->clear();
		organizationAdminModel->clear();
	}
	else if (index == 2)
	{
		if (tab == 1)
		{
			userFileModel->clear();
			organizationMemberModel->clear();
			organizationAppealModel->clear();
			fileAdminModel->clear();
			userAdminModel->clear();
			organizationAdminModel->clear();
		}
		else if (tab == 2)
		{
			userFileModel->clear();
			organizationFileModel->clear();
			organizationAppealModel->clear();
			fileAdminModel->clear();
			userAdminModel->clear();
			organizationAdminModel->clear();
		}
		else if (tab == 3)
		{
			userFileModel->clear();
			organizationFileModel->clear();
			organizationMemberModel->clear();
			fileAdminModel->clear();
			userAdminModel->clear();
			organizationAdminModel->clear();
		}
	}
	else if (index == 3)
	{
		if (tab == 1)
		{
			userFileModel->clear();
			organizationFileModel->clear();
			organizationMemberModel->clear();
			organizationAppealModel->clear();
			userAdminModel->clear();
			organizationAdminModel->clear();
		}
		else if (tab == 2)
		{
			userFileModel->clear();
			organizationFileModel->clear();
			organizationMemberModel->clear();
			organizationAppealModel->clear();
			fileAdminModel->clear();
			organizationAdminModel->clear();
		}
		else if (tab == 3)
		{
			userFileModel->clear();
			organizationFileModel->clear();
			organizationMemberModel->clear();
			organizationAppealModel->clear();
			fileAdminModel->clear();
			userAdminModel->clear();
		}
	}
}

void MainWindow::ShowFileEvent(QJsonObject obj)
{
	qDebug() << "Call MainThread ShowFileEvent";
	fileAdminModel->clear();
	auto userFile = obj.value("user").toArray();
	auto organizationFile = obj.value("organization").toArray();
	for (auto i = 0; i < userFile.size(); ++i)
	{
		QStringList it;
		auto ob = userFile.at(i).toObject();
		it << ob.value("filename").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		fileAdminModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userfile", 1);
		operatorButton->setProperty("name", ob.value("username").toString());
		operatorButton->setProperty("fileid", ob.value("fileid").toInt());
		operatorButton->setProperty("filename", ob.value("filename").toString());
		operatorButton->setProperty("status", ob.value("status").toInt());
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(AdminOperatorFile()));
		fileAdminView->setIndexWidget(fileAdminModel->index(i, 2), operatorButton);
	}
	QStringList it;
	it << QStringLiteral("以上为用户文件————————————————————————————") << QStringLiteral("——————————————") << QStringLiteral("以下为组织文件");
	fileAdminModel->addData(it);
	for (auto i = 0; i < organizationFile.size(); ++i)
	{
		QStringList it;
		auto ob = organizationFile.at(i).toObject();
		it << ob.value("filename").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		fileAdminModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userfile", 0);
		operatorButton->setProperty("name", ob.value("organizationname").toString());
		operatorButton->setProperty("fileid", ob.value("fileid").toInt());
		operatorButton->setProperty("filename", ob.value("filename").toString());
		operatorButton->setProperty("status", ob.value("status").toInt());
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(AdminOperatorFile()));
		fileAdminView->setIndexWidget(fileAdminModel->index(userFile.size() + i + 1, 2), operatorButton);
	}
}

void MainWindow::ShowUserEvent(QJsonArray obj)
{
	qDebug() << "Call MainThread ShowUserEvent";
	userAdminModel->clear();
	for (auto i = 0; i < obj.size(); ++i)
	{
		QStringList it;
		auto ob = obj.at(i).toObject();
		it << ob.value("username").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		userAdminModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("userid", ob.value("userid").toInt());
		operatorButton->setProperty("username", ob.value("username").toString());
		operatorButton->setProperty("status", ob.value("status").toInt());
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(AdminOperatorUser()));
		userAdminView->setIndexWidget(userAdminModel->index(i, 2), operatorButton);
	}
}

void MainWindow::ShowOrganizationEvent(QJsonArray obj)
{
	qDebug() << "Call MainThread ShowOrganizationEvent";
	organizationAdminModel->clear();
	for (auto i = 0; i < obj.size(); ++i)
	{
		QStringList it;
		auto ob = obj.at(i).toObject();
		it << ob.value("organizationname").toString()
			<< Status(ob.value("status").toInt())
			<< QString();
		organizationAdminModel->addData(it);
		QPushButton* operatorButton = new QPushButton(QStringLiteral("操作"));
		operatorButton->setProperty("organizationid", ob.value("organizationid").toInt());
		operatorButton->setProperty("organizationname", ob.value("organizationname").toString());
		operatorButton->setProperty("status", ob.value("status").toInt());
		connect(operatorButton, SIGNAL(clicked()), this, SLOT(AdminOperatorOrganization()));
		organizationAdminView->setIndexWidget(organizationAdminModel->index(i, 2), operatorButton);
	}
}

void MainWindow::AdminOperatorFile()
{
	qDebug() << "Call MainThread AdminOperatorFile";
	QPushButton* button = (QPushButton*)sender();
	int fileid = button->property("fileid").toInt();
	QString filename = button->property("filename").toString();
	int status = button->property("status").toInt();

	operatorAdminFile->setWindowTitle(filename);
	belongToLab->setText(button->property("name").toString());
	downLoadFileAdminButton->setEnabled(true);
	downLoadFileAdminBar->setValue(0);

	disconnect(downLoadFileAdminButton, 0, 0, 0);
	disconnect(banFileAdminButton, 0, 0, 0);
	disconnect(resetFileAdminButton, 0, 0, 0);
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(DownLoadProgressEvent(qint64, qint64))));
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(UpLoadUserProgressEvent(qint64, qint64))));
	disconnect(com, SIGNAL(LoadProgressRes(qint64, qint64), this, SLOT(DownLoadAdminProgressProgressEvent(qint64, qint64))));
	connect(com, SIGNAL(LoadProgressRes(qint64, qint64)), this, SLOT(DownLoadAdminProgressProgressEvent(qint64, qint64)));
	connect(downLoadFileAdminButton, &QPushButton::clicked, this, [fileid, this]()
		{
			operatorAdminFile->setProperty("doing", true);
			downLoadFileAdminButton->setEnabled(false);
			emit DownLoadFile(fileid);
		});
	connect(banFileAdminButton, &QPushButton::clicked, this, [fileid, status, this]()
		{
			if (status != 0)
			{
				QMessageBox::information(operatorAdminFile, QStringLiteral("文件无法封禁"), QStringLiteral("文件无法封禁，无法对非正常文件进行封禁"), QMessageBox::Ok);
				return;
			}
			emit BanFile(fileid);
		});
	connect(resetFileAdminButton, &QPushButton::clicked, this, [fileid, status, this]()
		{
			if (status == 0)
			{
				QMessageBox::information(operatorAdminFile, QStringLiteral("文件无法解封"), QStringLiteral("文件无法解封，无法对正常文件进行解封"), QMessageBox::Ok);
				return;
			}
			emit ResetFile(fileid);
		});

	operatorAdminFile->setVisible(true);
}

void MainWindow::AdminOperatorUser()
{
	qDebug() << "Call MainThread AdminOperatorFile";
	QPushButton* button = (QPushButton*)sender();
	int userid = button->property("userid").toInt();
	QString username = button->property("username").toString();
	int status = button->property("status").toInt();

	operatorAdminUser->setWindowTitle(username);

	disconnect(banUserAdminButton, 0, 0, 0);
	disconnect(resetUserAdminButton, 0, 0, 0);
	connect(banUserAdminButton, &QPushButton::clicked, this, [userid, status, this]()
		{
			if (status != 0)
			{
				QMessageBox::information(operatorAdminUser, QStringLiteral("用户无法封禁"), QStringLiteral("用户无法封禁，无法对非正常用户进行封禁"), QMessageBox::Ok);
				return;
			}
			emit BanUser(userid);
		});
	connect(resetUserAdminButton, &QPushButton::clicked, this, [userid, status, this]()
		{
			if (status == 0)
			{
				QMessageBox::information(operatorAdminUser, QStringLiteral("用户无法解封"), QStringLiteral("用户无法解封，无法对正常用户进行解封"), QMessageBox::Ok);
				return;
			}
			emit ResetUser(userid);
		});

	operatorAdminUser->setVisible(true);
}

void MainWindow::AdminOperatorOrganization()
{
	qDebug() << "Call MainThread AdminOperatorOrganization";
	QPushButton* button = (QPushButton*)sender();
	int organizationid = button->property("organizationid").toInt();
	QString organizationname = button->property("organizationname").toString();
	int status = button->property("status").toInt();

	operatorAdminOrganization->setWindowTitle(organizationname);

	disconnect(banOrganizationAdminButton, 0, 0, 0);
	disconnect(resetOrganizationAdminButton, 0, 0, 0);
	connect(banOrganizationAdminButton, &QPushButton::clicked, this, [organizationid, status, this]()
		{
			if (status != 0)
			{
				QMessageBox::information(operatorAdminOrganization, QStringLiteral("组织无法封禁"), QStringLiteral("组织无法封禁，无法对非正常组织进行封禁"), QMessageBox::Ok);
				return;
			}
			emit BanOrganization(organizationid);
		});
	connect(resetOrganizationAdminButton, &QPushButton::clicked, this, [organizationid, status, this]()
		{
			if (status == 0)
			{
				QMessageBox::information(operatorAdminOrganization, QStringLiteral("组织无法解封"), QStringLiteral("组织无法解封，无法对正常组织进行解封"), QMessageBox::Ok);
				return;
			}
			emit ResetOrganization(organizationid);
		});

	operatorAdminOrganization->setVisible(true);
}

void MainWindow::BanFileEvent(bool res)
{
	qDebug() << "Call MainThread BanFileEvent";
	if (res)
	{
		emit ShowFile();
		QMessageBox::information(operatorAdminFile, QStringLiteral("封禁文件成功"), QStringLiteral("封禁文件成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("封禁文件失败"), QStringLiteral("封禁文件失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::ResetFileEvent(bool res)
{
	qDebug() << "Call MainThread ResetFileEvent";
	if (res)
	{
		emit ShowFile();
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封文件成功"), QStringLiteral("解封文件成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封文件失败"), QStringLiteral("解封文件失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::BanUserEvent(bool res)
{
	qDebug() << "Call MainThread BanUserEvent";
	if (res)
	{
		emit ShowUser();
		QMessageBox::information(operatorAdminFile, QStringLiteral("封禁用户成功"), QStringLiteral("封禁用户成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("封禁用户失败"), QStringLiteral("封禁用户失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::ResetUserEvent(bool res)
{
	qDebug() << "Call MainThread ResetUserEvent";
	if (res)
	{
		emit ShowUser();
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封用户成功"), QStringLiteral("解封用户成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封用户失败"), QStringLiteral("解封用户失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::BanOrganizationEvent(bool res)
{
	qDebug() << "Call MainThread BanOrganizationEvent";
	if (res)
	{
		emit ShowOrganization();
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封组织成功"), QStringLiteral("解封组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封组织失败"), QStringLiteral("解封组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::ResetOrganizationEvent(bool res)
{
	qDebug() << "Call MainThread BanOrganizationEvent";
	if (res)
	{
		emit ShowOrganization();
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封组织成功"), QStringLiteral("解封组织成功"), QMessageBox::Ok);
	}
	else
	{
		QMessageBox::information(operatorAdminFile, QStringLiteral("解封组织失败"), QStringLiteral("解封组织失败，请检查网络后重试"), QMessageBox::Ok);
	}
}

void MainWindow::SetListenPort()
{
	if (serverPortButton->text().compare(QStringLiteral("监听")) == 0)
	{
		serverPortButton->setEnabled(false);
		serverPortEdit->setEnabled(false);
		AddRowInServerModel(QStringLiteral("正在设置监听端口%1").arg(serverPortEdit->text().toUInt()));
		serverPortButton->setText(QStringLiteral("正在设置"));
		server->SetListenPort(serverPortEdit->text().toUInt());
		emit ServerInit();
	}
	else
	{
		serverPortButton->setEnabled(false);
		serverPortEdit->setEnabled(false);
		AddRowInServerModel(QStringLiteral("正在取消监听端口%1").arg(serverPortEdit->text().toUInt()));
		serverPortButton->setText(QStringLiteral("正在取消"));
		emit ServerClose();
	}
}

void MainWindow::AddRowInServerModel(QString str)
{
	serverModel->insertRow(serverModel->rowCount());
	auto index = serverModel->index(serverModel->rowCount() - 1, 0);
	serverModel->setData(index, str, Qt::DisplayRole);
}

void MainWindow::UpdateConnectNum()
{
	connectCountLab->setText(QString::number(server->NowConnectNum()));
}

void MainWindow::InitServerEvent(bool res)
{
	if (!res)
	{
		QMessageBox::information(this, "Init Server Error", QStringLiteral("初始化失败，请换个端口或者重试"), QMessageBox::Yes);
		serverPortButton->setText(QStringLiteral("监听"));
		serverPortButton->setEnabled(true);
		serverPortEdit->setEnabled(true);
		AddRowInServerModel(QStringLiteral("设置失败"));
	}
	else
	{
		serverPortButton->setText(QStringLiteral("取消监听"));
		serverPortButton->setEnabled(true);
		AddRowInServerModel(QStringLiteral("设置成功"));
	}
}

void MainWindow::CloseServerEvent(bool)
{
	serverPortButton->setText(QStringLiteral("监听"));
	serverPortButton->setEnabled(true);
	serverPortEdit->setEnabled(true);
	AddRowInServerModel(QStringLiteral("取消成功"));
}

void MainWindow::SetClientHostAndPort()
{
	if (clientButton->text().compare(QStringLiteral("断开连接")))
	{
		if (clientAddressEdit->text().compare("127.0.0.1"))
		{
			client->SetAddress(clientAddressEdit->text());
		}
		if (clientPortEdit->text().compare("929"))
		{
			client->SetListenPort(clientPortEdit->text().toInt());
		}
		clientButton->setEnabled(false);
		clientAddressEdit->setEnabled(false);
		clientPortEdit->setEnabled(false);
		AddRowInClientModel(QStringLiteral("正在连接%1:%2").arg(clientAddressEdit->text()).arg(clientPortEdit->text()));
		clientButton->setText(QStringLiteral("正在连接"));
		emit ClientInit();
	}
	else
	{
		clientButton->setEnabled(true);
		clientAddressEdit->setEnabled(true);
		clientPortEdit->setEnabled(true);
		clientButton->setText(QStringLiteral("连接"));
		AddRowInClientModel(QStringLiteral("关闭连接"));
		emit ClientClose();
	}
}

void MainWindow::AddRowInClientModel(QString str)
{
	clientModel->insertRow(clientModel->rowCount());
	auto index = clientModel->index(clientModel->rowCount() - 1, 0);
	clientModel->setData(index, str, Qt::DisplayRole);
}

void MainWindow::SendOutMessage()
{
	emit SendMessageToServer(clientInputEdit->toPlainText());
	clientInputEdit->clear();
}

void MainWindow::BeginConversation()
{
	qDebug() << "Call MainThread BeginConversation";
	LOG(INFO) << QStringLiteral("连接成功");
	AddRowInClientModel(QStringLiteral("连接成功"));
	clientButton->setEnabled(true);
	sendMessageButton->setEnabled(true);
	clientButton->setText(QStringLiteral("断开连接"));
}