#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "translationwidget.h"
#include "dictionarywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    DictionaryWidget dw; dw.show();
//    Gui::Settings s;
//    s.show();

//    Gui::MainWindow mw;mw.show();


    return a.exec();
}
