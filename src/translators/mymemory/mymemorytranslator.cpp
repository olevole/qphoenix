#include "mymemorytranslator.h"
#include <QtGui>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



#include <QtGlobal>
MyMemoryTranslator::MyMemoryTranslator(QObject *parent)
    :QObject(parent)
{
    setName("MyMemory");
    setUrl("http://mymemory.translated.net");

}



QString MyMemoryTranslator::translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {
    QByteArray html = src_text.toUtf8();

    html.replace("&", "&amp;");
    html.replace("<", "&lt;");
    html.replace(">", "&gt;");
    html.replace("\n", "<br>");

    QByteArray query = "v=1.0&format=html";
    query += "&langpair=" + src_lang.toLatin1() + "%7C" + dest_lang.toLatin1();
    query += "&q=" + html.toPercentEncoding();

    QUrl url("http://mymemory.translated.net/api/get");
    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", "Mozilla/5.0");
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    req.setRawHeader("Content-Length", QByteArray::number(query.size()));

    QNetworkAccessManager manager;
    QEventLoop loop;

    connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    QNetworkReply *reply  = manager.post(req, query);
    loop.exec();

    const QByteArray rawdata = reply->readAll();


    QJsonDocument doc;
    doc = QJsonDocument::fromBinaryData(rawdata);


    QJsonObject arr = doc.object();
    qDebug() << "OBJECT!" << arr.size();

//        QxtJSON parser;


//        QVariantMap map = parser.parse(QString::fromUtf8(rawdata.data())).toMap();
//        QVariantMap map2 = map["responseData"].toMap();

//        const QString result = map2["translatedText"].toString();

    return QString();//QTextDocumentFragment::fromHtml(result).toPlainText();
}
