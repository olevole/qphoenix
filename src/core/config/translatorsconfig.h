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
#include <QList>
#include "iconfigpage.h"
#include "itranslator.h"
#include <QComboBox>

class QLabel;
class QComboBox;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;
class QTabWidget;
class QCheckBox;
class QSpinBox;

class TranslatorsConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    explicit TranslatorsConfig(QWidget *parent = 0);

    void save() {}
    void read() {}
    void reset(){}

    QComboBox *translatorComboBox() { return mTranslatorComboBox;}


    ITranslator *currentTranslator() {
        if(mTranslatorComboBox->currentIndex() > -1)
            return mTranslatorsList[mTranslatorComboBox->currentIndex()];
        else
            return NULL;
    }

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

    QList <ITranslator *>mTranslatorsList;


    QTabWidget *mTabWidget;
};

#endif // TRANSLATOR_H
