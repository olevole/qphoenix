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
    const QString langs = pair.first + pair.second;

    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").
            arg(apikey).arg(langs).arg(text);

    QNetworkRequest req(url);
    QNetworkAccessManager manager;
    QEventLoop loop;

    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    QNetworkReply *reply  = manager.get(req);
    loop.exec();


    qDebug() << reply->readAll() << "URL: " << url.toString();

    DictionaryVariantList list;

    DictionaryVariant v(Verb, "test", "A testing of subject", "Тестирование чего-либо");
    list.append(v);
    return list;


    return parse(reply->readAll());


}

DictionaryVariantList WordReference::parse(const QByteArray content) const {

}

Q_EXPORT_PLUGIN2(wordreference, WordReference);
