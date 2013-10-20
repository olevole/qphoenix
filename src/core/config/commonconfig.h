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

#include <QWidget>
#include "iconfigpage.h"

class QTabWidget;
class QCheckBox;
class QLabel;
class QComboBox;
class QSettings;


#define QP_COMMON_CONFIG_GROUP "Common"


class CommonConfig : public QWidget, public IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    explicit CommonConfig(QWidget *parent = 0);

    virtual void save();
    virtual void read();
    virtual void reset();

    bool getNativeNamesEnabled();
private:
    void createLanguagePage();
    void createNetworkPage();
private:
    QSettings *mSettings;
    QTabWidget *mTabWidget;

    QCheckBox *mUseNativeCheckbox;
    QComboBox *mLanguageCombobox;
    QLabel *mLanguageLabel;
};
