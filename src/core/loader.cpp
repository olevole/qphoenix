#include "loader.h"
#include "defines.h"
#include <QDir>
#include <QPluginLoader>
#include <QDebug>


QPModuleList QPModuleLoader::modules() {
    QPModuleList modules;
    mSearchPaths.removeDuplicates();
    foreach(QString path, mSearchPaths) {
        QDir dir(path);
        QStringList rel_paths = dir.entryList(QStringList() << "*.spec");
        foreach(QString rpath, rel_paths) {
            QPModule module;

            QPModuleData data = mParser.parse(dir.absoluteFilePath(rpath));
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
    qDebug() << "??????????" << modules.count();
    return modules;
}
