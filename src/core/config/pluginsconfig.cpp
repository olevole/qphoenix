#include "pluginsconfig.h"
#include "defines.h"
#include "info.h"
#include "plugininterface.h"

#include <QTableWidget>
#include <QHBoxLayout>
#include <QSettings>

PluginsConfig::PluginsConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this))
{
    this->setLayout(new QHBoxLayout);
    this->layout()->addWidget(mTable);

    this->setName("Plugins");


    mTable->setColumnCount(4);


    Loader loader("/tmp/qphoenix-build/src/plugins/trayicon");

    mPlugins = loader.modules();


    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem(""));

    updateTable();
}


void PluginsConfig::save() {

}

void PluginsConfig::read() {

    // Reading settings, yeah!
    QSettings s;
    QStringList enabled;

    s.beginGroup("Plugins");
    enabled = s.value("EnabledPlugins").toStringList();
    s.endGroup();





}

void PluginsConfig::reset() {

}

void PluginsConfig::updateTable() {
//    mTable->clear();



    for (int i = 0; i < mPlugins.count(); ++i) {
        PluginInterface *iface = qobject_cast<PluginInterface *>(mPlugins.at(i));

        const int row = mTable->rowCount();
        mTable->insertRow(row);

        mTable->setItem(row, 0, new QTableWidgetItem(iface->name()));
        mTable->setItem(row, 1, new QTableWidgetItem(iface->description()));
        mTable->setItem(row, 2, new QTableWidgetItem(iface->version()));


        QP_DBG("++++++++++++++++++++++++++++++");
        QP_DBG(iface->name());
    }
}
