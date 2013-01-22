#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fancytabwidget.h"
#include "mainwindowinterface.h"
#include "dictionarywidgetinterface.h"
#include "dictionarywidget.h"
#include "translationwidget.h"



class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;
//class QPushButton;


class Config;
class PluginsConfig;
class TranslatorsConfig;
class LanguageConfig;

class MainWindow : public  QMainWindow, MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void setCurrentPage(const int i);

    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);

    DictionaryWidgetInterface *dictionaryWidget()
    {return qobject_cast<DictionaryWidgetInterface *>(mDictionaryWidget);  }

    TranslatorWidgetInterface *translationWidget()
    {return qobject_cast<TranslatorWidgetInterface *>(mTranslationWidget);}


    QToolBar *toolbar()     { return mToolBar;      }
    QStatusBar *statusbar() { return mStatusBar;    }
    QMenuBar *menubar()     { return mMenuBar;      }

private slots:

    //! Update plugins, etc information from config dialog.
    void onConfigAccept();


    void about();

private:
    QStatusBar  *mStatusBar;
    QToolBar    *mToolBar;
    QMenuBar    *mMenuBar;
    Core::Internal::FancyTabWidget *mFancyWidget;

    QMenu   *mFileMenu, *mEditMenu, *mHelpMenu;

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
    *mActionCopy,
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


    QStringList mLastEnabledLanguages;
signals:
    void pageChanged(const int i);

};


#endif // MAINWINDOW_H
