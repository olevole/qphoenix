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

#include "translatorloader.h"
#include "defines.h"
#include <QPluginLoader>

TranslatorLoader::TranslatorLoader(QObject *parent) :
    QObject(parent),
    mLoader(new QPluginLoader(this))
{

}


bool TranslatorLoader::load(const int i) {

}

bool TranslatorLoader::load(const QString &name) {

}

void TranslatorLoader::update() {
    QStringList dump;
    QString path;
    QDir dir;

    /*
     * Gettings list of all available plugins in following directories.
     */
    foreach(path, mPaths) {
        dir.setPath(path);
        dump << dir.entryList(QStringList() << QP_PLUGIN_EXT);
    }

    /*
     * Okay, then, let's get their names
     */

    foreach(path, dump) {
        mLoader->setFileName(path);
        if(!mLoader->load()) {
            QP_DBG("Unable to load translator!");
        } else {
            QObject *obj = mLoader->instance();
            TranslatorInterface *iface = qobject_cast<TranslatorInterface *>(obj);

            if(iface == NULL) {
                QP_DBG("Unable to cast interface.");
                break; // TODO: Check it!
            }
            TranslatorEntry e;
            e.first = iface->name();
            e.second = path;

            mDetectedList << e;

            mLoader->unload();
        }
    }
}
