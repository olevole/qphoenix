#pragma once

#include "iconfigpage.h"
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
    QPModuleList *pluginsList() {
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
    QString name() const{return "";}
    QIcon icon() const{return QIcon("");}
protected:
    void updateTable();
private:
    QTableWidget *mTable;
    QPModuleList mPlugins;
    QStringList mEnabledList;

    QList<QCheckBox *>mCheckboxList;
};
