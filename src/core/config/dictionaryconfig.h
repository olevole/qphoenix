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

#include "api.h"
#include "loader.h"
#include <QWidget>
#include <QList>

#define QP_DEFAULT_RESULT_COUNT 15
#define QP_DICTIONARY_CONFIG_GROUP "Dictionaries"

class QTableWidget;
class QTabWidget;
class QCheckBox;
class QSpinBox;
class QLabel;
class QSettings;

struct QPDictionary {
    IDictionary *instance;
    QPModuleData data;
};

typedef QList<QPDictionary> QPDictionaryList;

class DictionaryConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    DictionaryConfig(QWidget *parent = 0);

    void save();
    void read();
    void reset();

    QPDictionaryList dictionaries();
    unsigned int maxResults();
private:
    QSettings *mSettings;
    QPModuleList mDictionaries;
    QPDictionaryList mConvertedDicts;
    QTableWidget *mTable;
    QTabWidget *mTabWidget;
    QSpinBox *mResultCountSpin;
    QLabel *mResultCountLabel;

    QList<QCheckBox *> mCheckBoxList;
};
