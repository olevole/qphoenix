/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

#include "yandex_translator.h"
#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>

QString YandexTranslator::mApiKey = "trnsl.1.1.20130623T124051Z.0700cd74def1a0f5.a64b755e8f8f1312a82edd26c0bc6585be02c695";

YandexTranslator::YandexTranslator(QObject *parent)
    :QObject(parent)
{
}

QString YandexTranslator::translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {
    const QString  query = QString("key=%1&lang=%2-%3&text=%4").arg(mApiKey, src_lang, dest_lang, src_text);

    QUrl url("https://translate.yandex.net/api/v1.5/tr.json/translate");

    const QString  rawdata = HTTP::POST(url, query);

    QJsonObject obj = QJsonDocument::fromJson(rawdata.toUtf8()).object();

    const int code = obj.value("code").toDouble();
    const QString pair = obj.value("lang").toString();
    const QString text = obj.value("text").toArray().first().toString();

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
