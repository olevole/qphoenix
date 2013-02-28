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
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void setCurrentIndex(const int i);

    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);

    IDictionaryWidget *dictionaryWidget()
    {return qobject_cast<IDictionaryWidget *>(mDictionaryWidget);  }

    ITranslatorWidget *translationWidget()
    {return qobject_cast<ITranslatorWidget *>(mTranslationWidget);}


    void addToolBar(QToolBar *toolbar) {
        QMainWindow::addToolBar(toolbar);
    }


    QToolBar *toolbar()     { return mToolBar;      }
    QStatusBar *statusbar() { return mStatusBar;    }
    QMenuBar *menubar()     { return mMenuBar;      }


    int currentIndex() const;


//    QString getCopyableContent();


    void setWindowCloseable(const bool b) {mWindowCloseable = b;}
    bool windowCloseable() const { return mWindowCloseable;}
protected:
    void closeEvent(QCloseEvent *event);

private slots:



    //! Update plugins, etc information from config dialog.
    void onConfigAccept();
    void onIndexChange(const int i);

    void readCfg();
    void saveCfg();



    /*
     * Menu actions slots
     */

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



    void translate();
    void diction();
private:
    bool mWindowCloseable;


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

    TranslationWidget *mTranslationWidget;
    DictionaryWidget *mDictionaryWidget;

    Config *mSettingsDialog;

    PluginsConfig *mPluginsConfig;
    TranslatorsConfig *mTranslatorsConfig;
    LanguageConfig *mLanguageConfig;
    DictionaryConfig *mDictionaryConfig;

    QClipboard *mClipboard;
    QStringList mLastEnabledLanguages;

    QList<IDictionary *> mDictList;
    LanguagePairList mDictPairList;

    TranslatorWrapper mTranslatorWrapper;
    DictionaryWrapper mDictionaryWrapper;
signals:
    void currentIndexChanged(const int i);



};


#endif // MAINWINDOW_H
