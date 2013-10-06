#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include "imainwindow.h"
#include "idictionarywidget.h"
#include "dictionarywidget.h"
#include "translationwidget.h"

class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;
class QClipboard;
class QTabWidget;
class QTimer;
class QCloseEvent;

class Config;
class PluginsConfig;
class QPTranslatorsConfig;
class LanguageConfig;
class DictionaryConfig;
class CommonConfig;

class MainWindow : public  QMainWindow, public IMainWindow
{
    Q_OBJECT
    Q_INTERFACES(IMainWindow)
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMainWindow *instance() {return this;}

    //Begin API methods
    virtual QString getStatusBarMessage() const;
    virtual void addStatusBarWidget(QWidget *widget);
    virtual void addToolBarAction(QAction *action);
    //End API methods
public slots:
    //Begin API methods
    virtual void setCurrentIndex(int i);
    virtual void setStatusBarMessage(const QString &msg, int timeout);
    //End API methods
private slots:

    //! Update plugins, etc information from config dialog.
    void onConfigAccept();
    void updateTranslatorConfig();

    //! Handle table index change
    void onIndexChange(const int i);

    void readCfg();
    void saveCfg();

    // Menu actions slots
    void open();
    void save();
    void saveAs();
    void print();

    void exit();

    void clear();
//    void copy();
    void undo();
    void redo();
//    void swap();
    void about();
private:
    QString mSavePath;

    QStatusBar  *mStatusBar;
    QToolBar    *mToolBar;
    QMenuBar    *mMenuBar;
    QTabWidget *mTabWidget;

    QMenu   *mFileMenu, *mEditMenu, *mToolsMenu, *mHelpMenu;

    // File menu
    QAction
    *mActionExit,
    *mActionOpen,
    *mActionSave,
    *mActionSaveAs,
    *mActionPrint;

    // Edit Menu
    QAction
    *mActionClear,
    *mActionUndo,
    *mActionRedo,
    *mActionSwap,
    *mActionOptions;

    // Help menu
    QAction *mActionAbout, *mActionAboutQt;

    // Main widgets
    QPTranslationWidget *mTranslationWidget;
    DictionaryWidget *mDictionaryWidget;

    /*!
     * Main config dialog and these pages
     */
    Config *mSettingsDialog;
    PluginsConfig *mPluginsConfig;
    QPTranslatorsConfig *mTranslatorsConfig;
    LanguageConfig *mLanguageConfig;
    DictionaryConfig *mDictionaryConfig;\
    CommonConfig *mCommonConfig;

    static QString mAboutStr;
signals:
    void currentIndexChanged(const int i);
};
