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

class QPModuleLoader : public QObject
{
    Q_OBJECT
public:
    QPModuleLoader(QObject *parent = 0) :QObject(parent) {}
    QPModuleLoader(const QString &path) {addSearchPath(path);}
    QPModuleLoader(const QStringList &paths) {addSearchPath(paths);}

    void addSearchPath(const QString &path) {addSearchPath(QStringList() << path);}
    void addSearchPath(const QStringList &paths) {mSearchPaths += paths;}
    QStringList searchPaths() const {return mSearchPaths;}
    void clearSearchPaths() {mSearchPaths.clear();}

    QPModuleList modules();
private:
    QStringList mSearchPaths;
    QPModuleSpecParser mParser;
};
