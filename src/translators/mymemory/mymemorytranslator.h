#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "translatorinterface.h"
#include "info.h"
#include "qxtjson.h"
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
        QByteArray html = src_text.toUtf8();

        html.replace("&", "&amp;");
        html.replace("<", "&lt;");
        html.replace(">", "&gt;");
        html.replace("\n", "<br>");

        QByteArray query = "v=1.0&format=html";
        query += "&langpair=" + src_lang.toLatin1() + "%7C" + dest_lang.toLatin1();
        query += "&q=" + html.toPercentEncoding();

        QUrl url("http://mymemory.translated.net/api/get");
        QNetworkRequest req(url);
        req.setRawHeader("User-Agent", "Mozilla/5.0");
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        req.setRawHeader("Content-Length", QByteArray::number(query.size()));

        QNetworkAccessManager manager;
        QEventLoop loop;

        connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

        QNetworkReply *reply  = manager.post(req, query);
        loop.exec();

        const QByteArray rawdata = reply->readAll();

        QxtJSON parser;


        QVariantMap map = parser.parse(QString::fromUtf8(rawdata.data())).toMap();
        QVariantMap map2 = map["responseData"].toMap();

        const QString result = map2["translatedText"].toString();

        return QTextDocumentFragment::fromHtml(result).toPlainText();
    }
};

#endif // MYMEMORYTRANSLATOR_H
