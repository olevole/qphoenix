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

#include "dictionaryconfig.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTabWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QSettings>

DictionaryConfig::DictionaryConfig(QWidget *parent)
    :QWidget(parent),
      mSettings(new QSettings(this)),
      mTable(new QTableWidget(this)),
      mTabWidget(new QTabWidget(this)),
      mResultCountSpin(new QSpinBox(this)),
      mResultCountLabel(new QLabel(tr("Maximum dictionary results to show"), this))
{
    QPModuleLoader ldr("dictionaries:");
    mDictionaries = ldr.modules();

    QVBoxLayout *tab1 = new QVBoxLayout;
    tab1->addWidget(mTable);

    QVBoxLayout *tab2 = new QVBoxLayout;

    QHBoxLayout *result_layout = new QHBoxLayout;
    result_layout->addWidget(mResultCountLabel);
    result_layout->addWidget(mResultCountSpin);
    tab2->addLayout(result_layout);
    tab2->addStretch();

    mTabWidget->addTab(new QWidget(this), "Dictionaries");
    mTabWidget->addTab(new QWidget(this), "Preferences");

    mTabWidget->widget(0)->setLayout(tab1);
    mTabWidget->widget(1)->setLayout(tab2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTabWidget);
    this->setLayout(mainLayout);

    mTable->setColumnCount(4);
    mTable->verticalHeader()->hide();
    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Enabled")));

    for (int i = 0; i < mDictionaries.count(); ++i) {
        QPModule module = mDictionaries[i];
        IDictionary *iface = qobject_cast<IDictionary *>(module.instance);
        iface->load();

        QPDictionary dict;
        dict.instance = iface;
        dict.data = module.data;

        mConvertedDicts.append(dict);

        mTable->insertRow(i);
        mTable->setRowHeight(i, 20);

        QStringList columns;
        columns << module.data.name << module.data.description << module.data.version;

        for (int j = 0; j < columns.size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(columns[j]);
            item->setFlags(item->flags() & (~(Qt::ItemIsEditable | Qt::ItemIsSelectable)));
            mTable->setItem(i, j, item);
        }
        QCheckBox *checkbox = new QCheckBox(this);
        mCheckBoxList << checkbox;
        checkbox->setChecked(true);
        mTable->setCellWidget(i, 3, checkbox);
    }
    mTable->resizeColumnsToContents();

    mSettings->beginGroup(QP_DICTIONARY_CONFIG_GROUP);
}

void DictionaryConfig::save() {
    mSettings->setValue("MaxResults", mResultCountSpin->value());
}

void DictionaryConfig::read() {
    const int index = mSettings->value("MaxResults", QP_DEFAULT_RESULT_COUNT).toInt();
    mResultCountSpin->setValue(index);
}

void DictionaryConfig::reset() {
    mResultCountSpin->setValue(QP_DEFAULT_RESULT_COUNT);
}

QPDictionaryList DictionaryConfig::dictionaries() {
    QPDictionaryList enabled;
    for (int i = 0; i < mConvertedDicts.count(); ++i) {
        if(mCheckBoxList.at(i)->isChecked())
            enabled.append(mConvertedDicts.at(i));
    }
    return enabled;
//    return mConvertedDicts;
}

unsigned int DictionaryConfig::maxResults() {
    return mResultCountSpin->value();
}
