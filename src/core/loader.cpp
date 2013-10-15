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
            if(mParser.hasError())
                continue;
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
