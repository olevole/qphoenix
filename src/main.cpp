#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "translationwidget.h"
#include "dictionarywidget.h"
#include "translatorloader.h"
#include "defines.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//    DictionaryWidget dw; dw.show();
    Settings s;s.show();

    MainWindow mw;mw.show();
    QP_DBG("Message!");


    return a.exec();
}
