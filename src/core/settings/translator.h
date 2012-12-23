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

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QWidget>
#include "settingspageinterface.h"
#include "translatorloader.h"

class QLabel;
class QComboBox;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;

class Translator : public QWidget, SettingsPageInterface
{
    Q_OBJECT
    Q_INTERFACES(SettingsPageInterface)
public:
    explicit Translator(QWidget *parent = 0);
    void save() {}
    void read() {}
    void reset(){}

    void setLoader(const TranslatorLoader *ptr);
private:
    QLabel *mTranslatorLabel;
    QComboBox *mTranslatorComboBox;
    QGroupBox *mTranslatorGroupBox;
    QHBoxLayout *mTranslatorLayout;

    QGroupBox *mOptionsGroupBox;
    QHBoxLayout *mOptionsLayout;
};

#endif // TRANSLATOR_H
