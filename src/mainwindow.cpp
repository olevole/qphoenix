#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "historymanager/historymanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HistoryManager m; m.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
