#ifndef DEFINES_H
#define DEFINES_H


#include <QDir>
#include <QString>

#define QP_APP_VERSION "0.01a"
#define QP_APP_NAME "QPhoenix"
#define QP_ORG_NAME "QPhoenix developers"
#define QP_ORG_DOMAIN "http://qphoenix.org"


#define QP_PREFIX QString("%1/%2").arg("${CMAKE_INSTALL_PREFIX}").arg(QDir::separator())

#define QP_PLUGINS_PATH QP_PREFIX  + "plugins"
#define QP_TRANSLATORS_PATH  QP_PREFIX + "translators"
#define QP_DICTIONARIES_PATH QP_PREFIX + "dictionaries"


#define QP_DEBUG_MODE

#define QP_PLUGIN_SIGNATURE "__qphoenix-1.0plugin___"


#ifdef QP_DEBUG_MODE
    #include <QDebug>
    #define QP_DBG(x) qDebug() << x
#else
    #define QP_DBG(x) Q_UNUSED(x)
#endif


#ifdef Q_OS_UNIX
    #define QP_PLUGIN_EXT ".so"
#endif

#ifdef Q_OS_WIN32
    #define QP_PLUGIN_EXT ".dll"
#endif


#endif // DEFINES_H
