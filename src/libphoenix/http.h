#ifndef HTTP_H
#define HTTP_H

#include <QObject>

class HTTP : public QObject
{
    Q_OBJECT
public:
    explicit HTTP(QObject *parent = 0);

    QString get(const QUrl &req) const;
//    QString post(const QUrl &req, QByteArray ) const;

    
signals:
    
public slots:
    
};

#endif // HTTP_H
