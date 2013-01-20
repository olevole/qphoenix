#include "mainwindow.h"
#include "defines.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include "languages.h"

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


    MainWindow *mw = new MainWindow();

    mw->show();


    LanguageEngine engine;


    QString text = engine.languages()["uz"].nativeName();

    qDebug() <<  text;
    mw->setWindowTitle(text);

    return a.exec();
}
