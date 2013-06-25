#include "http.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

HTTP::HTTP(QObject *parent) :
    QObject(parent)
{
}

QByteArray HTTP::get(QUrl req){
    QNetworkAccessManager mManager;
    QEventLoop loop;

    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply  = mManager.get(QNetworkRequest(req));

    loop.exec();


    return reply->readAll();
}


QByteArray HTTP::post(const QUrl &url, const QString &data) {
    QByteArray _data = data.toUtf8();
    QNetworkAccessManager mManager;
    QEventLoop loop;


    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", "Mozilla/5.0");
    req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    req.setRawHeader("Content-Length", QByteArray::number(data.size()));


    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply  = mManager.post(req, _data);

    loop.exec();


    return reply->readAll();
}
