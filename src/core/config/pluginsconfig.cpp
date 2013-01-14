#include "pluginsconfig.h"
#include "defines.h"


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


    mTable->setColumnCount(3);


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


    // Loading all plugins (for information)
//    QStringList names = MultiLoader::loadPlugins(QP_PLUGINS_PATH, mPluginsList);


    // Updating information about plugins

//    mTable->clear();

//    for(int i = 0; i < mPluginsList.count(); i++) {
//        const QString cur_name = names.at(i);
//        if(!enabled.contains(cur_name)) {
//            mPluginsList[cur_name]->unload();
//            mPluginsList.remove(cur_name);
//        }

//        Info *iface = qobject_cast<mPluginsList[]
//    }


}

void PluginsConfig::reset() {

}
