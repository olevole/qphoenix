#ifndef ICONS_H
#define ICONS_H

#include <QObject>
#include <QIconEngineV2>
#include <QIcon>
#include <QDir>
#include "defines.h"

class Icons : public QObject
{
    Q_OBJECT
public:
    explicit Icons(QObject *parent = 0);

    static  QIcon flag(const QString &key) {
        QString path = QString("%1%2%3.ico").arg(QP_RESOURCES_PATH).arg(QDir::separator()).arg(key);
        return QIcon(path);
    }

};

#endif // ICONS_H
