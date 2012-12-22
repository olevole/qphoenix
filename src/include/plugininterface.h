#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H



/*
 * This is a basic interface for ALL plugins
 */

#include <QString>
#include "abstractinfocontainer.h"
#include "pluginapi.h"
#include "settingspageinterface.h"
#include "mainwindowinterface.h"




class PluginInterface : public AbstractInfoContainer
{
public:
    virtual ~PluginInterface() {}


    virtual void setMainWindowPTR(MainWindowInterface *ptr) = 0;
    virtual void setSettingsPTR(QObject *ptr) = 0;

private:


};



Q_DECLARE_INTERFACE(PluginInterface, "com.qphoenix.interfaces.plugin/1.0");



#endif // PLUGININTERFACE_H
