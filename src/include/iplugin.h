#pragma once


/*
 * This is a basic interface for ALL plugins
 */

#include "imainwindow.h"
#include "iconfig.h"
#include "imodule.h"
#include "pluginconnector.h"

class IPlugin : public IModule
{

public:
    virtual ~IPlugin() {}

//    /*!
//     * \brief setMainWindowPTR
//     * \param ptr a pointer to MainWindow class
//     */
//    virtual void setMainWindowPTR(IMainWindow *ptr) = 0;

//    /*!
//     * \brief setSettingsPTR
//     * \param ptr a pointer to config dialog object
//     */
//    virtual void setSettingsPTR(IConfig *ptr) = 0;

    /*!
     * \brief setPluginConnector
     * \param connector
     */
    virtual void setPluginConnector(PluginConnector connector) = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "com.qphoenix.interfaces.plugin/1.0");
