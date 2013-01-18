#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H



/*
 * This is a basic interface for ALL plugins
 */

#include "mainwindowinterface.h"
#include "configinterface.h"
#include "basemodule.h"



class PluginInterface : public BaseModule
{

public:
    virtual ~PluginInterface() {}

    /*!
     * \brief setMainWindowPTR
     * \param ptr a pointer to MainWindow class
     */
    virtual void setMainWindowPTR(MainWindowInterface *ptr) = 0;

    /*!
     * \brief setSettingsPTR
     * \param ptr a pointer to config dialog object
     */
    virtual void setSettingsPTR(ConfigInterface *ptr) = 0;
};



Q_DECLARE_INTERFACE(PluginInterface, "com.qphoenix.interfaces.plugin/1.0");



#endif // PLUGININTERFACE_H
