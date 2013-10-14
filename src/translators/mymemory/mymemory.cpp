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
