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
        qDebug() << "ITer no: " << i;
    }

    // Parse principal translations
//    for (int i = 0; i < principal.count(); i++) {

//        QJsonObject orig = principal[i].toObject();

//        if(orig.isEmpty()) break;

//        QJsonObject oterm = orig.value("OriginalTerm").toObject();

//        QString src_term = oterm.value("term").toString();
//        QString src_sense = oterm.value("sense").toString();

//        QJsonObject oterm2 = orig.value("FirstTranslation").toObject();

//        QString res_term = oterm2.value("term").toString();
//        QString res_sense = oterm2.value("sense").toString();

//        lst << QString(
//                   "[b]%1 (%2)[/b]\n\n"
////                   "[i]%2[/i]\n\n"
//                   "[u]%3[/u][b]%4[/b]"
//                   ).
//               arg(src_term,
//                   src_sense,
//                   res_sense,
//                   res_term);
//    }
   return lst;
}

QString WordReference::parseVariant(QJsonObject obj) const {
    QString data;


    //Parsing first element
//    const QString first = QString()
//    obj.ta

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

//        data += variant.value("term").toString() + "\n";
//        data += variant.value("sense").toString() + "\n\n";

    }

//    data += obj.value("Note").toString() + "\n\n\n";
    return data;
//    return obj.te
}

QJsonDocument WordReference::queryData(const QString &text, const QString &src_lang, const QString &dest_lang) const {
    const QByteArray html = text.toUtf8();
    const QUrl url = QString("http://api.wordreference.com/%2/json/%3/%4").arg(mApiKey, src_lang+dest_lang, html.toPercentEncoding());

    const QString  rawdata = HTTP::GET(url);
    return QJsonDocument::fromJson(rawdata.toUtf8());
}

QStringList WordReference::completions(const QString &str,const QString &src_lang, const QString &dest_lang) const {
//    QJsonDocument doc = queryData(str, src_lang, dest_lang);
//    qDebug() << "JSON" << doc.toJson();
//    QJsonObject root = doc.object().value("term0").toObject();
//    QJsonObject principal = root.value("PrincipalTranslations").toObject();

//    QStringList lst;

//    for (int i = 0; i < 20; i++) {
//        QJsonObject orig = principal.value(QString::number(i)).toObject();
//        if(orig.isEmpty()) break;
//        QJsonObject oterm = orig.value("FirstTranslation").toObject();
//        QString expl = oterm.value("term").toString();
//        lst << expl;
//    }
//   lst.prepend(str);
//   return lst;
    return QStringList();
}
