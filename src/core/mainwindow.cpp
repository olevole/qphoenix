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
#include <QMap>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QLineEdit>
#include <QClipboard>
#include <QThread>
#include <QFrame>
#include <QTabWidget>
#include <QToolButton>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>

#include "iplugin.h"
#include "querywrappers.h"
#include "translationwidget.h"
#include "dictionarywidget.h"
#include "config.h"
#include "translatorsconfig.h"
#include "defines.h"
#include "pluginsconfig.h"
#include "loader.h"
#include "itranslator.h"
#include "languageconfig.h"
#include "dictionaryconfig.h"



QString MainWindow::mAboutStr = "QPhoenix is an advanced translation tool that could use multiple dictionaries and translators\n"
#ifdef QP_DEBUG
        "REVISION: "
        QP_GIT_REV
        "\nVersion: "
        QP_APP_VERSION
#endif
;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mStatusBar(new QStatusBar(this)),
    mToolBar(new QToolBar(this)),
    mMenuBar(new QMenuBar(this)),
    mTabWidget(new QTabWidget(this)),

    // Menus
    mFileMenu(new QMenu(tr("File"), this)),
    mEditMenu(new QMenu(tr("Edit"), this)),
    mToolsMenu(new QMenu(tr("Tools"), this)),
    mHelpMenu(new QMenu(tr("Help"), this)),

    //Actions
    mActionExit(new QAction(QP_ICON("application-exit"), tr("Exit"), this)),
    mActionOpen(new QAction(QP_ICON("document-open"),tr("Open"), this)),
    mActionSave(new QAction(QP_ICON("document-save"),tr("Save"), this)),
    mActionSaveAs(new QAction(QP_ICON("document-save-as"),tr("Save As"), this)),
    mActionPrint(new QAction(QP_ICON("document-print"),tr("Print"), this)),

    mActionClear(new QAction(QP_ICON("edit-clear"), tr("Clear"), this)),
    mActionUndo(new QAction(QP_ICON("edit-undo"),tr("Undo"), this)),
    mActionRedo(new QAction(QP_ICON("edit-redo"),tr("Redo"), this)),
    mActionSwap(new QAction(tr("Swap"), this)),
    mActionOptions(new QAction(tr("Options"), this)),


    mActionAbout(new QAction(QIcon::fromTheme("help-about"), tr("About"), this)),
    mActionAboutQt(new QAction(tr("About Qt"), this)),

    mTranslationWidget(new TranslationWidget(this)),
    mDictionaryWidget(new DictionaryWidget(this)),
    mSettingsDialog(new Config(this)),

    mPluginsConfig(new PluginsConfig),
    mTranslatorsConfig(new TranslatorsConfig(this)),
    mLanguageConfig(new LanguageConfig(this)),
    mDictionaryConfig(new DictionaryConfig(this))
{
    setWindowTitle(qApp->applicationName());

    mFileMenu->addAction(mActionOpen);
    mFileMenu->addSeparator();
    mFileMenu->addAction(mActionSave);
    mFileMenu->addAction(mActionSaveAs);
    mFileMenu->addAction(mActionPrint);
    mFileMenu->addSeparator();
    mFileMenu->addAction(mActionExit);

    mEditMenu->addAction(mActionClear);
    mEditMenu->addSeparator();
    mEditMenu->addAction(mActionUndo);
    mEditMenu->addAction(mActionRedo);
    mEditMenu->addAction(mActionSwap);
    mEditMenu->addSeparator();
    mEditMenu->addAction(mActionOptions);

    mHelpMenu->addAction(mActionAbout);
    mHelpMenu->addAction(mActionAboutQt);

    mMenuBar->addMenu(mFileMenu);
    mMenuBar->addMenu(mEditMenu);
    mMenuBar->addMenu(mHelpMenu);

    mToolBar->addAction(mActionClear);
    mToolBar->addAction(mActionUndo);
    mToolBar->addAction(mActionRedo);
    mToolBar->setMovable(false);

    mTabWidget->setTabPosition(QTabWidget::West);

    this->setCentralWidget(mTabWidget);
    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);

    this->addToolBar(mToolBar);
    this->addToolBar(mDictionaryWidget->mainToolBar());
    this->addToolBar(mTranslationWidget->mainToolBar());

    this->addPage(mTranslationWidget);
    this->addPage(mDictionaryWidget);

    if(mTabWidget->count() > 1)
        mTabWidget->setCurrentIndex(0);

    // Configuring settings pages
    mSettingsDialog->addPage(mTranslatorsConfig);
    mSettingsDialog->addPage(mDictionaryConfig);
    mSettingsDialog->addPage(mLanguageConfig);
    mSettingsDialog->addPage(mPluginsConfig);

    connect(mActionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(mActionExit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(mActionClear, SIGNAL(triggered()), this, SLOT(clear()));
    connect(mActionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(mActionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(mActionSwap, SIGNAL(triggered()), this, SLOT(swap()));
    connect(mActionOptions, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));
    connect(mActionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(mActionAbout, SIGNAL(triggered()), this, SLOT(about()));



    // Widgets , Dialogs, etc
    connect(mSettingsDialog, SIGNAL(accepted()), this, SLOT(onConfigAccept()));
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(onIndexChange(int)));

    QComboBox *src = mTranslationWidget->translatorComboBox();
    QComboBox *dest = mTranslatorsConfig->translatorComboBox();

    connect(src, SIGNAL(currentIndexChanged(int)), dest, SLOT(setCurrentIndex(int)));
    connect(dest, SIGNAL(currentIndexChanged(int)), src, SLOT(setCurrentIndex(int)));

    QStringList items;
    for (int i = 0; i < dest->count(); ++i) {
        items << dest->itemText(i);
    }

    src->clear();
    src->addItems(items);

    readCfg();
    // Read configs
    onConfigAccept();
}

MainWindow::~MainWindow()
{
    saveCfg();
}

void MainWindow::addPage(QWidget *page) {
    Info *i = qobject_cast<Info *>(page);
    if(i == NULL) {
        //TODO: Error processing
        return;
    }
    QIcon icon = i->icon();
    QString name = i->name();

    mTabWidget->insertTab(mTabWidget->count(), page, icon, name);
}

void MainWindow::removePage(const QWidget *page) {

}

QWidget *MainWindow::pageAt(const int i) {
    return new QWidget();
}

void MainWindow::setCurrentIndex(const int i) {
    mTabWidget->setCurrentIndex(i);
    onIndexChange(i);
}

void MainWindow::onConfigAccept() {
    /*!
     * Plugins processing
     *
     */
    QObjectList *lst = mPluginsConfig->pluginsList();
    for(int i = 0; i < lst->count(); i++) {
        IPlugin *iface =  qobject_cast<IPlugin *>(lst->at(i));

        bool enabled = mPluginsConfig->isEnabled(i);
        if(enabled) {
            iface->setMainWindowPTR(this);
            iface->load();

        } else if(iface->isLoaded()) {
                iface->unload();
        }
    }

    /*!
     * Updating translators information...
     */

    QStringList enabledKeys = mLanguageConfig->keysForEnabled();

    mLanguageConfig->setNativeNames(false);
    mTranslationWidget->setNativeNames(false);
    mDictionaryWidget->setDictionaryList(mDictionaryConfig->dictionaries());
    mTranslationWidget->setEnabledKeys(mLanguageConfig->keysForEnabled());
    mTranslationWidget->setTranslator(mTranslatorsConfig->currentTranslator());
}

void MainWindow::onIndexChange(const int i) {
    mDictionaryWidget->mainToolBar()->setVisible(i == 1);
    mTranslationWidget->mainToolBar()->setVisible(i == 0);
}

void MainWindow::readCfg() {
    QSettings s;
    s.beginGroup("MainWindow");
    this->setCurrentIndex(s.value("tabIndex", 0).toInt());
    this->restoreGeometry(s.value("geometry").toByteArray());
    s.endGroup();
}

void MainWindow::saveCfg() {
    QSettings s;
    s.beginGroup("MainWindow");
    s.setValue("tabIndex", mTabWidget->currentIndex());
    s.setValue("geometry", saveGeometry());
    s.endGroup();
}


//----------------------------------------------------------------------------------------------
// Actions slots


void MainWindow::open() {
    const QString path = QFileDialog::getOpenFileName(this);
    QFile file(path);
    if(!file.open( QFile::ReadOnly))
        return;
    const QString text = file.readAll();
    this->translatorWidget()->srcText()->setText(text);
}

void MainWindow::exit() {
    saveCfg();
    qApp->quit();
}

void MainWindow::clear() {
    const int i = currentIndex();
    switch(i){
        case 0:
            translatorWidget()->srcText()->clear();
            translatorWidget()->resText()->clear();
        break;
        case 1:
            dictionaryWidget()->srcText()->clear();
            dictionaryWidget()->resText()->setHtml("<html><body></body></html>");
        break;
    }
}

void MainWindow::undo() {
    currentIndex() == 0 ? translatorWidget()->srcText()->undo()
                        : dictionaryWidget()->srcText()->undo();

}

void MainWindow::redo() {
    currentIndex() == 0 ? translatorWidget()->srcText()->redo()
                        : dictionaryWidget()->srcText()->redo();
}

void MainWindow::swap() {
    translatorWidget()->swapButton()->click();
}

//----------------------------------------------------------------------------------------------

void MainWindow::about() {
    QMessageBox::about(this, tr("About QPhoenix"), mAboutStr);
}

int MainWindow::currentIndex() const {
    return mTabWidget->currentIndex();
}
