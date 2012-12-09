#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Gui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui_MainWindow;
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
}
