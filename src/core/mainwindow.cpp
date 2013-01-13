#include "mainwindow.h"



#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QPluginLoader>
#include <QPushButton>
#include <QApplication>

#include "plugininterface.h"

#include "translationwidget.h"
#include "dictionarywidget.h"
#include "config.h"
#include "translatorsconfig.h"
#include "testpage.h"
#include "defines.h"
#include "pluginsconfig.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mToolBar(new QToolBar(this)),
    mStatusBar(new QStatusBar(this)),
    mMenuBar(new QMenuBar(this)),
    mFancyWidget(new Core::Internal::FancyTabWidget(this)),

    // Menus
    mFileMenu(new QMenu(tr("File"), this)),
    mEditMenu(new QMenu(tr("Edit"), this)),
    mHelpMenu(new QMenu(tr("Help"), this)),

    //Actions
    mExitAction(new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), this)),
    mCopyAction(new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this)),
    mOptionsAction(new QAction("Options", this)),
    mAboutAction(new QAction(QIcon::fromTheme("help-about"), tr("About"), this)),
    mTranslationWidget(new TranslationWidget(this)),
    mDictionaryWidget(new DictionaryWidget(this)),
    mSettingsDialog(new Config(this))
{

    setWindowTitle(qApp->applicationName());


    mFileMenu->addAction(mExitAction);
    mEditMenu->addAction(mCopyAction);
    mEditMenu->addAction(mOptionsAction);
    mHelpMenu->addAction(mAboutAction);


    mMenuBar->addMenu(mFileMenu);
    mMenuBar->addMenu(mEditMenu);
    mMenuBar->addMenu(mHelpMenu);


    QList<QAction *> ActionsList;
    ActionsList << mExitAction << mCopyAction << mAboutAction;
    mToolBar->addActions(ActionsList);
//    mToolBar->setMovable(false);



    this->setCentralWidget(mFancyWidget);


    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);
    this->addToolBar(Qt::RightToolBarArea, mToolBar);


    this->addPage(mTranslationWidget);
    this->addPage(mDictionaryWidget);

    if(mFancyWidget->count() > 0)
        mFancyWidget->setCurrentIndex(0);


    mSettingsDialog->addPage(new TranslatorsConfig(this));
    mSettingsDialog->addPage(new TestPage(this));
    mSettingsDialog->addPage(new PluginsConfig(this));

    connect(mOptionsAction, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));
    connect(mExitAction, SIGNAL(triggered()), qApp, SLOT(quit()));


//    QPluginLoader loader("/tmp/qphoenix-build/src/plugins/trayicon/libtrayicon.so");
//    loader.load();
//    QObject *obj = loader.instance();

//    PluginInterface *iface = qobject_cast<PluginInterface *>(obj);


//    qDebug() << "Name iszzzzzz: ---- " <<iface->name();

//    iface->setMainWindowPTR(this);

}

MainWindow::~MainWindow()
{
}


void MainWindow::addPage(QWidget *page) {

    Info *i =
            qobject_cast<Info *>(page);


    if(i == NULL) {
        qDebug() << "Problem here!"; //TODO: fix it!
        return;
    }


    QIcon icon = i->icon();
    QString name = i->name();

    QGroupBox *gb = new QGroupBox(this);

    gb->setTitle(name);
    gb->setLayout(new QHBoxLayout);
    gb->layout()->addWidget(page);

    mFancyWidget->insertTab(mFancyWidget->count(), gb, icon, name);

    resize(800, 600);
}

void MainWindow::removePage(const QWidget *page) {

}

QWidget *MainWindow::pageAt(const int i) {

}

void MainWindow::setCurrentPage(const int i) {
    mFancyWidget->setCurrentIndex(i);

    qDebug() << "BLLLL";
}
