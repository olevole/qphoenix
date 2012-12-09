#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Gui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui_MainWindow;
//    ui->setupUi(this);


    using namespace Core;
         using namespace Core::Internal;

    FancyTabWidget* ptab = new FancyTabWidget(this);

//    w.show();
    this->setCentralWidget(ptab);
    ptab->insertTab(0, new QWidget(this),QIcon("images/mode_Edit.png"),"Very~" );
    ptab->insertTab(1, new QWidget(this),QIcon("images/mode_Edit.png"),"Very~" );
    ptab->setTabEnabled(0, true);
    ptab->setTabEnabled(1, true);
}

MainWindow::~MainWindow()
{
}
