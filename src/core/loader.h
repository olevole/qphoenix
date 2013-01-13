#ifndef LOADER_H
#define LOADER_H

#include <QStringList>
#include <QObject>
#include <QList>

typedef QList<QObject *> ModuleList;

class Loader
{
public:
    Loader() {}

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


    ModuleList modules();
//    void update();
private:
    QStringList mSearchPaths;



};

#endif // LOADER_H
