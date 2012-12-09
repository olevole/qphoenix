#include "mainwindow.h"
#include <QApplication>

#include "settings.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Gui::MainWindow *mw = new Gui::MainWindow;
    mw->show();

    Gui::Settings s;s.show();


    return a.exec();
}
