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
#include <QUrl>


QString YandexDictionary::mApiKey = "284e7";
QString YandexDictionary::mApiVer = "0.8";

YandexDictionary::YandexDictionary(QObject *parent)
    :QObject(parent)
{
}

QStringList YandexDictionary::query(const QString &text, const QString &src_lang, const QString &dest_lang, unsigned int max_count)  {
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

QJsonDocument YandexDictionary::queryData(const QString &text, const QString &src_lang, const QString &dest_lang) const {
    const QByteArray html = text.toUtf8();
    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").arg(mApiKey, src_lang+dest_lang, html.toPercentEncoding());

    const QString  rawdata = HTTP::GET(url);
    return QJsonDocument::fromJson(rawdata.toUtf8());
}

QStringList YandexDictionary::completions(const QString &str,const QString &src_lang, const QString &dest_lang) const {
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
}
