/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

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
#include <QFrame>
#include <QTabWidget>
#include <QToolButton>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QWebFrame>
#include <QPainter>

#include "mainwindow.h"
#include "iplugin.h"
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
#include "itranslationwidget.h"
#include "commonconfig.h"


QString MainWindow::mAboutStr = "Trasnaltor and dictionary with plugins support.\n"
#ifdef QP_DEBUG
        "REVISION: "
        QP_GIT_REV
        "\nVersion: "
        QP_APP_VERSION
#endif
;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mSettings(new QSettings(this)),
    mSavePath(""),
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
    mActionSwap(new QAction(QP_ICON("system-switch-user"), tr("Swap"), this)),
    mActionOptions(new QAction(QP_ICON("configure"), tr("Options"), this)),

    mActionAbout(new QAction(QIcon::fromTheme("help-about"), tr("About"), this)),
    mActionAboutQt(new QAction(tr("About Qt"), this)),

    mTranslationWidget(new QPTranslationWidget(this)),
    mDictionaryWidget(new DictionaryWidget(this)),
    mSettingsDialog(new Config(this)),

    mPluginsConfig(new PluginsConfig),
    mTranslatorsConfig(new QPTranslatorsConfig(this)),
    mLanguageConfig(new LanguageConfig(this)),
    mDictionaryConfig(new DictionaryConfig(this)),
    mCommonConfig(new CommonConfig(this))
{
    setWindowTitle(qApp->applicationName());

    mActionOpen->setShortcut(QKeySequence("Ctrl+O"));
    mActionSave->setShortcut(QKeySequence("Ctrl+S"));
    mActionSaveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));
    mActionPrint->setShortcut(QKeySequence("Ctrl+P"));
    mActionExit->setShortcut(QKeySequence("Ctrl+Q"));

    mActionUndo->setShortcut(QKeySequence("Ctrl+U"));
    mActionRedo->setShortcut(QKeySequence("Ctrl+R"));
    mActionSwap->setShortcut(QKeySequence("Ctrl+Alt+S"));

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

    mToolBar->addAction(mActionOpen);
    mToolBar->addAction(mActionSave);
    mToolBar->addAction(mActionSaveAs);
    mToolBar->addSeparator();
    mToolBar->addAction(mActionClear);
    mToolBar->addAction(mActionUndo);
    mToolBar->addAction(mActionRedo);
    mToolBar->setMovable(false);

    mTabWidget->setTabPosition(QTabWidget::West);

    this->setCentralWidget(mTabWidget);
    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);

    this->addToolBar(mToolBar);
    this->addToolBar(mDictionaryWidget->getToolBar());
    this->addToolBar(mTranslationWidget->mainToolBar());

    mTabWidget->insertTab(mTabWidget->count(), mTranslationWidget, QP_ICON("translator"), tr("Translator"));
    mTabWidget->insertTab(mTabWidget->count(), mDictionaryWidget, QP_ICON("dictionary"), tr("Dictionary"));

    if(mTabWidget->count() > 1)
        mTabWidget->setCurrentIndex(0);

    // Configuring settings pages
    mSettingsDialog->addPage(mTranslatorsConfig, "Translators");
    mSettingsDialog->addPage(mDictionaryConfig, "Dictionaries");
    mSettingsDialog->addPage(mLanguageConfig, "Languages");
    mSettingsDialog->addPage(mPluginsConfig, "Plugins");
    mSettingsDialog->addPage(mCommonConfig, "Generic");

    connect(mActionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(mActionPrint, SIGNAL(triggered()), this, SLOT(print()));
    connect(mActionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(mActionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

    connect(mActionExit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(mActionClear, SIGNAL(triggered()), this, SLOT(clear()));
    connect(mActionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(mActionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(mActionSwap, SIGNAL(triggered()), mTranslationWidget, SLOT(swap()));
    connect(mActionOptions, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));
    connect(mActionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(mActionAbout, SIGNAL(triggered()), this, SLOT(about()));

    // Widgets , Dialogs, etc
    connect(mSettingsDialog, SIGNAL(accepted()), this, SLOT(onConfigAccept()));
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(onIndexChange(int)));

    connect(mTranslatorsConfig, SIGNAL(translatorIndexChanged(int)), mTranslationWidget, SLOT(setTranslatorIndex(int)));
    connect(mTranslationWidget, SIGNAL(translatorIndexChanged(int)), mTranslatorsConfig, SLOT(setTranslatorIndex(int)));
    connect(mTranslationWidget, SIGNAL(translatorIndexChanged(int)), this, SLOT(updateTranslatorConfig()));


    mSettings->beginGroup(QP_MAINWINDOW_CONFIG_GROUP);

    readCfg();
    // Read configs
    updateTranslatorConfig();
    onConfigAccept();

    mTranslationWidget->setTranslatorsNames(mTranslatorsConfig->getTranslatorsNames());

    mTranslatorsConfig->read();
}

MainWindow::~MainWindow()
{
    saveCfg();
}

QString MainWindow::getStatusBarMessage() const {
    return mStatusBar->currentMessage();
}

void MainWindow::addStatusBarWidget(QWidget *widget) {
    mStatusBar->addPermanentWidget(widget);
}

void MainWindow::addToolBarAction(QAction *action) {
    mToolBar->addAction(action);
}


void MainWindow::setCurrentIndex(int i) {
    mTabWidget->setCurrentIndex(i);
    onIndexChange(i);
}

void MainWindow::setStatusBarMessage(const QString &msg, int timeout) {
    mStatusBar->showMessage(msg, timeout);
}

void MainWindow::onConfigAccept() {
    /*!
     * Plugins processing
     */
    PluginConnector connector;
    connector.configdialog = mSettingsDialog;
    connector.mainwindow = this;
    connector.translationwidget = mTranslationWidget;
    connector.dictionarywidget = mDictionaryWidget;

    QPPluginList *lst = mPluginsConfig->pluginsList();

    qDebug() << "Plugins Count: " <<  lst->size();

    for(int i = 0; i < lst->count(); i++) {

        QPPlugin plugin = lst->at(i);
        qDebug() << "Loading plugin: " <<  plugin.data.name;
        bool enabled = mPluginsConfig->isEnabled(i);
        if(enabled) {
            plugin.instance->setPluginConnector(connector);
            plugin.instance->load();

        } else if(plugin.instance->isLoaded()) {
                plugin.instance->unload();
        }
    }

    mLanguageConfig->setNativeNames(mCommonConfig->getNativeNamesEnabled());
    mTranslationWidget->setNativeNames(mCommonConfig->getNativeNamesEnabled());

    mDictionaryWidget->setNativeNames(mCommonConfig->getNativeNamesEnabled());
    mDictionaryWidget->setDictionaryList(mDictionaryConfig->dictionaries());

    updateTranslatorConfig();
}

void MainWindow::updateTranslatorConfig() {
    QPTranslator tr = mTranslatorsConfig->currentTranslator();
    mTranslationWidget->setEnabledLanguages(mLanguageConfig->getEnabledLanguages());
    mTranslationWidget->setTranslator(tr);
}

void MainWindow::onIndexChange(const int i) {
    mDictionaryWidget->getToolBar()->setVisible(i == 1);
    mTranslationWidget->mainToolBar()->setVisible(i == 0);
}

void MainWindow::readCfg() {
    setCurrentIndex(mSettings->value("TabIndex", 0).toInt());
    restoreGeometry(mSettings->value("Geometry").toByteArray());
}

void MainWindow::saveCfg() {
    mSettings->setValue("TabIndex", mTabWidget->currentIndex());
    mSettings->setValue("Geometry", saveGeometry());
}

//----------------------------------------------------------------------------------------------
// Actions slots

void MainWindow::open() {
    const QString path = QFileDialog::getOpenFileName(this);
    QFile file(path);
    if(!file.open( QFile::ReadOnly))
        return;
    const QString text = file.readAll();
    mTranslationWidget->setSourceText(text);
}

void MainWindow::print() {
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);

    if(dialog->exec() != QPrintDialog::Accepted)
        return;

    const int i = mTabWidget->currentIndex();
    QString text;
    QPainter painter;
    painter.begin(&printer);

    switch(i){
    case 0:
        text = mTranslationWidget->getSourceText();
        break;
    case 1:
        text = mDictionaryWidget->getResultText();
        break;
    }
    painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, text);
    painter.end();
}

void MainWindow::save() {
    QFile file;
    if(QFile::exists(mSavePath)) {
        file.setFileName(mSavePath);
    } else {
        mSavePath = QFileDialog::getSaveFileName(
                    this, tr("Save file"),
                    QDir::homePath(),
                    tr("Image Files (*.txt *.html )"));
        file.setFileName(mSavePath);
    }

    file.open(QFile::Truncate | QFile::ReadWrite);

    const int i = mTabWidget->currentIndex();
    switch(i){
        case 0:
            file.write(mTranslationWidget->getResultText().toUtf8());
        break;
        case 1:
            file.write(mDictionaryWidget->getResultText().toUtf8());
        break;
    }

    file.close();
}

void MainWindow::saveAs() {
    mSavePath = "";
    save();
}

void MainWindow::exit() {
    saveCfg();
    qApp->quit();
}

void MainWindow::clear() {
    const int i = mTabWidget->currentIndex();
    switch(i){
        case 0:
            mTranslationWidget->clearSourceText();
            mTranslationWidget->clearResultText();
        break;
        case 1:
            mDictionaryWidget->clearSourceText();
        break;
    }
}

void MainWindow::undo() {
    mTabWidget->currentIndex() == 0 ? mTranslationWidget->undo()
                        : mDictionaryWidget->undo();
}

void MainWindow::redo() {
    mTabWidget->currentIndex() == 0 ? mTranslationWidget->redo()
                        : mDictionaryWidget->redo();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About QPhoenix"), mAboutStr);
}
