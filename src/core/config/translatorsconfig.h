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
#include <QList>
#include <QComboBox>
#include <QDebug>
#include "iconfigpage.h"
#include "itranslator.h"
#include "loader.h"

#define QP_TRANSLATORS_CONFIG_GROUP "Translators"

class QLabel;
class QComboBox;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;
class QTabWidget;
class QCheckBox;
class QSpinBox;
class QSettings;

struct QPTranslator {
    ITranslator *instance;
    QPModuleData data;
};


class QPTranslatorsConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    explicit QPTranslatorsConfig(QWidget *parent = 0);
    ~QPTranslatorsConfig();

    void save();
    void read();
    void reset();

    QStringList getTranslatorsNames() const;

    QPTranslator currentTranslator();
public slots:
    void setTranslatorIndex(int idx);
private slots:
    void onIndexChange(const int i);
private:
    QLabel *mTranslatorLabel;
    QComboBox *mTranslatorComboBox;
    QGroupBox *mTranslatorGroupBox;
    QHBoxLayout *mTranslatorLayout;
    QGroupBox *mOptionsGroupBox;
    QHBoxLayout *mOptionsLayout;
    QVBoxLayout *mTab1;
    QTabWidget *mTabWidget;

    QSettings *mSettings;
    QPModuleList mModuleList;
signals:
    void translatorIndexChanged(int);
};
