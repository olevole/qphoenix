#pragma once

#include <QStringList>
#include <QObject>
#include <QList>
#include "specparser.h"

struct Module {
    ModuleSpecData data;
    QObject *instance;
};

typedef QList<Module>ModuleList;

/*!
 * \brief The Loader class
 * ModuleLoader
 */

class Loader : public QObject
{
    Q_OBJECT
public:
    Loader(QObject *parent = 0) :QObject(parent) {}
    Loader(const QString &path) {addSearchPath(path);}
    Loader(const QStringList &paths) {addSearchPath(paths);}

    void addSearchPath(const QString &path) {addSearchPath(QStringList() << path);}
    void addSearchPath(const QStringList &paths) {mSearchPaths += paths;}
    QStringList searchPaths() const {return mSearchPaths;}
    void clearSearchPaths() {mSearchPaths.clear();}

    QObjectList modules();
private:
    QStringList mSearchPaths;
};

class NewLoader : public QObject
{
    Q_OBJECT
public:
    NewLoader(QObject *parent = 0) :QObject(parent) {}
    NewLoader(const QString &path) {addSearchPath(path);}
    NewLoader(const QStringList &paths) {addSearchPath(paths);}

    void addSearchPath(const QString &path) {addSearchPath(QStringList() << path);}
    void addSearchPath(const QStringList &paths) {mSearchPaths += paths;}
    QStringList searchPaths() const {return mSearchPaths;}
    void clearSearchPaths() {mSearchPaths.clear();}

    ModuleList modules();
private:
    QStringList mSearchPaths;
    ModuleSpecParser mParser;
};
