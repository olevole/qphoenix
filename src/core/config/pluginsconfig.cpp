#include "pluginsconfig.h"


#include <QTableWidget>
#include <QHBoxLayout>

PluginsConfig::PluginsConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this))
{
    this->setLayout(new QHBoxLayout);
    this->layout()->addWidget(mTable);


    mTable->setColumnCount(3);


}


void PluginsConfig::save() {

}

void PluginsConfig::read() {

}

void PluginsConfig::reset() {

}
