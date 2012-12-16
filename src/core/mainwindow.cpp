#include "mainwindow.h"

using namespace Gui;

#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDebug>

#include "translationwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mToolBar(new QToolBar(this)),
    mStatusBar(new QStatusBar(this)),
    mMenuBar(new QMenuBar(this)),
    mFancyWidget(new Core::Internal::FancyTabWidget(this))
{





    this->setCentralWidget(mFancyWidget);

    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);

    TranslationWidget *tw = new TranslationWidget;
    this->addPage(tw);

//    mFancyWidget->insertTab(0, new QWidget(this),QIcon::fromTheme("accessories-text-editor"),"Translator" );
//      mFancyWidget->insertTab(1, new QWidget(this),QIcon::fromTheme("accessories-dictionary"),"Dictionary" );
//      mFancyWidget->setTabEnabled(0, true);
//      mFancyWidget->setTabEnabled(1, true);

//    mFancyWidget->insertTab();



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

    mFancyWidget->insertTab(0, page, icon, name);
    mFancyWidget->setTabEnabled(0, true);

    resize(800, 600);

}

void MainWindow::removePage(const QWidget *page) {

}

MainWindowTabInterface *MainWindow::pageAt(const int i) {

}
