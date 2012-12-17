#ifndef DEFINES_H
#define DEFINES_H


#include <QDir>

#define QP_VERSION "0.01a"
#define QP_APP_NAME "QPhoenix"


#define QP_PREFIX "${CMAKE_INSTALL_PREFIX}" + QDir::separator()

#define QP_PLUGINS_PATH QP_PREFIX  + "plugins"
#define QP_TRANSLATORS_PATH  QP_PREFIX + "translators"
#define QP_DICTIONARIES_PATH QP_PREFIX + "dictionaries"

#define QP_DEBUG_MODE


#ifdef QP_DEBUG_MODE
    #include <QDebug>
    #define QP_DBG(x) qDebug() << x
#else
    #define QP_DBG(x) Q_UNUSED(x)
#endif


#endif // DEFINES_H
