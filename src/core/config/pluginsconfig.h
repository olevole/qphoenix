#pragma once

#include "iconfigpage.h"
#include "api.h"
#include "loader.h"
#include <QWidget>
#include <QList>
#include <QCheckBox>

class QTableWidget;
class QHBoxLayout;
class QPushButton;

struct QPPlugin {
    IPlugin *instance;
    QPModuleData data;
};

typedef QList<QPPlugin> QPPluginList;

class PluginsConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    PluginsConfig(QWidget *parent = 0);

    QPPluginList *pluginsList();
    QStringList enabledPluginsList();

    bool isEnabled(const int index) const ;
    void save();
    void read();
    void reset();
protected:
    void updateTable();
private:
    QTableWidget *mTable;
    QPPluginList mPlugins;
    QList<QCheckBox *>mCheckboxList;
};
