#include "wordreference.h"
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
#include <QtGui>


WordReference::WordReference(QObject *parent)
    :QObject(parent)
{
    setName("WordReference");
}


DictionaryVariantList WordReference::query(const LanguagePair &pair, const QString &text)  {
//    const QString langs = pair.first + pair.second;

//    const QUrl url = QString(" http://api.wordreference.com/%1/%2/%3/%4").
//            arg(version).arg(apikey).arg(langs).arg(text);

//    QNetworkRequest req(url);
//    req.setRawHeader("User-Agent", "Mozilla/5.0");
//    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
////        req.setRawHeader("Content-Length", QByteArray::number(text.size()));

//    QNetworkAccessManager manager;
//    QEventLoop loop;

//    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

//    QNetworkReply *reply  = manager.get(req);
//    loop.exec();


//    qDebug() << reply->readAll();

    DictionaryVariantList list;
//    list.append();


}

Q_EXPORT_PLUGIN2(wordreference, WordReference);
