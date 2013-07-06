#include "pluginsconfig.h"
#include "defines.h"
#include "info.h"
#include "iplugin.h"

#include <QTableWidget>
#include <QHBoxLayout>
#include <QSettings>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>

PluginsConfig::PluginsConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this))
{
    QVBoxLayout *mainLayoit = new QVBoxLayout;
    mainLayoit->addWidget(mTable);

    this->setLayout(mainLayoit);
    this->setName("Plugins");

    mTable->setColumnCount(4);
    mTable->verticalHeader()->hide();

    mTable->horizontalHeader()->setStretchLastSection(true);
    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem("*"));

    mTable->setColumnWidth(0, 70);
    mTable->setColumnWidth(1, 300);
    mTable->setColumnWidth(3, 70);

    updateTable();
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
    QSettings s;

    s.beginGroup("Plugins");
    s.setValue("EnabledPlugins", enabledPluginsList());
    s.endGroup();
}

void PluginsConfig::read() {
    QSettings s;
    QStringList enabled;

    s.beginGroup("Plugins");
    enabled = s.value("EnabledPlugins").toStringList();
    s.endGroup();

    for (int i = 0; i < mTable->rowCount(); ++i) {
        bool contains = enabled.contains(mTable->itemAt(0, i)->text());
        mCheckboxList[i]->setChecked(contains);
    }
}

void PluginsConfig::reset() {

}

void PluginsConfig::updateTable() {
    Loader loader("plugins:");

    mPlugins = loader.modules();

    for (int i = 0; i < mPlugins.count(); ++i) {
        IPlugin *iface = qobject_cast<IPlugin *>(mPlugins.at(i));

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
            item->setFlags(item->flags() & (~(Qt::ItemIsEditable | Qt::ItemIsSelectable)));
            mTable->setItem(row, i, item);
        }

        QCheckBox *cb = new QCheckBox(this);
        mCheckboxList << cb;
        mTable->setCellWidget(row, 3, cb);
    }
    mTable->resizeColumnsToContents();
}
