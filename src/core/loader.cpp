#include "loader.h"
#include "defines.h"
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

QObjectList Loader::modules() {

    /*
     * Getting absolute paths of all modules
     */

    mSearchPaths.removeDuplicates();
    QStringList abs;
    for (int i = 0; i < mSearchPaths.count()/* - 1*/; i++) {
        QString path = mSearchPaths.at(i);
        QDir dir(path);
        QStringList rel;
        rel << dir.entryList(QStringList() << QP_MODULE_SIGNATURE);
        for (int j = 0; j < rel.count(); j++) {
            abs << dir.absoluteFilePath(rel.at(j));
        }
    }

    /*
     * Now we have a list with absolute paths to EACH plugin
     * Let's try load them
     */
    QObjectList list;
    foreach(QString module, abs) {
        QPluginLoader *l = new QPluginLoader(module, this);
        QObject *instance;


        if(l->load() && (instance = l->instance()) != NULL)
            list.append(instance);
        else
            qWarning() << "Couldn't load plugin: " << l->fileName() << l->errorString();
    }
    return list;
}
