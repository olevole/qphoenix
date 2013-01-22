#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "../../include/translatorinterface.h"
#include "../../include/info.h"
#include <QObject>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QtTest/QTest>



class SleeperThread : public QThread
{
public:
static void msleep(unsigned long msecs)
{
QThread::msleep(msecs);
}
};




class MyMemoryTranslator : public QObject, TranslatorInterface
{
    Q_OBJECT
    Q_INTERFACES(TranslatorInterface)
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

    bool isLinear() const{ return false; }

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

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {
        qDebug() << "SLEEP STARTED";

        SleeperThread t;t.msleep(10002);
        qDebug() << "SLEEP FINISHED";
        return QString("Result text | " + src_text);
    }
};

#endif // MYMEMORYTRANSLATOR_H
