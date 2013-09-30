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
     */
    QObjectList list;
    foreach(QString module, abs) {
        QPluginLoader *l = new QPluginLoader(module, this);
        QObject *instance;

        if(l->load() && (instance = l->instance()) != NULL)
            list.append(instance);
        else
            qWarning() << "Couldn't load plugin: " << l->fileName() << "reason: " << l->errorString();
        delete l;
    }
    return list;
}

ModuleList NewLoader::modules() {
    ModuleList modules;
    mSearchPaths.removeDuplicates();
    foreach(QString path, mSearchPaths) {
        QDir dir(path);
        QStringList rel_paths = dir.entryList(QStringList() << "*.spec");
        foreach(QString rpath, rel_paths) {
            Module module;

            ModuleSpecData data = mParser.parse(dir.absoluteFilePath(rpath));
            const QString libpath = dir.absoluteFilePath(data.libname);
            QPluginLoader *l = new QPluginLoader(libpath, this);
            QObject *instance;

            if(l->load() && (instance = l->instance()) != NULL) {
                module.instance = instance;
                module.data = data;
                modules << module;
            } else {
                qWarning() << "Couldn't load plugin: " << l->fileName() << "reason: " << l->errorString();
            }
            delete l;
        }
    }
    return modules;
}
