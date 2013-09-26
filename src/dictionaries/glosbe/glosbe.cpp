#include "glosbe.h"
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



QStringList Glosbe::mLangs = QStringList()  << "ru" << "da" << "cs" << "it";\

LanguagePairList Glosbe::mPairList = LanguagePairList() << LanguagePair("it", "ru") << LanguagePair("ru", "it");

QString Glosbe::mApiKey = "284e7";
QString Glosbe::mApiVer = "0.8";

Glosbe::Glosbe(QObject *parent)
    :QObject(parent)
{
    setName("Glosbe");
    setDescription(tr("Word reference is a free online dictionary service"));
    setVersion(DICTIONARY_VERSION);
}


QStringList Glosbe::query(const QString &text, const LanguagePair &pair, unsigned int max_count)  {
    QJsonDocument doc = queryData(text, pair);
    QJsonObject root = doc.object().value("term0").toObject();
    QJsonObject principal = root.value("PrincipalTranslations").toObject();
    QStringList lst;

    for (int i = 0; i < 20; i++) {

        QJsonObject orig = principal.value(QString::number(i)).toObject();

        if(orig.isEmpty()) break;

        QJsonObject oterm = orig.value("OriginalTerm").toObject();

        QString src_term = oterm.value("term").toString();
        QString src_sense = oterm.value("sense").toString();

        QJsonObject oterm2 = orig.value("FirstTranslation").toObject();

        QString res_term = oterm2.value("term").toString();
        QString res_sense = oterm2.value("sense").toString();


        lst << QString("[b]%1[/b]\n\n[i]%2[/i]\n\n[u]%3[/u][b]%4[/b]").arg(src_term, src_sense, res_sense, res_term);

    }
   return lst;
}


QJsonDocument Glosbe::queryData(const QString &text, const LanguagePair &pair) const {
    const QString langs = pair.first + pair.second;
    const QByteArray html = text.toUtf8();
    const QUrl url = QString("http://api.Glosbe.com/%2/json/%3/%4").arg(mApiKey, langs, html.toPercentEncoding());
    //TODO: percent encoding fails!


    QNetworkAccessManager mManager;
    QEventLoop loop;
    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply  = mManager.get(QNetworkRequest(url));
    loop.exec();

    const QString  rawdata = reply->readAll();
    return QJsonDocument::fromJson(rawdata.toUtf8());
}



QStringList Glosbe::completions(const QString &str, const LanguagePair &pair) const {
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
}
