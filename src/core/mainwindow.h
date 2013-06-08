#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include "imainwindow.h"
#include "idictionarywidget.h"
#include "dictionarywidget.h"
#include "translationwidget.h"
#include "querywrappers.h"

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
class TranslatorsConfig;
class LanguageConfig;
class DictionaryConfig;

class MainWindow : public  QMainWindow, IMainWindow
{
    Q_OBJECT
    Q_INTERFACES(IMainWindow)
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);

    IDictionaryWidget *dictionaryWidget()
    {return qobject_cast<IDictionaryWidget *>(mDictionaryWidget); }

    ITranslatorWidget *translatorWidget()
    {return qobject_cast<ITranslatorWidget *>(mTranslationWidget);}

    QMainWindow *instance() {return this;}
    QToolBar *toolbar()     { return mToolBar;      }
    QStatusBar *statusbar() { return mStatusBar;    }
    QMenuBar *menubar()     { return mMenuBar;      }

    int currentIndex() const;
public slots:
    void setCurrentIndex(const int i);
protected:
//    void closeEvent(QCloseEvent *event);
private slots:
    //! Update plugins, etc information from config dialog.
    void onConfigAccept();

    //! Handle table index change
    void onIndexChange(const int i);
    void readCfg();
    void saveCfg();

    // Menu actions
//    void open();
//    void save();
//    void saveAs();
//    void print();
    void exit();

    void clear();
//    void copy();
    void undo();
    void redo();
    void swap();
    void about();
private:
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
//    *mActionCopy,
    *mActionUndo,
    *mActionRedo,
    *mActionSwap,
    *mActionOptions;

    // Help menu
    QAction *mActionAbout, *mActionAboutQt;

    // Main widgets
    TranslationWidget *mTranslationWidget;
    DictionaryWidget *mDictionaryWidget;

    /*!
     * Main config dialog and these pages
     */
    Config *mSettingsDialog;
    PluginsConfig *mPluginsConfig;
    TranslatorsConfig *mTranslatorsConfig;
    LanguageConfig *mLanguageConfig;
    DictionaryConfig *mDictionaryConfig;
    static QString mAboutStr;
signals:
    void currentIndexChanged(const int i);
};


#endif // MAINWINDOW_H
