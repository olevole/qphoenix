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

#include "plugininterface.h"
#include "querywrappers.h"

#include "translationwidget.h"
#include "dictionarywidget.h"
#include "config.h"
#include "translatorsconfig.h"
#include "defines.h"
#include "pluginsconfig.h"
#include "loader.h"
#include "translatorinterface.h"
#include "languageconfig.h"
#include <QThread>
#include <qtconcurrentrun.h>


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
    mActionExit(new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), this)),
    mActionOpen(new QAction(tr("Open"), this)),
    mActionSave(new QAction(tr("Save"), this)),
    mActionSaveAs(new QAction(tr("Save As"), this)),
    mActionPrint(new QAction(tr("Print"), this)),

    mActionClear(new QAction(tr("Clear"), this)),
    mActionCopy(new QAction(QIcon::fromTheme("edit-copy"),tr("Copy"), this)),
    mActionUndo(new QAction(tr("Undo"), this)),
    mActionRedo(new QAction(tr("Redo"), this)),
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


    mTranslatorWrapper(new TranslatorWrapper())
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
    mEditMenu->addAction(mActionCopy);
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


    QList<QAction *> ActionsList;
    ActionsList << mActionExit << mActionCopy << mActionAbout;
    mToolBar->addActions(ActionsList);



    this->setCentralWidget(mFancyWidget);


    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);
    this->addToolBar(Qt::RightToolBarArea, mToolBar);


    this->addPage(mTranslationWidget);
    this->addPage(mDictionaryWidget);


    if(mFancyWidget->count() > 0)
        mFancyWidget->setCurrentIndex(0);


    mSettingsDialog->addPage(mTranslatorsConfig);
    mSettingsDialog->addPage(mPluginsConfig);
    mSettingsDialog->addPage(mLanguageConfig);

    connect(mActionOptions, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));
    connect(mActionExit, SIGNAL(triggered()), qApp, SLOT(quit()));


    connect(mActionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(mActionAbout, SIGNAL(triggered()), this, SLOT(about()));


    connect(mSettingsDialog, SIGNAL(accepted()), this, SLOT(onConfigAccept()));


    connect(translationWidget()->translateButton(), SIGNAL(clicked()), this, SLOT(translate()));

    onConfigAccept();

//    wp = new TranslatorWrapper;
////    QThread thread;

//

//    wp->setTranslator(mTranslatorsConfig->currentTranslator());
//    wp->moveToThread(&thread);
//    wp->setParams("test","test","test");

//    connect(&thread, SIGNAL(started()), wp, SLOT(execute()));
//    thread.start();
//    wp->execQuery("test", "test", "test");



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
    return new QWidget();
}

void MainWindow::setCurrentPage(const int i) {
    mFancyWidget->setCurrentIndex(i);
}


void MainWindow::onConfigAccept() {
    /*!
     * Plugins processing
     *
     */
    ModuleList *lst = mPluginsConfig->pluginsList();

    for(int i = 0; i < lst->count(); i++) {
        qDebug() << "iteration #" << i;
        PluginInterface *iface =  qobject_cast<PluginInterface *>(lst->at(i));

        bool enabled = mPluginsConfig->isEnabled(i);
        if(enabled) {
            iface->load();
            iface->setMainWindowPTR(this);
        } else if(iface->isLoaded()) {
                iface->unload();
        }
    }


    /*!
     * Updating translators information...
     */



    QStringList enabledKeys = mLanguageConfig->keysForEnabled();

    mLanguageConfig->setUseNativeNames(false);
    mTranslationWidget->setNativeNames(false);


    if(enabledKeys != mLastEnabledLanguages) {
        mLastEnabledLanguages = enabledKeys;

        qDebug() << "Being uptadted--____";

        TranslatorInterface *translator  = mTranslatorsConfig->currentTranslator();
        LanguageTable table;

        if(translator != NULL)
            table = translator->table();
        else
            qDebug("No translators loaded! Nothing to do!");


        QStringList keys = table.keys();

        for(LanguageTable::iterator i = table.begin(); i != table.end(); i++) {
            const QString key = i.key();
            if(!enabledKeys.contains(key)) {
                table.remove(key);
            } else {
                QStringList values = i.value();
                for (int j = 0; j < values.count(); ++j) {
                    if(!enabledKeys.contains(values.at(j)))
                        values.removeAt(j);
                }
                table[key] = values;
            }
        }
        qDebug() << "ALL KEYS: " << table.values();
        mTranslationWidget->setLangTable(table);
    }


    // Updating table
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About QPhoenix"),
                                      tr("Advanced translation tool Advanced translation toolAdvanced translation tool"));
}

void MainWindow::translate() {
    QString src_text = this->translationWidget()->srcText()->toPlainText();
    QString src_lang = mLastEnabledLanguages.at(mTranslationWidget->srcComboBox()->currentIndex());
    QString res_lang = mLastEnabledLanguages.at(mTranslationWidget->resComboBox()->currentIndex());

    connect(mTranslatorWrapper, SIGNAL(reply(QString)), this->translationWidget()->resText(), SLOT(setText(QString)));

    mTranslatorWrapper->setTranslator(mTranslatorsConfig->currentTranslator());

    mTranslatorWrapper->setParams(src_text, src_lang, res_lang);
    mTranslatorWrapper->moveToThread(&mTranslatorWorkerThread);


    connect(&mTranslatorWorkerThread, SIGNAL(started()), mTranslatorWrapper, SLOT(execute()));
    mTranslatorWorkerThread.start();


    qDebug() << "Src text: " << src_text << " SRc Lang: " << src_lang << " REs Lang: " << res_lang;
}
