#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
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


    QString getCopyableContent();
private slots:

    //! Update plugins, etc information from config dialog.
    void onConfigAccept();

//    void open();
//    void save();
//    void saveAs();
//    void print();

    void clear();
    void copy();
    void undo();
    void redo();
    void swap();


    void about();



    void translate();
    void diction();





private:
    QStatusBar  *mStatusBar;
    QToolBar    *mToolBar;
    QMenuBar    *mMenuBar;
    QTabWidget *mFancyWidget;

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
