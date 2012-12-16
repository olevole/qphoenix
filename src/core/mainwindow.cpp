#include "mainwindow.h"

using namespace Gui;

#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QMenu>
#include <QAction>




//#include "translationwidget.h"
//#include "dictionarywidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mToolBar(new QToolBar(this)),
    mStatusBar(new QStatusBar(this)),
    mMenuBar(new QMenuBar(this)),
    mFancyWidget(new Core::Internal::FancyTabWidget(this)),

    // Menus
    mFileMenu(new QMenu(tr("File"), this)),
    mEditMenu(new QMenu(tr("Edit"), this)),
    mHelpMenu(new QMenu(tr("Help"), this)),

    //Actions
    mExitAction(new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), this)),
    mCopyAction(new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this)),
    mAboutAction(new QAction(QIcon::fromTheme("help-about"), tr("About"), this))
{

//    mMenuBar->setDisabled();


    mFileMenu->addAction(mExitAction);
    mEditMenu->addAction(mCopyAction);
    mHelpMenu->addAction(mAboutAction);


    mMenuBar->addMenu(mFileMenu);
    mMenuBar->addMenu(mEditMenu);
    mMenuBar->addMenu(mHelpMenu);


    QList<QAction *> ActionsList;
    ActionsList << mExitAction << mCopyAction << mAboutAction;
    mToolBar->addActions(ActionsList);
    mToolBar->setMovable(false);



    this->setCentralWidget(mFancyWidget);

//    Utils::StyledBar sb;sb.show();

//mFancyWidget->addCornerWidget(&sb);

    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);
    this->addToolBar(Qt::RightToolBarArea, mToolBar);
//    mToolBar->setDisab;

//    TranslationWidget *tw = new TranslationWidget;
//    DictionaryWidget *dw = new DictionaryWidget;
//    this->addPage(tw);
//    this->addPage(dw);


    QPushButton *pb = new QPushButton(this);


    mFancyWidget->addCornerWidget(pb);
    mFancyWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
}


void MainWindow::addPage(QWidget *page) {

    MainWindowTabInterface *i =
            qobject_cast<MainWindowTabInterface *>(page);


    if(i == NULL) {
        qDebug() << "Problem here!"; //TODO: fix it!
        return;
    }


    QIcon icon = i->info()->icon();
    QString name = i->info()->name();

    QGroupBox *gb = new QGroupBox(this);

    gb->setTitle(name);
    gb->setLayout(new QHBoxLayout);
    gb->layout()->addWidget(page);
//    gb->setFlat(true);

    mFancyWidget->insertTab(mFancyWidget->count(), gb, icon, name);
//    mFancyWidget->setTabEnabled(0, true);

    resize(800, 600);

}

void MainWindow::removePage(const QWidget *page) {

}

MainWindowTabInterface *MainWindow::pageAt(const int i) {

}
