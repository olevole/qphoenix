#include "mainwindow.h"
#include "defines.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include "languages.h"
#include "tools.h"

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




    QStringList lst1, lst2;
    lst1 << "test" <<"blablabla" <<"bla";
    lst2 << "test" <<"bababa" <<"bla";



    qDebug() << "TOOLS TEST: " << Tools::intersects(lst1,lst2);


    return a.exec();
}
