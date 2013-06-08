#pragma once

#include <QStringList>
#include <QObject>
#include <QList>

//typedef QList<QObject *> ModuleList;

class Loader : public QObject
{
    Q_OBJECT
public:
    Loader(QObject *parent = 0) :QObject(parent){}

    Loader(const QString &path)
    { addSearchPath(path);  }

    Loader(const QStringList &paths)
    { addSearchPath(paths); }

    // ---------------------------------------------------------

    void addSearchPath(const QString &path)
    { addSearchPath(QStringList() << path); }
    void addSearchPath(const QStringList &paths)
    { mSearchPaths += paths; }

    QStringList searchPaths() const
    { return mSearchPaths; }

    void clearSearchPaths()
    { mSearchPaths.clear(); }

    // ---------------------------------------------------------

    QObjectList modules();
//    void update();
private:
    QStringList mSearchPaths;
};
