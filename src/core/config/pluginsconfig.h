#ifndef PLUGINSCONFIG_H
#define PLUGINSCONFIG_H


#include "configpageinterface.h"
#include "info.h"
#include "loader.h"

#include <QWidget>
#include <QList>
#include <QCheckBox>


class QTableWidget;
class QHBoxLayout;

class PluginsConfig : public QWidget, ConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(ConfigPageInterface)

public:
    PluginsConfig(QWidget *parent = 0);

    ModuleList *pluginsList() {
        return &mPlugins;
    }

    QStringList enabledPluginsList();


    void save();
    void read();
    void reset();
protected:
    void updateTable();

private:
    QTableWidget *mTable;
    ModuleList mPlugins;
    QStringList mEnabledList;
};

#endif // PLUGINSCONFIG_H
