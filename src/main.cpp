#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "exceptions.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Settings s;
    return s.exec();

//    Exceptions e;

//    return e.exec();
}
