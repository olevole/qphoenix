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

#pragma once

#include <QString>
#include <QtPlugin>

class QObject;



/*!
 * \brief The IModule class
 *
 * This is a base class for ALL modules (translators, dictionaries, plugins)
 * Class IModule MUST be inherited by any kinds of modules.
 */

class IModule {
public:
    virtual ~IModule() {}


    /*!
     * \brief load
     * \return true module was successfully loaded, otherwise -false
     * Initialise plugin (prepare plugin to work). It means creating
     * widgets, loading configs, etc. Do it in this method INSTEAD
     * of consturctor!!!!
     */
    virtual bool load() = 0;

    /*!
     * \brief unload
     * \return true module was successfully unloaded, otherwise -false
     * Unload plugin (removing all widgets, etc)
     */

    virtual bool unload() = 0;


    /*!
     * \brief isLoaded
     * \return true if plugin is loaded, othervise - fasle
     */
    virtual bool isLoaded() const = 0;

};

Q_DECLARE_INTERFACE(IModule, "com.qphoenix.interfaces.imodule/1.0")
