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

#include "mymemory.h"
#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>
#include <QTextDocumentFragment>
#include <QUrl>


MyMemory::MyMemory(QObject *parent)
    :QObject(parent)
{
}

QString MyMemory::translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {
    QByteArray html = src_text.toUtf8();

    html.replace("&", "&amp;");
    html.replace("<", "&lt;");
    html.replace(">", "&gt;");
    html.replace("\n", "<br>");

    QString query = "v=1.0&format=html";
    query += "&langpair=" + src_lang.toLatin1() + "%7C" + dest_lang.toLatin1();
    query += "&q=" + html.toPercentEncoding();

    QUrl url("http://mymemory.translated.net/api/get");

    const QString  rawdata = HTTP::POST(url, query);

    QJsonObject obj = QJsonDocument::fromJson(rawdata.toUtf8()).object();
    QString res = obj.value("responseData").toObject().value("translatedText").toString();

    return QTextDocumentFragment::fromHtml(res).toPlainText();
}
