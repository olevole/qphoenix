#include "wordreference.h"
#include "http.h"
#include <QObject>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextDocumentFragment>
#include <QEventLoop>
#include <QStringList>
#include <QDebug>
#include <QtGui>
#include <QJsonDocument>
#include <QJsonObject>



QStringList WordReference::mLangs = QStringList()  << "ar" << "zh" << "cz" << "fr" << "gr" << "it"
                                                           << "ja" << "ko" << "pl" << "pt" << "ro" << "es" << "tr";
QString WordReference::mApiKey = "284e7";
QString WordReference::mApiVer = "0.8";

WordReference::WordReference(QObject *parent)
    :QObject(parent)
{
    setName("WordReference");
}


DictionaryVariantList WordReference::query(const QString &text, const LanguagePair &pair, const int max_count)  {
    QJsonDocument doc = queryData(text, pair);
    QJsonObject root = doc.object().value("term0").toObject();
    QJsonObject principal = root.value("PrincipalTranslations").toObject();
    DictionaryVariantList lst;

    for (int i = 0; i < 20; i++) {

        QJsonObject orig = principal.value(QString::number(i)).toObject();

        if(orig.isEmpty()) break;

        QJsonObject oterm = orig.value("OriginalTerm").toObject();

        QString src_term = oterm.value("term").toString();
        QString src_sense = oterm.value("sense").toString();

        QJsonObject oterm2 = orig.value("FirstTranslation").toObject();

        QString res_term = oterm2.value("term").toString();
        QString res_sense = oterm2.value("sense").toString();



        lst << DictionaryVariant(src_term, res_term, src_sense, res_sense);
    }
   return lst;
}


QJsonDocument WordReference::queryData(const QString &text, const LanguagePair &pair) const {
    const QString langs = pair.first + pair.second;
    const QByteArray html = text.toUtf8();
    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").arg(mApiKey, langs, html.toPercentEncoding());
    //TODO: percent encoding fails!


    QNetworkAccessManager mManager;
    QEventLoop loop;
    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply  = mManager.get(QNetworkRequest(url));
    loop.exec();

    const QString  rawdata = reply->readAll();
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
   lst.prepend(str);
   return lst;
//    return QStringList() << "pills" << "louis" << "zoey" << "heavy" << "medic" << "peers" << "cheers";
}
