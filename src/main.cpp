#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "translationwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    Gui::MainWindow *mw = new Gui::MainWindow;
//    mw->show();

//    TranslationWidget t; t.show();

    Gui::Settings s;
    s.show();


    return a.exec();
}
