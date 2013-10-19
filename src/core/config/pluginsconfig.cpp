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

#include "pluginsconfig.h"
#include "defines.h"
#include "iplugin.h"

#include <QTableWidget>
#include <QHBoxLayout>
#include <QSettings>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>

PluginsConfig::PluginsConfig(QWidget *parent)
    :QWidget(parent),
      mSettings(new QSettings(this)),
      mTable(new QTableWidget(this))
{
    QVBoxLayout *mainLayoit = new QVBoxLayout;
    mainLayoit->addWidget(mTable);

    this->setLayout(mainLayoit);

    mTable->setColumnCount(4);
    mTable->verticalHeader()->hide();

    mTable->horizontalHeader()->setStretchLastSection(true);
    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Enabled")));

    mTable->setColumnWidth(0, 70);
    mTable->setColumnWidth(1, 300);
    mTable->setColumnWidth(3, 70);

    updateTable();

    mSettings->beginGroup(QP_PLUGINS_CONFIG_GROUP);
}

QPPluginList *PluginsConfig::pluginsList() {
    qDebug() << "Plugins Count: " <<  mPlugins.size();
    return &mPlugins;
}

QStringList PluginsConfig::enabledPluginsList()  {
    QStringList lst;
    for (int i = 0; i < mTable->rowCount(); i++)
        if(mCheckboxList[i]->isChecked())
            lst << mTable->itemAt(i, 0)->text();

    return lst;
}

bool PluginsConfig::isEnabled(const int index) const {
    if(index >= mTable->rowCount())
        qFatal("Plugin index out of range");

    return mCheckboxList[index]->isChecked();
}

void PluginsConfig::save() {
    mSettings->setValue("EnabledPlugins", enabledPluginsList());
}

void PluginsConfig::read() {
    QStringList enabled = mSettings->value("EnabledPlugins").toStringList();

    for (int i = 0; i < mTable->rowCount(); ++i) {
        bool contains = enabled.contains(mTable->itemAt(0, i)->text());
        mCheckboxList[i]->setChecked(contains);
    }
}

void PluginsConfig::reset() {

}

void PluginsConfig::updateTable() {
    QPModuleLoader loader("plugins:");
    QPModuleList modules = loader.modules();

    foreach(QPModule plugin, modules) {

        IPlugin *iface = qobject_cast<IPlugin *>(plugin.instance);

        QPPlugin pl;
        pl.data = plugin.data;
        pl.instance = iface;

        mPlugins << pl;

        const int row = mTable->rowCount();
        mTable->insertRow(row);
        mTable->resize(100, 100);
        mTable->setRowHeight(row, 20);

        QStringList data;
        data << plugin.data.name << plugin.data.description << plugin.data.version;

        for (int i = 0; i < data.count(); ++i) {
            QString item_data = data[i];

            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(item_data);
            item->setFlags(item->flags() & (~(Qt::ItemIsEditable | Qt::ItemIsSelectable)));
            mTable->setItem(row, i, item);
        }

        QCheckBox *cb = new QCheckBox(this);
        mCheckboxList << cb;
        mTable->setCellWidget(row, 3, cb);
    }
    mTable->resizeColumnsToContents();
}
