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

#include "iconfigpage.h"
#include "api.h"
#include "loader.h"
#include <QWidget>
#include <QList>
#include <QCheckBox>

#define QP_PLUGINS_CONFIG_GROUP "Plugins"

class QTableWidget;
class QHBoxLayout;
class QPushButton;
class QSettings;

struct QPPlugin {
    IPlugin *instance;
    QPModuleData data;
};

typedef QList<QPPlugin> QPPluginList;

class PluginsConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    PluginsConfig(QWidget *parent = 0);

    QPPluginList *pluginsList();
    QStringList enabledPluginsList();

    bool isEnabled(const int index) const ;
    void save();
    void read();
    void reset();
protected:
    void updateTable();
private:
    QSettings *mSettings;
    QTableWidget *mTable;
    QPPluginList mPlugins;
    QList<QCheckBox *>mCheckboxList;
};
