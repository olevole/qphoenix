#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H



/*
 * This is a basic interface for ALL plugins
 */

#include <QString>
#include "abstractinfocontainer.h"
#include "pluginapi.h"
#include "settingsinterface.h"



namespace Api {

class PluginInterface : public AbstractInfoContainer
{
public:
    virtual ~PluginInterface() {}

//    virtual void load() = 0;
//    virtual void unload() = 0;

    virtual void setMainWindowPTR(QObject *ptr) = 0;
    virtual void setSettingsPTR(QObject *ptr) = 0;
private:


};


} // end Api namespace

Q_DECLARE_INTERFACE(Api::PluginInterface, "com.qphoenix.interfaces.plugin/1.0");



#endif // PLUGININTERFACE_H
