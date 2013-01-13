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
#include <QMap>

#include "abstractinfocontainer.h"


typedef AbstractInfoContainer Info;
typedef QMap<QString, QObject*> ModuleList;
typedef QMap<QString, AbstractInfoContainer*> InfoList;



/*!
 * \brief The MultiLoader class
 *
 * This class provide information and basic
 * load for modules.
 */
class MultiLoader {

public:
    MultiLoader(){}
    MultiLoader(const QStringList &paths) {
        addSearchPath(paths);
    }

//    --------------------------------------------

    void addSearchPath(const QString &path)
    { addSearchPath(QStringList() << path); }

    void addSearchPath(const QStringList &paths)
    { mSearchPaths += paths;    }

    QStringList searchPaths() const
    { return mSearchPaths; }

    void clearSearchPaths()
    { mSearchPaths.clear(); }

    void updateInfo();

//    --------------------------------------------

    ModuleList moduleList() {
        return mList;
    }

    InfoList infoList() const;
private:
    ModuleList mList;
    InfoList mInfoList;
    QStringList mModulesPath, mSearchPaths;
};


#endif // MULTILOADER_H
