/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

#ifndef MULTILOADER_H
#define MULTILOADER_H

#include <QStringList>
#include <QPluginLoader>
#include <QList>

typedef QList <QPluginLoader *> QPluginLoaderList;



//template<typename T>
//class Loader {
//public:
//    Loader() {

//    }

//    bool load();
//    void unload();

//    T *instance();

////    QString name() const { return mName; }
//    QString path() const { return mPath; }
//private:
//    QString mPath;
//    QPluginLoader *loader;
//};


template<typename T>
class MultiLoader
{
public:
    explicit MultiLoader(){}
    
    T *instance();
    T *instanceAt(const int i);

    T *load(const int i);
    T *load(const QString &name);
    void loadAll();

    void unload(const int i);
    void unload(const QString &str);
    void unloadAll();

    bool isLoaded(const int i);
    bool isLoaded(const QString &name);

    int count() const                               { return mNames.size(); }
    int countLoaded() const;
    int currentInstance() const;
    QStringList list() const                        { return mNames;        }

    void addSearchPath(const QString &path)         { mSearchPaths << QStringList(path); }
    void addSearchPath(const QStringList &paths)    { mSearchPaths << paths;}
    void clearSearchPaths()                         { mSearchPaths.clear(); }
    QStringList searchPaths() const                 { return mSearchPaths;  }

    void update();

protected:
    int mCurrentInstance;
    QStringList mNames;
    QStringList mPaths;
    QStringList mPluginsPaths;
    QStringList mSearchPaths;

    QPluginLoaderList mLoaderList;
private:
//    void update();
//    void

};

#endif // MULTILOADER_H
