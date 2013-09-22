#include "yandex_translator.h"
#include "http.h"
#include <QtGui>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QStringList YandexTranslator::mLangs = QStringList()    <<"en" <<"ru";
QString YandexTranslator::mApiKey = "trnsl.1.1.20130623T124051Z.0700cd74def1a0f5.a64b755e8f8f1312a82edd26c0bc6585be02c695";

YandexTranslator::YandexTranslator(QObject *parent)
    :QObject(parent)
{
    setName("Yandex");
    setUrl("http://translate.yandex.ru/");
}

QString YandexTranslator::translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {
    const QString  query = QString("key=%1&lang=%2-%3&text=%4").arg(mApiKey, src_lang, dest_lang, src_text);

    QUrl url("https://translate.yandex.net/api/v1.5/tr.json/translate");

    const QString  rawdata = HTTP::POST(url, query);

    QJsonObject obj = QJsonDocument::fromJson(rawdata.toUtf8()).object();

    const int code = obj.value("code").toDouble();
    const QString pair = obj.value("lang").toString();
    const QString text = obj.value("text").toArray()[0].toString();

    switch (code) {
    case 200:
        // Then ok
        break;
    case 401:
        qWarning("Invalid API Key!");
        break;
    case 402:
        qWarning("API KEY IS BANNED!!");
        break;
    case 403:
        qWarning("Call restriction limit is over!");
        break;
    case 404:
        qWarning("Char restriction limit is over!");
        break;
    case 413:
        qWarning("Translation text limit is over!");
        break;
    case 422:
        qWarning("Unable to translate text!");
        break;
    case 501:
        qWarning("Wrong translation direction");
    break;
    default:
        break;
    }
    return text;
}

QString YandexTranslator::detectLanguage(const QString &pattern) {
    const QString req = QString("key=%1&text=%4").arg(mApiKey, pattern);
    QUrl url("https://translate.yandex.net/api/v1.5/tr.json/detect");

    const QString reply =  HTTP::POST(url, req);
    QJsonObject obj = QJsonDocument::fromJson(reply.toUtf8()).object();
    return obj.value("lang").toString();
}
