#include "mainwindow.h"
#include "defines.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include "languages.h"
#include "dictionaryconfig.h"
#include "querywrappers.h"
#include <QFile>
#include "dictionarywidget.h"
#include "idictionary.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<DictionaryVariantList>("DictionaryVariantList");


    QCoreApplication::setApplicationName(QP_APP_NAME);
    QCoreApplication::setApplicationVersion(QP_APP_VERSION);
    QCoreApplication::setOrganizationName(QP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(QP_ORG_DOMAIN);

    QDir::addSearchPath("plugins", QP_PLUGINS_PATH);
    QDir::addSearchPath("translators", QP_TRANSLATORS_PATH);
    QDir::addSearchPath("dictionaries", QP_DICTIONARIES_PATH);

    MainWindow *mw = new MainWindow();

    mw->show();
    mw->setWindowIcon(QP_ICON("dictionary"));


    return a.exec();
}
