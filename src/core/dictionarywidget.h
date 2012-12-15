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

#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include <QWidget>
#include "pluginapi.h"

using namespace Tools;

class DictionaryWidget : public QWidget, Api::DictionaryWidgetAPI, Api::MainWindowTabInterface
{
    Q_OBJECT
    Q_INTERFACES(Api::DictionaryWidgetAPI)
    Q_INTERFACES(Api::MainWindowTabInterface)
public:
    explicit DictionaryWidget(QWidget *parent = 0);
    Info *info() = 0;

    virtual QComboBox   *srcComboBox();
    virtual QComboBox   *resComboBox();
    virtual QLineEdit   *srcText();
    virtual QTextBrowser*resText();
    virtual QToolButton *swapButton();

    
signals:
    
public slots:
    
};

#endif // DICTIONARYWIDGET_H
