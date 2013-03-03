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
//    mActionCopy(new QAction(QP_ICON("edit-copy"),tr("Copy"), this)),
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
    mDictionaryConfig(new DictionaryConfig(this)),
    mClipboard(qApp->clipboard())
{
    setWindowTitle(qApp->applicationName());

    // Closeable by default
    setWindowCloseable(true);


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
    mToolBar->addSeparator();
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




    connect(mActionExit, SIGNAL(triggered()), this, SLOT(exit()));

    connect(mActionClear, SIGNAL(triggered()), this, SLOT(clear()));
    connect(mActionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(mActionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(mActionSwap, SIGNAL(triggered()), this, SLOT(swap()));
    connect(mActionOptions, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));

    connect(mActionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(mActionAbout, SIGNAL(triggered()), this, SLOT(about()));



    // Widgets , Dialogs, etc
    connect(mDictionaryWidget, SIGNAL(queryChanged()), this, SLOT(diction()));
    connect(mSettingsDialog, SIGNAL(accepted()), this, SLOT(onConfigAccept()));

    connect(translationWidget()->translateButton(), SIGNAL(clicked()), this, SLOT(translate()));

    connect(&mDictionaryWrapper, SIGNAL(reply(DictionaryVariantList)), mDictionaryWidget, SLOT(displayData(DictionaryVariantList)));
    connect(&mDictionaryWrapper, SIGNAL(reply(QStringList)), mDictionaryWidget, SLOT(setCompletions(QStringList)));

    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(onIndexChange(int)));

    QComboBox *src = mTranslationWidget->translatorComboBox();
    QComboBox *dest = mTranslatorsConfig->translatorComboBox();

    connect(src, SIGNAL(currentIndexChanged(int)), dest, SLOT(setCurrentIndex(int)));
    connect(dest, SIGNAL(currentIndexChanged(int)), src, SLOT(setCurrentIndex(int)));

    connect(&mTranslatorWrapper, SIGNAL(timeout()), this, SLOT(onTranslatorTimeout()));
    connect(&mDictionaryWrapper, SIGNAL(timeout()), this, SLOT(onDictionaryTimeout()));


    QStringList items;
    for (int i = 0; i < dest->count(); ++i) {
        items << dest->itemText(i);
    }

    src->clear();

    src->addItems(items);

    readCfg();

    // Read configs
    onConfigAccept();



    // NOTE: Timeout must be set! By default it's 0 (nothing will be processed)
    mTranslatorWrapper.setTimeout(10000);
    mDictionaryWrapper.setTimeout(10000);
}

MainWindow::~MainWindow()
{
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
//    resize(800, 600);
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


    //TODO: move this code to translationwidget cls :)

    if(enabledKeys != mLastEnabledLanguages) {
        mLastEnabledLanguages = enabledKeys;
        ITranslator *translator  = mTranslatorsConfig->currentTranslator();
        LanguageTable table;

        if(translator != NULL)
            table = translator->table();
        else
            qWarning("No translators loaded! Nothing to do!");

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
        mTranslationWidget->setLangTable(table);
    }




    // Updating table



    /*!
     * Dictionaries sync
     */

    QObjectList dicts = mDictionaryConfig->dictionaries();

//    QStringList enabledKeys = mLanguageConfig->keysForEnabled();
    foreach(QObject *obj, dicts) {
        IDictionary *iface = qobject_cast<IDictionary *>(obj);
        mDictList << iface;

        if(!iface->isLoaded())
            iface->load();

//        mDictPairList <<
                        LanguagePairList list = iface->pairs();

        for(int i = 0; i < list.count(); i++) {
            const LanguagePair pair = list.at(i);


            const QString first = QP_LANG_FACTORY->languages()[pair.first].name();
            const QString second = QP_LANG_FACTORY->languages()[pair.second].name();

            if(!first.isEmpty() && !second.isEmpty()) {
                    mDictionaryWidget->languagesComboBox()->addItem(first + " -> " + second);
                    mDictPairList << pair;



            } else {

//                mDictPairList.removeAt(i);
//                delete &mDictPairList[i];
                qWarning("This language doesn't supported yet! Sorry...");
            }
        }
    }

    mDictionaryWrapper.setDictionaryList(mDictList);

    qDebug() << "SIZE OF DICTS" << mDictList.count();


    mTranslationWidget->setTranslator(mTranslatorsConfig->currentTranslator());
}


void MainWindow::onIndexChange(const int i) {
    mDictionaryWidget->mainToolBar()->setVisible(i == 1);
    mTranslationWidget->mainToolBar()->setVisible(i == 0);
}


void MainWindow::onTranslatorTimeout() {
    mStatusBar->clearMessage();
    mStatusBar->showMessage(tr("Translator reply timeout!"));
}


void MainWindow::onDictionaryTimeout() {
    mStatusBar->clearMessage();
    mStatusBar->showMessage(tr("Dictionary reply timeout!"));
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


void MainWindow::exit() {
    saveCfg();
    qApp->quit();
}


void MainWindow::clear() {
    const int i = currentIndex();
    switch(i){
        case 0:
            translationWidget()->srcText()->clear();
            translationWidget()->resText()->clear();
        break;

        case 1:
            dictionaryWidget()->srcText()->clear();
            dictionaryWidget()->resText()->setHtml("<html><body></body></html>");
        break;
    }
}



void MainWindow::undo() {
    switch(currentIndex()) {
    case 0:
        translationWidget()->srcText()->undo();
        break;
    case 1:
        dictionaryWidget()->srcText()->undo();
        break;
    }

}

void MainWindow::redo() {
    switch(currentIndex()) {
    case 0:
        translationWidget()->srcText()->redo();
        break;
    case 1:
        dictionaryWidget()->srcText()->redo();
    break;
    }
}

void MainWindow::swap() {
    translationWidget()->swapButton()->click();
}

//----------------------------------------------------------------------------------------------

void MainWindow::about() {
    QMessageBox::about(this, tr("About QPhoenix"),
                                      tr("QPhoenix is an advanced translation tool that \
                                         could use multiple dictionaries and translators"));
}

void MainWindow::translate() {
//    mStatusBar->clearMessage();


//    QString src_text = this->translationWidget()->srcText()->toPlainText();


//    QString src_lang = mTranslationWidget->srcComboBox()->
//            itemData(mTranslationWidget->srcComboBox()->currentIndex()).toString();


//    QString res_lang = mTranslationWidget->resComboBox()->
//            itemData(mTranslationWidget->resComboBox()->currentIndex()).toString();

//    if(src_lang == res_lang) {
//        mStatusBar->showMessage(tr("Please select two distinct languages!"));
//        return;
//    }

//    connect(&mTranslatorWrapper, SIGNAL(reply(QString)), this->translationWidget()->resText(), SLOT(setText(QString)));


}


void MainWindow::diction() {
    const QString text = mDictionaryWidget->srcText()->text();
    const LanguagePair pair = mDictPairList.at(mDictionaryWidget->languagesComboBox()->currentIndex());

    qDebug() << "TEXT: " << text ;

    mDictionaryWrapper.query(pair, text);
}

int MainWindow::currentIndex() const {
    return mTabWidget->currentIndex();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(mWindowCloseable) {
        saveCfg();
        event->accept();
        QMainWindow::closeEvent(event);
    } else {
        event->ignore();
    }
}
