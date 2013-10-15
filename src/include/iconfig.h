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

#include <QtPlugin>
#include <QIcon>

class QWidget;


/*!
 * \brief The ConfigInterface class
 *
 * This interface allow plugins to access main
 * config dialog (add their own setting pages)
 */

class IConfig {
public:
    virtual ~IConfig() {}

    /*  Inserting Settings page into the main
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */
    virtual void addPage(QWidget *page, const QString &name, const QIcon &icon = QIcon()) = 0;

    /*!
     * \brief removePage removing page
     * \param page page to remove
     */
    virtual void removePage(QWidget *page) = 0;

    /*!
     * \brief pageAt returns page by index
     * \param index of page
     * \return page widget
     */
    virtual QWidget *pageAt(int i) = 0;
};

Q_DECLARE_INTERFACE(IConfig, "com.qphoenix.interfaces.configpage/1.0")

