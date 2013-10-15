#include "wordreference.h"
#include "http.h"
#include <QObject>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>


QString WordReference::mApiKey = "284e7";
QString WordReference::mApiVer = "0.8";

WordReference::WordReference(QObject *parent)
    :QObject(parent)
{
}

QStringList WordReference::query(const QString &text, const QString &src_lang, const QString &dest_lang, unsigned int max_count)  {
    QJsonDocument doc = queryData(text, src_lang, dest_lang);
    QJsonObject root = doc.object().value("term0").toObject();
    QJsonObject principal = root.value("PrincipalTranslations").toObject();
    QStringList lst;

    // Parse principal translations
    for (int i = 0; i < 20; i++) {

        QJsonObject orig = principal.value(QString::number(i)).toObject();

        if(orig.isEmpty()) break;

        QJsonObject oterm = orig.value("OriginalTerm").toObject();

        QString src_term = oterm.value("term").toString();
        QString src_sense = oterm.value("sense").toString();

        QJsonObject oterm2 = orig.value("FirstTranslation").toObject();

        QString res_term = oterm2.value("term").toString();
        QString res_sense = oterm2.value("sense").toString();

        lst << QString(
                   "[b]%1 (%2)[/b]\n\n"
//                   "[i]%2[/i]\n\n"
                   "[u]%3[/u][b]%4[/b]"
                   ).arg(src_term, src_sense, res_sense, res_term);
    }
   return lst;
}

QJsonDocument WordReference::queryData(const QString &text, const QString &src_lang, const QString &dest_lang) const {
    const QByteArray html = text.toUtf8();
    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").arg(mApiKey, src_lang+dest_lang, html.toPercentEncoding());

    const QString  rawdata = HTTP::GET(url);
    return QJsonDocument::fromJson(rawdata.toUtf8());
}

QStringList WordReference::completions(const QString &str,const QString &src_lang, const QString &dest_lang) const {
    QJsonDocument doc = queryData(str, src_lang, dest_lang);
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
//   return QStringList() << "foo" << "bar";
}
