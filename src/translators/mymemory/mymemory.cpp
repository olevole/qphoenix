#include "mymemory.h"
#include "http.h"
#include <QtGui>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>


QStringList MyMemory::mLangs = QStringList()   << "sq" <<"ar" <<"bg" <<"ca"
                                               <<"zh-CN" <<"zh-TW" <<"hr"
                                               <<"cs" <<"da" <<"nl" <<"en"
                                               <<"et" <<"tl" <<"fi" <<"fr"
                                               <<"gl" <<"de" <<"el" <<"iw"
                                               <<"hi" <<"hu" <<"id" <<"it"
                                               <<"ja" <<"ko" <<"lv" <<"lt"
                                               <<"mt" <<"no" <<"pl" <<"pt"
                                               <<"ro" <<"ru" <<"sr" <<"sk"
                                               <<"sl" <<"es" <<"sv" <<"th"
                                               <<"tr" <<"uk" <<"vi";


MyMemory::MyMemory(QObject *parent)
    :QObject(parent)
{
    setName("MyMemory");
    setUrl("http://mymemory.translated.net");
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



    QNetworkAccessManager manager;
    QEventLoop loop;

    connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));


    const QString  rawdata = HTTP::POST(url, query);

    QJsonObject obj = QJsonDocument::fromJson(rawdata.toUtf8()).object();
    QString res = obj.value("responseData").toObject().value("translatedText").toString();

    qDebug() << "You has been called mymemory!\n";
    return res;
}
