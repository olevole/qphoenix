#include "mainwindow.h"
#include <QApplication>

#include "settings.h"
#include "translationwidget.h"
#include "dictionarywidget.h"
#include "translatorloader.h"
#include "defines.h"
#include "multiloader.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QCoreApplication::setApplicationName(QP_APP_NAME);
    QCoreApplication::setApplicationVersion(QP_APP_VERSION);
    QCoreApplication::setOrganizationName(QP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(QP_ORG_DOMAIN);



//    Foo b();


    QP_DBG("Trying to create MainWindow object....");

    MainWindow *mw = new MainWindow();

    mw->show();

    QP_DBG("Success!");




    return a.exec();
}
