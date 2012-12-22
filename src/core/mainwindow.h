#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fancytabwidget.h"
#include "mainwindowinterface.h"

class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;
//class QPushButton;

class TranslationWidget;
class DictionaryWidget;
class Settings;







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

    DictionaryWidgetInterface *dictionaryWidget() {
//        return (DictionaryWidgetInterface *)mDictionaryWidget;
    }

    TranslatorWidgetInterface *translationWidget() {
//        return (TranslatorWidgetInterface *)mTranslationWidget;
    }

    QToolBar *toolbar() { return mToolBar; }
    QStatusBar *statusbar() { return mStatusBar; }
    QMenuBar *menubar() { return mMenuBar; }

public slots:

private:
    QStatusBar  *mStatusBar;
    QToolBar    *mToolBar;
    QMenuBar    *mMenuBar;
    Core::Internal::FancyTabWidget *mFancyWidget;

    QMenu   *mFileMenu, *mEditMenu, *mHelpMenu;

    // File menu
    QAction *mExitAction;

    // Edit Menu
    QAction *mCopyAction, *mOptionsAction;

    // Help menu
    QAction *mAboutAction;

    TranslationWidget *mTranslationWidget;
    DictionaryWidget *mDictionaryWidget;

    Settings *mSettingsDialog;
signals:
    void pageChanged(const int i);
};


#endif // MAINWINDOW_H
