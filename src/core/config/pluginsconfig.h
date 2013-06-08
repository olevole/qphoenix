#pragma once

#include "iconfigpage.h"
#include "info.h"
#include "loader.h"
#include <QWidget>
#include <QList>
#include <QCheckBox>

class QTableWidget;
class QHBoxLayout;
class QPushButton;

class PluginsConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    PluginsConfig(QWidget *parent = 0);

    QObjectList *pluginsList() {
        return &mPlugins;
    }
    QStringList enabledPluginsList();
    bool isEnabled(const int index) const ;
    void save();
    void read();
    void reset();
private slots:
    void configure();
protected:
    void updateTable();
private:
    QTableWidget *mTable;
    QPushButton *mCfgButton;
    QObjectList mPlugins;
    QStringList mEnabledList;

    QList<QCheckBox *>mCheckboxList;
};
