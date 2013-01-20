#include "mainwindow.h"
#include <QApplication>

#include "config.h"
#include "translationwidget.h"
#include "dictionarywidget.h"
#include "defines.h"
#include "querywrappers.h"
#include "plugininterface.h"
#include "loader.h"
#include "languages.h"
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QCoreApplication::setApplicationName(QP_APP_NAME);
    QCoreApplication::setApplicationVersion(QP_APP_VERSION);
    QCoreApplication::setOrganizationName(QP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(QP_ORG_DOMAIN);

    QDir::addSearchPath("plugins", QP_PLUGINS_PATH);
    QDir::addSearchPath("translators", QP_TRANSLATORS_PATH);
    QDir::addSearchPath("dictionaries", QP_DICTIONARIES_PATH);
    QDir::addSearchPath("l18n", QP_L18N_PATH);
    QDir::addSearchPath("resources", QP_RESOURCES_PATH);


    MainWindow *mw = new MainWindow();

    mw->show();




    qDebug() << "Name: " << LanguageFactory::list()["ru"].first;
    qDebug() << "Native name: " << LanguageFactory::list()["ru"].second.toUtf8();


    mw->setWindowTitle(LanguageFactory::list()["ru"].second);

    return a.exec();
}
