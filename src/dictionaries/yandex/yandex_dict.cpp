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


QString YandexDictionary::mApiKey = "dict.1.1.20131027T162417Z.02f762c5e8f46667.ce8d3c6adf6c5c6f3bf20ce0f9040dccae8ab082";

YandexDictionary::YandexDictionary(QObject *parent)
    :QObject(parent)
{
}

QStringList YandexDictionary::query(const QString &text, const QString &src_lang, const QString &dest_lang, unsigned int max_count)  {
    const QUrl url = QString("https://dictionary.yandex.net/api/v1/dicservice.json/lookup");
    const QString params = QString("key=%1&lang=%2-%3&text=%4").
            arg(mApiKey, src_lang, dest_lang, text.toUtf8().toPercentEncoding());

    const QString  rawdata = HTTP::POST(url, params);


    qDebug() << "Request URI: " << url;
    qDebug() << "Request parameters: " << params;
    qDebug() << "Reply data: " << rawdata;



    return QStringList();
}



QStringList YandexDictionary::completions(const QString &str,const QString &src_lang, const QString &dest_lang) const {
    return QStringList();
}
