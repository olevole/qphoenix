#include "mainwindow.h"
#include <QApplication>

#include "config.h"
#include "translationwidget.h"
#include "dictionarywidget.h"
#include "defines.h"
#include "querywrappers.h"
#include "plugininterface.h"
#include "loader.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QCoreApplication::setApplicationName(QP_APP_NAME);
    QCoreApplication::setApplicationVersion(QP_APP_VERSION);
    QCoreApplication::setOrganizationName(QP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(QP_ORG_DOMAIN);

    QP_DBG("Trying to create MainWindow object....");

    MainWindow *mw = new MainWindow();

    mw->show();

    QP_DBG("Success!");
    QP_DBG(QP_PLUGINS_PATH);




    return a.exec();








}
