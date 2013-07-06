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

    /*!
     * \brief pluginsList
     * \return list of loaded plugin QObject's pointers
     */
    QObjectList *pluginsList() {
        return &mPlugins;
    }

    /*!
     * \brief enabledPluginsList
     * \return list of enabled plugins names
     */
    QStringList enabledPluginsList();

    /*!
     * \brief isEnabled
     * \param index index of plugin
     * \return true if plugin is enabled, false otherwise
     */
    bool isEnabled(const int index) const ;
    void save();
    void read();
    void reset();
protected:
    void updateTable();
private:
    QTableWidget *mTable;
    QObjectList mPlugins;
    QStringList mEnabledList;

    QList<QCheckBox *>mCheckboxList;
};
