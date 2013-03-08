#ifndef HTTP_H
#define HTTP_H

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
    explicit HTTP(QObject *parent = 0);

    static QByteArray get( QUrl req);
//    static QByteArray post(const QUrl &req, QByteArray &data) const;

};

#endif // HTTP_H
