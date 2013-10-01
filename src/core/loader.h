#pragma once

#include <QStringList>
#include <QObject>
#include <QList>
#include "specparser.h"

struct QPModule {
    QPModuleData data;
    QObject *instance;
};

typedef QList<QPModule>QPModuleList;

/*!
 * \brief The Loader class
 * ModuleLoader
 */

class QPPluginLoader : public QObject
{
    Q_OBJECT
public:
    QPPluginLoader(QObject *parent = 0) :QObject(parent) {}
    QPPluginLoader(const QString &path) {addSearchPath(path);}
    QPPluginLoader(const QStringList &paths) {addSearchPath(paths);}

    void addSearchPath(const QString &path) {addSearchPath(QStringList() << path);}
    void addSearchPath(const QStringList &paths) {mSearchPaths += paths;}
    QStringList searchPaths() const {return mSearchPaths;}
    void clearSearchPaths() {mSearchPaths.clear();}

    QPModuleList modules();
private:
    QStringList mSearchPaths;
    QPModuleSpecParser mParser;
};
