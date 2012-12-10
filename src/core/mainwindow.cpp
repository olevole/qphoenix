#include "mainwindow.h"

using namespace Gui;

#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mToolBar(new QToolBar(this)),
    mStatusBar(new QStatusBar(this)),
    mMenuBar(new QMenuBar(this))
{

    this->setStatusBar(mStatusBar);
    this->setMenuBar(mMenuBar);
//    ui = new Ui_MainWindow;
//    ui->setupUi(this);


    using namespace Core;
         using namespace Core::Internal;

    FancyTabWidget* ptab = new FancyTabWidget(this);

//    w.show();
    this->setCentralWidget(ptab);
    ptab->insertTab(0, new QWidget(this),QIcon::fromTheme("accessories-text-editor"),"Translator" );
    ptab->insertTab(1, new QWidget(this),QIcon::fromTheme("accessories-dictionary"),"Dictionary" );
    ptab->setTabEnabled(0, true);
    ptab->setTabEnabled(1, true);
    this->resize(800, 600);
}

MainWindow::~MainWindow()
{
}
