#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "exceptions.h"

#include "fancytabwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Core::Internal::FancyTabWidget w;
    Settings s;
    return s.exec();

//    Exceptions e;

//    return e.exec();
}
