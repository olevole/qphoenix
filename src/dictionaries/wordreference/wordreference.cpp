#include "wordreference.h"
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
#include <QJsonDocument>
#include <QJsonObject>


WordReference::WordReference(QObject *parent)
    :QObject(parent),
      mManager(new QNetworkAccessManager(this))
{
    setName("WordReference");

    first = "en";
    other << "ar" << "zh" << "cz" << "fr" << "gr" << "it"
          << "ja" << "ko" << "pl" << "pt" << "ro" << "es" << "tr";

}


DictionaryVariantList WordReference::query(const QString &text, const LanguagePair &pair)  {

    QJsonDocument doc = queryData(text, pair);

    QJsonObject root = doc.object().value("term0").toObject();

    QJsonObject principal = root.value("PrincipalTranslations").toObject();

    DictionaryVariantList lst;

    for (int i = 0; i < 20; i++) {

        QJsonObject orig = principal.value(QString::number(i)).toObject();

        if(orig.isEmpty()) break;

        QJsonObject oterm = orig.value("FirstTranslation").toObject();

        QString expl = oterm.value("term").toString();
        QString tr = oterm.value("sense").toString();

        lst << DictionaryVariant(Verb, text, expl, tr);
    }
   return lst;
}


QJsonDocument WordReference::queryData(const QString &text, const LanguagePair &pair) const {
    const QString langs = pair.first + pair.second;
    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").
            arg("284e7").arg(langs).arg(text);




    QEventLoop loop;

    QObject::connect(mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    QNetworkReply *reply  = mManager->get(QNetworkRequest(url));
    loop.exec();

    const QString  rawdata = reply->readAll();
    qDebug() << "QUERY URL: " << url.toString();
    return QJsonDocument::fromJson(rawdata.toUtf8());

}



QStringList WordReference::completions(const QString &str, const LanguagePair &pair) const {
    QJsonDocument doc = queryData(str, pair);

    QJsonObject root = doc.object().value("term0").toObject();

    QJsonObject principal = root.value("PrincipalTranslations").toObject();

    QStringList lst;

    for (int i = 0; i < 20; i++) {

        QJsonObject orig = principal.value(QString::number(i)).toObject();

        if(orig.isEmpty()) break;

        QJsonObject oterm = orig.value("FirstTranslation").toObject();

        QString expl = oterm.value("term").toString();

        lst << expl;
    }

   return lst;
}
