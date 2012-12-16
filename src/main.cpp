#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "translationwidget.h"
#include "dictionarywidget.h"

//#include "utils/fancymainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//    DictionaryWidget dw; dw.show();
    Gui::Settings s;
    s.show();


//    Utils::FancyMainWindow mw;mw.show();
//    Gui::MainWindow mw;mw.show();


    return a.exec();
}
