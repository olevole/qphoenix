#include "pluginsconfig.h"
#include "defines.h"
#include "info.h"
#include "plugininterface.h"

#include <QTableWidget>
#include <QHBoxLayout>
#include <QSettings>
#include <QHeaderView>
#include <QDebug>

PluginsConfig::PluginsConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this))
{
    this->setLayout(new QHBoxLayout);
    this->layout()->addWidget(mTable);

    this->setName("Plugins");


    mTable->setColumnCount(4);
    mTable->verticalHeader()->hide();





    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Enabled?"));

    mTable->setColumnWidth(0, 70);
    mTable->setColumnWidth(1, 300);
    mTable->setColumnWidth(3, 70);

    updateTable();
}

QStringList PluginsConfig::enabledPluginsList()  {


    mEnabledList.clear();
    for (int i = 0; i < mTable->rowCount(); ++i) {
        QWidget *widget = mTable->cellWidget(i, 3);
        QCheckBox *checkbox = qobject_cast<QCheckBox *>(widget);


        if(checkbox->isChecked()) {
            mEnabledList << mTable->itemAt(i, 0)->text();
            qDebug() << "Checkbox is checked!";

        } else {
            qDebug() << "Checkbox isn't' checked!";
        }

    }

    return mEnabledList;
}




void PluginsConfig::save() {
    // Reading settings, yeah!
    QSettings s;

    s.beginGroup("Plugins");
    s.setValue("EnabledPlugins", enabledPluginsList());
    s.endGroup();

}

void PluginsConfig::read() {

    // Reading settings, yeah!
    QSettings s;
    QStringList enabled;

    s.beginGroup("Plugins");
    enabled = s.value("EnabledPlugins").toStringList();
    s.endGroup();


    for (int i = 0; i < mTable->rowCount(); ++i) {
        QWidget *widget = mTable->cellWidget(i, 3);
        QCheckBox *checkbox = qobject_cast<QCheckBox *>(widget);

        bool contains = enabled.contains(mTable->itemAt(0, i)->text());
        checkbox->setChecked(contains);

    }
}

void PluginsConfig::reset() {

}

void PluginsConfig::updateTable() {
    Loader loader("/tmp/qphoenix-build/src/plugins/trayicon");

    mPlugins = loader.modules();


    for (int i = 0; i < mPlugins.count(); ++i) {
        PluginInterface *iface = qobject_cast<PluginInterface *>(mPlugins.at(i));

        const int row = mTable->rowCount();
        mTable->insertRow(row);


        mTable->resize(100, 100);
        mTable->setRowHeight(row, 20);


        QStringList data;
        data << iface->name() << iface->description() << iface->version();



        for (int i = 0; i < data.count(); ++i) {
            QString item_data = data[i];

            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(item_data);
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            mTable->setItem(row, i, item);
        }

        mTable->setCellWidget(row, 3, new QCheckBox(mTable));

    }
}
