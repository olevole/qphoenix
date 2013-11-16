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

#include "wordreference.h"
#include "http.h"
#include <QObject>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>

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

    for(int i = 0;;i++) {
        QJsonObject variant = principal.value(QString::number(i)).toObject();
        if(variant.isEmpty())
            break;
        lst << parseVariant(variant);
    }

    lst.removeDuplicates();

    return lst;
}

QString WordReference::parseVariant(QJsonObject obj) const {
    QString data;

    const QJsonObject first = obj.take("OriginalTerm").toObject();
    const QString first_term = first.value("term").toString();
    const QString first_sense = first.value("sense").toString();
    const QString first_pos = first.value("POS").toString();

    data += QString("[b]%1[/b] [u]%2[/u] (%3)\n").arg(first_term, first_pos, first_sense);


    for(QJsonObject::const_iterator it = obj.begin(); it != obj.end(); it++) {
        QJsonObject variant = it.value().toObject();

        const QString term = variant.value("term").toString();
        const QString sense = variant.value("sense").toString();
        const QString pos = variant.value("POS").toString();

        data += QString("[i]%1[/i]\t\t%2 [u]%3[/u]\n").arg(term, sense, pos);
    }

    return data;
}

QJsonDocument WordReference::queryData(const QString &text, const QString &src_lang, const QString &dest_lang) const {
    const QByteArray html = text.toUtf8();
    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").arg(mApiKey, src_lang+dest_lang, html.toPercentEncoding());

    const QString  rawdata = HTTP::GET(url);
    return QJsonDocument::fromJson(rawdata.toUtf8());
}

QStringList WordReference::completions(const QString &str,const QString &src_lang, const QString &dest_lang) const {
    return QStringList() << "test" << "tester" << "testing";
}
