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

typedef QMap<QString, QPluginLoader*> PluginList;


class MultiLoader {

public:
    /*!
     * \brief loadPlugins
     * \param paths paths to a plugins
     * \param lst list where to place a plugins
     * \return list of plugins names
     */
    static QStringList loadPlugins(const QStringList &paths, PluginList &lst);

    /*!
     * \brief loadPlugins
     * \param paths a dicrectory where to SEARCH for plugins
     * \param lst list where to place a plugins
     * \return list with plugins names
     */
    static QStringList loadPlugins(const QString &path, PluginList &lst);


private:
    //! This is only static class
    MultiLoader();

};





#endif // MULTILOADER_H
