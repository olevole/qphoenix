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



namespace Gui {


using namespace Api;



class MainWindow : public  QMainWindow//, MainWindowAPI
{
    Q_OBJECT

//    typedef QList<MainWindowTabInterface *>TabsList;

    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    virtual void addPage(QWidget *page);
    virtual void removePage(const QWidget *page);
    virtual MainWindowTabInterface *pageAt(const int i);



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

}// end Gui namespace

#endif // MAINWINDOW_H
