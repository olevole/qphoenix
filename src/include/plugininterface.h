#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H



/*
 * This is a basic interface for ALL plugins
 */

#include "abstractinfocontainer.h"
#include "settingsinterface.h"
#include "mainwindowinterface.h"




class PluginInterface : public AbstractInfoContainer
{
public:
    virtual ~PluginInterface() {}

    virtual void setMainWindowPTR(MainWindowInterface *ptr) = 0;
    virtual void setSettingsPTR(SettingsInterface *ptr) = 0;
};



Q_DECLARE_INTERFACE(PluginInterface, "com.qphoenix.interfaces.plugin/1.0");



#endif // PLUGININTERFACE_H
