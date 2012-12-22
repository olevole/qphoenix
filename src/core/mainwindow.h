#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pluginapi.h"
#include "fancytabwidget.h"
#include "mainwindowinterface.h"

class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;

class TranslationWidget;
class DictionaryWidget;







class MainWindow : public  QMainWindow, MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void setCurrentTab(const int i);

    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);

    DictionaryWidgetInterface *dictionaryWidget() {
        mDictionaryWidget;
    }

    TranslatorWidgetInterface *translationWidget() {
        mTranslationWidget;
    }

    QToolBar *toolbar() {
        mToolBar;
    }

    void echo(QString &str) {
        qDebug() << "ECHO: " << str;
    }


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
    QAction *mCopyAction;

    // Help menu
    QAction *mAboutAction;

    TranslationWidget *mTranslationWidget;
    DictionaryWidget *mDictionaryWidget;
signals:
    void tabChanged(const int i);
};


#endif // MAINWINDOW_H
