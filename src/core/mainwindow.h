#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pluginapi.h"
#include "fancytabwidget.h"


class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;








class MainWindow : public  QMainWindow, Api::MainWindowAPI
{
    Q_OBJECT
    Q_INTERFACES(Api::MainWindowAPI)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    virtual void addPage(QWidget *page);
    virtual void removePage(const QWidget *page);
    virtual QWidget *pageAt(const int i);



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
signals:
    void tabChanged(const int i);
    void setCurrentTab(const int i);
};


#endif // MAINWINDOW_H
