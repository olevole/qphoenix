#ifndef PLUGINSCONFIG_H
#define PLUGINSCONFIG_H


#include "configpageinterface.h"
#include "abstractinfocontainer.h"
#include "multiloader.h"

#include <QWidget>


class QTableWidget;
class QHBoxLayout;

class PluginsConfig : public QWidget, ConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(ConfigPageInterface)

public:
    PluginsConfig(QWidget *parent = 0);


    PluginList *getEnabledPlugins();

    void save();
    void read();
    void reset();
private:
    PluginList mPluginsList;
    QTableWidget *mTable;
};

#endif // PLUGINSCONFIG_H
