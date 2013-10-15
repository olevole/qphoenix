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

#include "imodule.h"

/*!
 * \brief The PluginConnector struct
 * Structure with public pointers to plugin interfaces
 * mainwindow - Main Window interface
 * configdialog - Config dialog iface
 * translationwidget - Translator widget iface
 * dictionarywidget - Dictionary widget iface
 */

#include "imainwindow.h"
#include "iconfig.h"
#include "itranslationwidget.h"
#include "idictionarywidget.h"

struct PluginConnector
{
    IMainWindow *mainwindow;
    IConfig *configdialog;
    ITranslationWidget *translationwidget;
    IDictionaryWidget *dictionarywidget;
};


/*!
 * \brief The IPlugin class
 * Interface for plugins
 */
class IPlugin : public IModule
{

public:
    virtual ~IPlugin() {}

    /*!
     * \brief setPluginConnector
     * \param connector
     */
    virtual void setPluginConnector(PluginConnector connector) = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "com.qphoenix.interfaces.plugin/1.0");
