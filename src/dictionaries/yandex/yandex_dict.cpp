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

#include "yandex_dict.h"
#include "http.h"
#include <QObject>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>

#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>


QString YandexDictionary::mApiKey = "dict.1.1.20131027T162417Z.02f762c5e8f46667.ce8d3c6adf6c5c6f3bf20ce0f9040dccae8ab082";

YandexDictionary::YandexDictionary(QObject *parent)
    :QObject(parent)
{
}

QStringList YandexDictionary::query(const QString &text, const QString &src_lang, const QString &dest_lang, unsigned int max_count)  {
    const QString url = "https://dictionary.yandex.net/api/v1/dicservice.json/lookup";
    const QString request = QString("%1?key=%2&lang=%3-%4&text=%5").
            arg(url, mApiKey, src_lang, dest_lang, text.toUtf8().toPercentEncoding());

    const QString  rawdata = HTTP::GET(request);

    QJsonDocument doc = QJsonDocument::fromJson(rawdata.toUtf8());

    QJsonArray def = doc.object().value("def").toArray();
    QStringList reply;
    for (int i = 0; i < def.size(); ++i) {
        const QString ret = parseTree(def.takeAt(i).toObject(), true);
        if(!ret.isEmpty())
            reply << ret;
    }
    return reply;
}


QString YandexDictionary::parseTree(QJsonObject root, bool header) {
    QString buf;

    const QString text = root.value("text").toString();
    const QString pos = root.value("pos").toString();

    if(!text.isEmpty()) {
        if(header)
            buf += QString("[b]%1[/b] ").arg(text);
        else
            buf += text;
    }

    if(!pos.isEmpty())
        buf += QString("([i]%1[/i])").arg(pos);

    if(!pos.isEmpty() || !text.isEmpty())
        buf += "\n";


    QJsonArray tr = root.value("tr").toArray();
    foreach(QJsonValue val, tr)
        buf += parseTree(val.toObject());


    QJsonArray mean = root.value("mean").toArray();
    foreach(QJsonValue val, mean)
        buf += parseTree(val.toObject());

    QJsonArray syn = root.value("syn").toArray();
    foreach(QJsonValue val, syn)
        buf += parseTree(val.toObject());

    QJsonArray ex = root.value("ex").toArray();
    foreach(QJsonValue val, ex)
        buf += parseTree(val.toObject());


    return buf;
}



QStringList YandexDictionary::completions(const QString &str,const QString &src_lang, const QString &dest_lang) const {
    return QStringList();
}
