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

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
//#include "../../include/plugininterface.h"
#include "../../include/plugininterface.h"

#include "../../include/basemodule.h"


class QPushButton;

class TrayIcon : public QObject, PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_INTERFACES(BaseModule)
    Q_INTERFACES(AbstractInfoContainer)

public:
    explicit TrayIcon(QObject *parent = 0);    
    void setMainWindowPTR(MainWindowInterface *ptr);

    void setSettingsPTR(ConfigInterface *ptr);

    bool init();
    QString errorString() const {}

private:
    QPushButton *button;
};

#endif // TRAYICON_H
