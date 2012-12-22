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

#include "trayicon.h"
#include <QtGui>
#include <QPushButton>

TrayIcon::TrayIcon(QObject *parent) :
    QObject(parent),
    button(new QPushButton)
{
//    this->setName("TrayIcon");
}

void TrayIcon::setMainWindowPTR(QObject *ptr) {
//    Api::MainWindowAPI *iface = qobject_cast<Api::MainWindowAPI *>(ptr);
//    iface->setCurrentTab(1);

//    QLabel l;

//    iface->toolbar()->addWidget(button);

}

void TrayIcon::setSettingsPTR(QObject *ptr) {

}



Q_EXPORT_PLUGIN2(trayicon, TrayIcon);
