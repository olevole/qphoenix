#include <QtMsgHandler>
#include <QFile>
#include <QIcon>
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "mainwindow.h"
#include "defines.h"
#include "languages.h"
#include "dictionaryconfig.h"
#include "querywrappers.h"
#include "dictionarywidget.h"
#include "idictionary.h"
#include "itranslator.h"
#include "dictionarytemplate.h"


void qpMsgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
#ifdef QP_DEBUG
    case QtDebugMsg:
        fprintf(stderr, "[Debug]:  %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
#endif
    case QtWarningMsg:
        fprintf(stderr, "[Warning]:  %s \n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[Critical]:  %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "[Fatal]: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    DictionaryTemplate t;
//    t.beginSection("Section Test");
//    t.addItem(QString("[b]%1[/b]\n\n[i]%2[/i]\n\n[u]%3[/u][b]%4[/b]").arg("Text1", "Text2", "Text3", "Text4"));
//    t.addItem("Hello!");

//    t.endSection();

//    qDebug() << t.toHtml();


    qInstallMessageHandler(qpMsgHandler);
    qRegisterMetaType<DictionaryVariantList>("DictionaryVariantList");

    QCoreApplication::setApplicationName(QP_APP_NAME);
    QCoreApplication::setApplicationVersion(QP_APP_VERSION);
    QCoreApplication::setOrganizationName(QP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(QP_ORG_DOMAIN);

    QDir::addSearchPath("plugins", QP_PLUGINS_PATH);
    QDir::addSearchPath("translators", QP_TRANSLATORS_PATH);
    QDir::addSearchPath("dictionaries", QP_DICTIONARIES_PATH);

    MainWindow mw;
    mw.show();
    mw.setWindowIcon(QP_ICON("dictionary"));

    return a.exec();
}
