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
    mFancyWidget(new QTabWidget(this)),

    // Menus
    mFileMenu(new QMenu(tr("File"), this)),
    mEditMenu(new QMenu(tr("Edit"), this)),
    mHelpMenu(new QMenu(tr("Help"), this)),

    //Actions
    mActionExit(new QAction(QP_ICON("application-exit"), tr("Exit"), this)),
    mActionOpen(new QAction(QP_ICON("document-open"),tr("Open"), this)),
    mActionSave(new QAction(QP_ICON("document-save"),tr("Save"), this)),
    mActionSaveAs(new QAction(QP_ICON("document-save-as"),tr("Save As"), this)),
    mActionPrint(new QAction(QP_ICON("document-print"),tr("Print"), this)),

    mActionClear(new QAction(QP_ICON("edit-clear"), tr("Clear"), this)),
    mActionCopy(new QAction(QP_ICON("edit-copy"),tr("Copy"), this)),
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
    ActionsList << mActionClear <<  mActionUndo<< mActionRedo, mActionAbout;
    mToolBar->addActions(ActionsList);

    this->setCentralWidget(mFancyWidget);

//    mMenuBar->setCornerWidget(new QPushButton());

    mFancyWidget->setTabPosition(QTabWidget::West);

//    mFancyWidget->setBackgroundBrush(QBrush(Qt::red));
    this->setStatusBar(mStatusBar);

    this->setMenuBar(mMenuBar);
    this->addToolBar(mToolBar);


    this->addPage(mTranslationWidget);
    this->addPage(mDictionaryWidget);


    if(mFancyWidget->count() > 0)
        mFancyWidget->setCurrentIndex(0);


    mSettingsDialog->addPage(mTranslatorsConfig);
    mSettingsDialog->addPage(mDictionaryConfig);

    mSettingsDialog->addPage(mLanguageConfig);
    mSettingsDialog->addPage(mPluginsConfig);

    connect(mActionOptions, SIGNAL(triggered()), mSettingsDialog, SLOT(show()));
    connect(mActionExit, SIGNAL(triggered()), qApp, SLOT(quit()));


    connect(mActionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(mActionAbout, SIGNAL(triggered()), this, SLOT(about()));

    // Edit actions connects
    connect(mActionClear, SIGNAL(triggered()), this, SLOT(clear()));
    connect(mActionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(mActionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(mActionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(mActionSwap, SIGNAL(triggered()), this, SLOT(swap()));


    connect(mSettingsDialog, SIGNAL(accepted()), this, SLOT(onConfigAccept()));


    connect(translationWidget()->translateButton(), SIGNAL(clicked()), this, SLOT(translate()));

    onConfigAccept();


//    QStringList wordList;
//    wordList << "alpha" << "omega" << "omicron" << "zeta";

//    mDictionaryWidget->setCompletions(wordList);
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

int MainWindow::currentIndex() const {
    return mFancyWidget->currentIndex();
}

void MainWindow::setCurrentIndex(const int i) {
    mFancyWidget->setCurrentIndex(i);
}


void MainWindow::onConfigAccept() {
    /*!
     * Plugins processing
     *
     */
    QObjectList *lst = mPluginsConfig->pluginsList();

    for(int i = 0; i < lst->count(); i++) {
        qDebug() << "iteration #" << i;
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


    if(enabledKeys != mLastEnabledLanguages) {
        mLastEnabledLanguages = enabledKeys;

        qDebug() << "Being uptadted--____";

        ITranslator *translator  = mTranslatorsConfig->currentTranslator();
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



    /*!
     * Dictionaries sync
     */


    QObjectList dicts = mDictionaryConfig->dictionaries();

    IDictionary *iface = qobject_cast<IDictionary *>(dicts.first());
    iface->load();

    iface->completions("test", LanguagePair("ru", "en"));

    mDictionaryWidget->setCompletions(iface->completions("test", LanguagePair("ru", "en")));

    mDictionaryWidget->displayData(iface->query(LanguagePair("en", "fr"), "test"));


}


//----------------------------------------------------------------------------------------------
// Actions slots
void MainWindow::clear() {
    const int i = currentIndex();
    switch(i){
        case 0:
            translationWidget()->srcText()->clear();
            translationWidget()->resText()->clear();
        break;

        case 1:
            dictionaryWidget()->srcText()->clear();
            dictionaryWidget()->resText()->clear();
        break;
    }
}

void MainWindow::copy() {
    mClipboard->setText(getCopyableContent());
}


void MainWindow::undo() {
    switch(currentIndex()) {
    case 0:
        translationWidget()->srcText()->undo();
        break;
//    case 1:
//        dictionaryWidget()->srcText()->undo();
//        break;
    }

}

void MainWindow::redo() {
    switch(currentIndex()) {
    case 0:
        translationWidget()->srcText()->redo();
        break;
//    case 1:
//            dictionaryWidget()->srcText()->redo();
//        break;
    }
}

void MainWindow::swap() {
//    translationWidget()->swapButton().
}

//----------------------------------------------------------------------------------------------

void MainWindow::about() {
    QMessageBox::about(this, tr("About QPhoenix"),
                                      tr("QPhoenix is an advanced translation tool that could use multiple dictionaries and translators"));
}

void MainWindow::translate() {
    QString src_text = this->translationWidget()->srcText()->toPlainText();


    QString src_lang = mTranslationWidget->srcComboBox()->
            itemData(mTranslationWidget->srcComboBox()->currentIndex()).toString();


    QString res_lang = mTranslationWidget->resComboBox()->
            itemData(mTranslationWidget->resComboBox()->currentIndex()).toString();




    connect(&mTranslatorWrapper, SIGNAL(reply(QString)), this->translationWidget()->resText(), SLOT(setText(QString)));


    mTranslatorWrapper.setTranslator(mTranslatorsConfig->currentTranslator());
    mTranslatorWrapper.query( src_lang, res_lang, src_text);


    qDebug() << "Src text: " << src_text << " SRc Lang: " << src_lang << " REs Lang: " << res_lang;
}


void MainWindow::diction() {

}


void MainWindow::onDictionaryQueryChange(const QString &str) {
//    foreach(DictionaryInterface *iface, )
}

QString MainWindow::getCopyableContent()  {
    QString text;
    switch(currentIndex()) {
    case 0:
        text = translationWidget()->resText()->toPlainText();
    case 1:
        //TODO: improve this part (because of html content?)
        text = dictionaryWidget()->resText()->toPlainText();
    }
    return text;
}
