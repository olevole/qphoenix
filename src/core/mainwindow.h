#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include "fancytabwidget.h"
#include "mainwindowinterface.h"
#include "dictionarywidgetinterface.h"
#include "dictionarywidget.h"
#include "translationwidget.h"
#include "querywrappers.h"



class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;
class QClipboard;


class Config;
class PluginsConfig;
class TranslatorsConfig;
class LanguageConfig;
class DictionaryConfig;

class MainWindow : public  QMainWindow, MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void setCurrentIndex(const int i);

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



//    void fillComboBox(QComboBox *cb, LanguageList &lst);


    void message(const QString &msg) {qDebug() << "TRANSLATION RESULT: " << msg;}


    void onDictionaryQueryChange(const QString &str);

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
    DictionaryConfig *mDictionaryConfig;

    QClipboard *mClipboard;
    QStringList mLastEnabledLanguages;

    QList<DictionaryInterface *> mDictList;

    TranslatorWrapper mTranslatorWrapper;
    DictionaryWrapper mDictionaryWrapper;
signals:
    void currentIndexChanged(const int i);



};


#endif // MAINWINDOW_H
