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
#include "multiloader.h"
#include "defines.h"
#include "abstractinfocontainer.h"
#include "plugininterface.h"
#include <QDir>


void MultiLoader::updateInfo() {


    //! Getting paths for ALL modules
    mSearchPaths.removeDuplicates();
    foreach(QString path, mSearchPaths) {
        QDir dir(path);

//        mModulesPath << dir.entryList(QStringList() << QP_MODULE_SIGNATURE);

        QStringList files =  dir.entryList(QStringList() << QP_MODULE_SIGNATURE);
        QStringList abs;
        for(int i = 0; i < files.count(); i++)
            abs << dir.absoluteFilePath(files.at(i));

    }
    QP_DBG(mModulesPath);


    foreach(QString module, mModulesPath) {
        QPluginLoader *l = new QPluginLoader(module);

        QObject *obj;

        if(l->load() && (obj = l->instance()) != NULL) {
            AbstractInfoContainer *info =
                    qobject_cast<AbstractInfoContainer *>(obj);

            mInfoList.insert(info->name(), info);
            mList.insert(info->name(), obj);
            if(info == NULL) {
                QP_DBG("Unalbe to cast interface!");
                return;
            }
        } else {
            QP_DBG("Unable to load module!");
            QP_DBG(l->errorString());
            QP_DBG(l->fileName());
            delete l;
        }
    }
}
