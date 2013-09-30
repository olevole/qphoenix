#pragma once

#include <QObject>

/*!
 * \brief The HTTP class
 * Provide a blocking get and post functions
 * It's useful because QNetworkAccessManager
 * is a concurrent and you need to re-define
 * event loop in every plugin.
 */


class HTTP : public QObject
{
    Q_OBJECT
public:
    static QByteArray GET(QUrl req);
    static QByteArray POST(const QUrl &url, const QString &data);
private:
    HTTP(QObject *parent = 0);
    HTTP();
    HTTP(const HTTP&);
    HTTP& operator=(const HTTP&);
};

