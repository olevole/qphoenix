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

#include "defines.h"
#include "abstractinfocontainer.h"
#include "plugininterface.h"

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

namespace __private__ {

class Plugin {
public:
    explicit Plugin(const QString &path);
    QString name() const { return mName; }
    QString path() const { return mLoader.fileName(); }
    QPluginLoader *loader(){ return &mLoader;         }
private:
    Plugin();
    Plugin( const Plugin& );
    void operator=( const Plugin& );

    QString mName;
    QPluginLoader mLoader;
};

Plugin::Plugin(const QString &path) {
    mLoader.setFileName(path);


    if(!(mLoader.load())) {
        QP_DBG(mLoader.errorString());
        return;
    }

    QObject *obj = mLoader.instance();

    PluginInterface *iface =
            qobject_cast<PluginInterface *>(obj);

    if(iface != NULL)
        mName = iface->name();
    else
        QP_DBG("Plugin invalid!");
}




} // __private__



template<typename T>
class MultiLoader
{
public:

    explicit MultiLoader();
    T *instance() { return instanceAt(mCurrentInstance); }
    T *instanceAt(const int i);
    T *instanceAt(const QString &str);

    T *load(const int i);
    T *load(const QString &name) { return load(mNames.indexOf(name));}

    void loadAll();

    void unload(const int i);
    void unload(const QString &str);
    void unloadAll();

    inline bool isLoaded(const int i) { return mLoaderList.at(i)->isLoaded();}

    bool isLoaded(const QString &name);
    int count() const                               { return mNames.size(); }
    int countLoaded() const                         { return mLoadedCount;  }
    int currentInstance() const                     { return mCurrentInstance;}
    QStringList list() const                        { return mNames;        }

    void addSearchPath(const QString &path)         { mSearchPaths << QStringList(path); }
    void addSearchPath(const QStringList &paths)    { mSearchPaths << paths;}
    void clearSearchPaths()                         { mSearchPaths.clear(); }
    QStringList searchPaths() const                 { return mSearchPaths;  }

    void update(){}

protected:

    // Last loaded instance
    int mCurrentInstance;

    // Count of loaded instances
    int mLoadedCount;

    /*
     * Names of plugins. All information taken
     * from plugin interface.
     */
    QStringList mNames;

    /*
     * Paths where to search plugins
     */
    QStringList mPaths;

    /*
     * Absolute paths to all plugins
     */
    QStringList mPluginsPaths;
    QStringList mSearchPaths;

    QPluginLoaderList mLoaderList;
    QList<QObject *> mInstancesList;

};

/*
 * Implementation.Your captain obivious.
 */

template<typename T>

MultiLoader<T>::MultiLoader() {
    this->addSearchPath(QP_PLUGINS_PATH);
    this->update();
}

template<typename T>
bool MultiLoader<T>::isLoaded(const QString &name)  {
    const int i = mNames.indexOf(name);

    if(i < 0){
        QP_DBG("Item " + name + "does not exists!");
        return false;
    }
    return mLoaderList.at(i)->isLoaded();
}

template<typename T>
T *MultiLoader<T>::load(const int i)  {
    QPluginLoader *ldr = mLoaderList.at(i);
    if(!ldr->load()) {
        QP_DBG(ldr->errorString());
        return NULL;
    }
    return qobject_cast<T *>(ldr->instance());
}

#endif // MULTILOADER_H
