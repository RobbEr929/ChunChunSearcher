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
	InitCommunicate();
	InitQuit();
	InitConnect();
	Show();
}

void MainWindow::Start()
{
	qDebug() << "Call Start";
	emit Begin();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	qDebug() << "Call closeEvent";
	if (Configuration::RunInBackground())
	{
		hide();
		event->ignore();
	}
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	qDebug() << "Call resizeEvent";
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
	qDebug() << "Call InitWindow";
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
	autoUpdate = new QTimer;
}

void MainWindow::InitTray()
{
	qDebug() << "Call InitTray";
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
	qDebug() << "Call InitMenu";
	menu1 = menuBar()->addMenu(QStringLiteral("系统"));
	menu2 = menuBar()->addMenu(QStringLiteral("视图"));
	menu3 = menuBar()->addMenu(QStringLiteral("搜索"));
	menu4 = menuBar()->addMenu(QStringLiteral("个性化"));
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
	action4_2 = new QAction(QStringLiteral("登出"));
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
	qDebug() << "Call InitButton";
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
	qDebug() << "Call InitInput";
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
	qDebug() << "Call InitFilter";
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
	qDebug() << "Call InitBottomInfo";
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
	qDebug() << "Call InitMonitor";
	monitor = new Monitor;
	monitorThread = new QThread;

	for (auto i : Configuration::MonitorPath())
		monitor->AddPath(i);
	monitor->moveToThread(monitorThread);

	monitorThread->start();
}

void MainWindow::InitData()
{
	qDebug() << "Call InitData";
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
	qDebug() << "Call InitView";
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
	tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
	qDebug() << "Call InitViewRightMenu";
	rightMenu = new QMenu;
	actionr_1 = rightMenu->addAction(QStringLiteral("打开"));
	actionr_2 = rightMenu->addAction(QStringLiteral("打开路径"));
	actionr_3 = rightMenu->addAction(QStringLiteral("复制全路径"));
	actionr_4 = rightMenu->addAction(QStringLiteral("复制路径"));
	rightMenu->addSeparator();
	actionr_5 = rightMenu->addAction(QStringLiteral("删除"));
	rightMenu->addSeparator();
	actionr_6 = rightMenu->addAction(QStringLiteral("属性"));

	rightMenu->setVisible(false);
}

void MainWindow::InitOption()
{
	qDebug() << "Call InitOption";
	option = new QWidget;
	option->resize(QApplication::desktop()->width() * 0.15, QApplication::desktop()->height() * 0.5);
	option->setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
	option->setWindowTitle(QStringLiteral("设置ChunChunSearcher"));
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

	//view
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
	qDebug() << "Call InitAbout";
	about = new QWidget(this);
	about->resize(QApplication::desktop()->width() * 0.2, QApplication::desktop()->height() * 0.2);
	about->setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
	about->setWindowTitle(QStringLiteral("关于ChunChunSearcher"));
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
	sign->setWindowFlags(Qt::CustomizeWindowHint);
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
	nameLine->setText(Configuration::Username());
	passLine->move(sign->width() * 0.2 + 40, sign->height() * 0.35);
	passLine->setEchoMode(QLineEdit::Password);
	passLine->setText(Configuration::Password());
	button_autosign->setText(QStringLiteral("自动登录"));
	button_autosign->resize(120, 30);
	button_autosign->move(sign->width() * 0.1, sign->height() * 0.5);
	button_s->setText(QStringLiteral("登录"));
	button_s->resize(50, 30);
	button_s->move(sign->width() * 0.1, sign->height() * 0.7);
	button_r->setText(QStringLiteral("注册"));
	button_r->resize(50, 30);
	button_r->move(sign->width() * 0.3, sign->height() * 0.7);
	button_skip->setText(QStringLiteral("游客进入"));
	button_skip->resize(100, 30);
	button_skip->move(sign->width() * 0.5, sign->height() * 0.7);
}

void MainWindow::InitCommunicate()
{
	com = new Communicate;
	comThread = new QThread;
	com->moveToThread(comThread);
	comThread->start();
}

void MainWindow::InitQuit()
{
	quit = new QWidget;
	quit->resize(300, 200);
	lab_q = new QLabel(quit);
	lab_q->setFont(QFont("Microsoft YaHei", 12, 75));
	lab_q->resize(this->width(), 50);
	lab_q->move(quit->width() * 0.2, quit->height() * 0.2);
	infoQuit = new Info(lab_q);
	quitInfoThread = new QThread;
	infoQuit->moveToThread(quitInfoThread);
	quit->setVisible(false);
}

void MainWindow::InitConnect()
{
	qDebug() << "Call InitConnect";
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
	connect(action4_2, SIGNAL(triggered()), this, SLOT(SignOut()));
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

	//View
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

	//Communicate
	if (Configuration::OnlineEnable())
	{
		connect(this, SIGNAL(Begin()), com, SLOT(AbleToOnline()));
		connect(this, SIGNAL(RetryToOnline()), com, SLOT(AbleToOnline()));
		connect(com, SIGNAL(Online(bool)), this, SLOT(OnlineEvent(bool)));
		connect(this, SIGNAL(Sign()), com, SLOT(Sign()));
		connect(com, SIGNAL(SignRes(bool)), this, SLOT(SignEvent(bool)));
		connect(this, SIGNAL(Register()), com, SLOT(Register()));
		connect(com, SIGNAL(RegisterRes(bool)), this, SLOT(RegisterEvent(bool)));
		connect(this, SIGNAL(GetConf()), com, SLOT(GetConf()));
		connect(com, SIGNAL(GetConfRes(bool)), this, SLOT(GetConfEvent(bool)));
		connect(this, SIGNAL(GetConf()), this, SLOT(UpdateMenu()));
		connect(this, SIGNAL(WriteConf()), com, SLOT(WriteConf()));
		connect(com, SIGNAL(WriteConfRes(bool)), this, SLOT(WriteEvent(bool)));
	}

	//Quit
	connect(this, SIGNAL(EmitInfo(QString)), infoQuit, SLOT(ShowInfo(QString)));
}

void MainWindow::Show()
{
	this->setVisible(true);
	sign->setVisible(!Configuration::AutoSign() && Configuration::OnlineEnable());
}

void MainWindow::InitVolume()
{
	qDebug() << "Call InitVolume";
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
	qDebug() << "Call AfterInit";
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
	qDebug() << "Call AfterFind";
	++nowTimes;
	for (auto i : volume)
	{
		if (i->VolumeName() == vol)
		{
			ModelItem it;
			rightFileNumber += i->RightFileNumber();
			for (auto j : i->RightFile())
			{
				it.name = j.first;
				it.path = j.second;
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
	qDebug() << "Call ButtonEvent";
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
	qDebug() << "Call QuitEvent";
	quitInfoThread->start();
	quit->setVisible(true);
	trayIcon->setVisible(false);
	if (!Configuration::IsSigned())
	{
		emit EmitInfo(QStringLiteral("正在保存本地设置..."));
		WriteSetting();
		qApp->quit();
	}
	else
	{
		emit EmitInfo(QStringLiteral("正在保存本地设置..."));
		WriteSetting();
		emit EmitInfo(QStringLiteral("正在保存设置到云端..."));
		emit WriteConf();
	}
}

void MainWindow::WriteSetting()
{
	qDebug() << "Call WriteSetting";
	Configuration::BeforeQuit();
}

void MainWindow::FilterTriggered()
{
	qDebug() << "Call FilterTriggered";
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
	qDebug() << "Call InfoTriggered";
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
	qDebug() << "Call FilterEvent";
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
	qDebug() << "Call TrayEvent";
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
	qDebug() << "Call AboutTriggered";
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
	qDebug() << "Call OptionTriggered";
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
		QList<ModelItem> list_ntfs;
		QList<ModelItem> list_other;
		auto volVec = Configuration::VolumeFileSystem();
		for (auto i = volVec.begin(); i != volVec.end(); ++i)
		{
			ModelItem it;
			if (i.value() & VOLUME_IS_NTFS)
			{
				it.name = QString("%1:").arg(i.key());
				if (i.value() & VOLUME_USEING)
				{
					it.path = QStringLiteral("启用");
				}
				else
				{
					it.path = QStringLiteral("停用");
				}
				list_ntfs.push_back(it);
			}
			else if (i.value() & VOLUME_NOT_NTFS)
			{
				it.name = i.key() % ':';
				if (i.value() & VOLUME_USEING)
				{
					it.path = QStringLiteral("启用");
				}
				else
				{
					it.path = QStringLiteral("停用");
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
	qDebug() << "Call OptionToSubmit";
	option->setVisible(false);
	Configuration::SetRunInBackground(boxi_1->isChecked());
	Configuration::SetTrayShow(boxi_2->isChecked());
	Configuration::SetOneClickShow(boxi_3->isChecked());
	Configuration::SetSelectAll(boxi_4->isChecked());
	Configuration::SetOnlineEnable(!boxi_5->isChecked());
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
		char c = i.name[0].toLatin1();
		if (i.path.compare(QStringLiteral("启用")) == 0)
		{
			if (ntfsVec.find(c).value() & VOLUME_DISCARD)
			{
				__int8 attr = VOLUME_IS_NTFS | VOLUME_USEING;
				emit ReInit(c);
				Configuration::SetVolumeFileSystem(c, attr);
				++reInitTimes;
			}
		}
		else if (i.path.compare(QStringLiteral("停用")) == 0)
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
		char c = i.name[0].toLatin1();
		if (i.path.compare(QStringLiteral("启用")) == 0)
		{
			if (ntfsVec.find(c).value() & VOLUME_DISCARD)
			{
				__int8 attr = VOLUME_NOT_NTFS | VOLUME_USEING;
				emit ReInit(c);
				Configuration::SetVolumeFileSystem(c, attr);
				++reInitTimes;
			}
		}
		else if (i.path.compare(QStringLiteral("停用")) == 0)
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
	qDebug() << "Call OptionCancel";
	option->setVisible(false);
}

void MainWindow::SearchCaseSensitiveTriggered()
{
	qDebug() << "Call SearchCaseSensitiveTriggered" << !Configuration::SearchCaseSensitive();
	auto res = Configuration::SearchCaseSensitive();
	Configuration::SetSearchCaseSensitive(!res);
	action3_1->setChecked(Configuration::SearchCaseSensitive());
}

void MainWindow::SearchMatchPathTriggered()
{
	qDebug() << "Call SearchMatchPathTriggered" << !Configuration::SearchMatchPath();
	auto res = Configuration::SearchMatchPath();
	Configuration::SetSearchMatchPath(!res);
	action3_2->setChecked(Configuration::SearchMatchPath());
}

void MainWindow::SearchMatchFileTriggered()
{
	qDebug() << "Call SearchMatchFileTriggered" << !Configuration::SearchMatchFile();
	auto res = Configuration::SearchMatchFile();
	Configuration::SetSearchMatchFile(!res);
	action3_3->setChecked(Configuration::SearchMatchFile());
}

void MainWindow::SearcRegExTriggered()
{
	qDebug() << "Call SearcRegExTriggered" << !Configuration::SearcRegEx();
	auto res = Configuration::SearcRegEx();
	Configuration::SetSearcRegEx(!res);
	action3_4->setChecked(Configuration::SearcRegEx());
}

void MainWindow::RightClicked(const QPoint& pos)
{
	qDebug() << "Call RightClicked" << tableView->selectionModel()->currentIndex();
	rightMenu->exec(mapToGlobal(pos));
}

void MainWindow::OpenFile()
{
	auto index = tableView->currentIndex();
	qDebug() << "Call OpenFile" % viewModel->FullPath(index);
	QFileInfo fileInfo(viewModel->FullPath(index));
	if (fileInfo.exists())
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
	}
}

void MainWindow::OpenPath()
{
	auto index = tableView->currentIndex();
	qDebug() << "Call OpenPath" % viewModel->Path(index);
	QFileInfo fileInfo(viewModel->Path(index));
	if (fileInfo.exists())
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
	}
}

void MainWindow::CopyFullPath()
{
	qDebug() << "Call CopyFullPath" % viewModel->FullPath(tableView->currentIndex());
	QApplication::clipboard()->setText(viewModel->FullPath(tableView->currentIndex()));
}

void MainWindow::CopyPath()
{
	qDebug() << "Call CopyPath";
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
	qDebug() << "Call Delete" % viewModel->FullPath(index);
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
	qDebug() << "Call Attribute" % viewModel->FullPath(index);
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

void MainWindow::VolumeNtfsStateChange()
{
	auto current = ntfsVolumeView->currentIndex();
	qDebug() << "Call VolumeNtfsStateChange" << current;
	if (!current.isValid())
	{
		QMessageBox::information(indexOptions[0], QStringLiteral("未选中!"), QStringLiteral("错误!\n未选择任何卷!"));
		return;
	}
	if (ntfsVolumeModel->isVaild(current))
	{
		auto it = ntfsVolumeModel->getRowData(current);
		if (it.path.compare(QStringLiteral("启用")) == 0)
		{
			it.path = QStringLiteral("停用");
		}
		else
		{
			it.path = QStringLiteral("启用");
		}
		ntfsVolumeModel->updateData(current, it);
	}
}

void MainWindow::VolumeOtherStateChange()
{
	auto current = ntfsVolumeView->currentIndex();
	qDebug() << "Call VolumeNtfsStateChange" << current;
	if (!current.isValid())
	{
		QMessageBox::information(indexOptions[0], QStringLiteral("未选中!"), QStringLiteral("错误!\n未选择任何卷!"));
		return;
	}
	if (otherVolumeModel->isVaild(current))
	{
		auto it = otherVolumeModel->getRowData(current);
		if (it.path.compare(QStringLiteral("启用")) == 0)
		{
			it.path = QStringLiteral("停用");
		}
		else
		{
			it.path = QStringLiteral("启用");
		}
		otherVolumeModel->updateData(current, it);
	}
}

void MainWindow::IgnorePathAdd()
{
	qDebug() << "Call IgnorePathAdd";
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
	qDebug() << "Call MonitorPathAdd";
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
	qDebug() << "Call OneClickShowTriggered";
	if (boxi_2->isChecked())
		boxi_3->setEnabled(true);
	else
		boxi_3->setEnabled(false);
}

void MainWindow::AutoUpdateTriggered()
{
	qDebug() << "Call AutoUpdateTriggered";
	if (boxs_5->isChecked())
		autoTimeBox->setEnabled(true);
	else
		autoTimeBox->setEnabled(false);
}

void MainWindow::Update()
{
	qDebug() << "Call Update";
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
	qDebug() << "Call SignWidgetTriggered";
	if (!sign->isVisible())
		sign->setVisible(true);
	else
		sign->raise();
}

void MainWindow::SignTriggered()
{
	qDebug() << "Call SignTriggered";
	Configuration::SetUsername(nameLine->text());
	Configuration::SetPassword(QCryptographicHash::hash(passLine->text().toLatin1(), QCryptographicHash::Md5).toHex());
	nameLine->setEnabled(false);
	passLine->setEnabled(false);
	button_s->setEnabled(false);
	button_r->setEnabled(false);
	button_skip->setEnabled(false);
	emit Sign();
}

void MainWindow::RegisterTriggered()
{
	qDebug() << "Call RegisterTriggered";
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
	qDebug() << "Call OnlineEvent";
	static int RetryTimes = 4;
	if (res)
	{
		if (Configuration::AutoSign() && !Configuration::Username().isEmpty() && !Configuration::Password().isEmpty())
		{
			emit Sign();
		}
	}
	else
	{
		if (RetryTimes == 0)
		{
			LOG(INFO) << QStringLiteral("无法连接到服务器");
			return;
		}
		if (Configuration::OnlineEnable())
		{
			--RetryTimes;
			LOG(INFO) << QStringLiteral("连接超时，重试中...");
			emit RetryToOnline();
		}
	}
}

void MainWindow::SignEvent(bool res)
{
	qDebug() << "Call SignEvent";
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
		emit GetConf();
		Configuration::SetAutoSign(button_autosign->isChecked());
	}
	else
	{
		qDebug() << "Sign Fail";
		if (!sign->isVisible())
			sign->raise();
		lab_s_f->setVisible(true);
		passLine->setText("");
		Configuration::SetUsername("");
		Configuration::SetPassword("");
	}
}

void MainWindow::RegisterEvent(bool res)
{
	qDebug() << "Call RegisterEvent";
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
	qDebug() << "Call GetConfEvent";
	static int RetryTimes = 4;
	if (res)
	{
		auto res = QMessageBox::information(this, QStringLiteral("获取到云端设置，是否覆盖？"), QStringLiteral("获取到云端设置，是否覆盖？"), QMessageBox::Yes | QMessageBox::No);
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
		qDebug() << "GetConf Fail";
		if (RetryTimes == 0)
		{
			LOG(INFO) << QStringLiteral("获取云端设置失败");
			return;
		}
		if (Configuration::IsSigned())
		{
			--RetryTimes;
			LOG(INFO) << QStringLiteral("获取失败，重试中...");
			emit GetConf();
		}
	}
}

void MainWindow::WriteEvent(bool res)
{
	qDebug() << "Call WriteEvent";
	static int retryTimes = 4;
	if (res)
	{
		qDebug() << "Write Success";
		emit EmitInfo(QStringLiteral("感谢使用，正在退出..."));
		qApp->quit();
	}
	else
	{
		--retryTimes;
		emit WriteConf();
		if (retryTimes == 0)
		{
			qDebug() << "Write Fail";
			LOG(INFO) << QStringLiteral("写入云端失败，请下次同步");
			emit EmitInfo(QStringLiteral("感谢使用，正在退出..."));
			qApp->quit();
		}
	}
}

void MainWindow::SkipTriggered()
{
	qDebug() << "Call SkipTriggered";
	sign->setVisible(false);
	Configuration::SetIsSigned(false);
	Configuration::SetUsername("");
	Configuration::SetPassword("");
	Configuration::SetAutoSign(false);
	this->raise();
}

void MainWindow::UpdateMenu()
{
	qDebug() << "Call UpdateMenu";
	if (Configuration::IsSigned())
	{
		menu4->removeAction(action4_1);
		menu4->addAction(action4_2);
	}
	else
	{
		menu4->removeAction(action4_2);
		menu4->addAction(action4_1);
	}
}

inline void SetValueToKey(QString str)
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
	qDebug() << "Call WriteToConf";
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
	qDebug() << "Call SignOut";
	Configuration::SetIsSigned(false);
	Configuration::SetUsername("");
	Configuration::SetPassword("");
	Configuration::SetAutoSign(false);
	UpdateMenu();
}