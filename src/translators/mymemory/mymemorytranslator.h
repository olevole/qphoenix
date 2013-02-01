#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "itranslator.h"
#include "info.h"
//#include "qxtjson.h"
#include <QObject>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QtTest/QTest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtGui/QTextDocumentFragment>
#include <QtCore/QEventLoop>
#include <QtCore/QStringList>
#include <QtCore/QDebug>




class SleeperThread : public QThread
{
public:
static void msleep(unsigned long msecs)
{
QThread::msleep(msecs);
}
};




class MyMemoryTranslator : public QObject, ITranslator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.translators.mymemory")
    Q_INTERFACES(ITranslator)

private:
    QWidget *mConfigWidget;
    bool mLoaded;
public:
    MyMemoryTranslator(QObject *parent = 0);

    bool load() {
        if(!isLoaded()) {
            mConfigWidget = new QWidget;
            mLoaded = true;
            return true;
        }
        return false;
    }

    bool unload() {
        if(isLoaded()) {
            delete mConfigWidget;
            mLoaded = false;
            return true;
        }
        return false;
    }
    bool isLoaded() const {return mLoaded;}


    QWidget *configWidget() {
//        QCheckBox *cb = new QCheckBox;
//        cb->setText("Disable google?");

//        return cb;
        return new QCheckBox("test");

    }

//    bool isLinear() const{ return false; }

    LanguageTable table() const {
        QStringList english;

        english << "ru" << "de" << "es";

        QStringList russian;
        russian << "de" << "en";


        QStringList german;
        german << "ru" << "en" << "uz";

        QStringList spanish;
        spanish << "de" << "ru";

        LanguageTable myTable;
        myTable["en"] = english;
        myTable["ru"] = russian;
        myTable["de"] = german;
        myTable["es"] = spanish;

        return myTable;

        qDebug() << "Keys2: " << myTable.keys();



    }

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang);
};

#endif // MYMEMORYTRANSLATOR_H
