#include "http.h"

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
