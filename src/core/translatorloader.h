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

#ifndef TRANSLATORLOADER_H
#define TRANSLATORLOADER_H

#include <QObject>
#include <QMap>
#include <QPair>


#include "translatorinterface.h"
#include "abstractloader.h"

class QPluginLoader;


class TranslatorLoader : public QObject, AbstractLoader
{
    /* First key - name, second key - absolute path to
     * translator .so library
     */
    typedef QPair<QString, QString> TranslatorEntry;
    typedef QList<TranslatorEntry> TranslatorEntryList;
    Q_OBJECT
public:
    explicit TranslatorLoader(QObject *parent = 0);

    bool load(const int i);
    bool load(const QString &name);

    void addSearchPath(const QString &str) {
        addSearchPaths(QStringList() << str);
    }

    void addSearchPaths(const QStringList &lst) {
        mPaths << lst;
        update();
    }

    // List of available for load instances.
    QStringList list() const {

    }

    TranslatorInterface *instance(){}


protected:
    void update();
private:
    QStringList mPaths;
    TranslatorEntryList mDetectedList;
    QPluginLoader *mLoader;
};



#endif // TRANSLATORLOADER_H
