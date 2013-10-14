#pragma once

#include "imodule.h"

/*!
 * \brief The PluginConnector struct
 * Structure with public pointers to plugin interfaces
 * mainwindow - Main Window interface
 * configdialog - Config dialog iface
 * translationwidget - Translator widget iface
 * dictionarywidget - Dictionary widget iface
 */

#include "imainwindow.h"
#include "iconfig.h"
#include "itranslationwidget.h"
#include "idictionarywidget.h"

struct PluginConnector
{
    IMainWindow *mainwindow;
    IConfig *configdialog;
    ITranslationWidget *translationwidget;
    IDictionaryWidget *dictionarywidget;
};


/*!
 * \brief The IPlugin class
 * Interface for plugins
 */
class IPlugin : public IModule
{

public:
    virtual ~IPlugin() {}

    /*!
     * \brief setPluginConnector
     * \param connector
     */
    virtual void setPluginConnector(PluginConnector connector) = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "com.qphoenix.interfaces.plugin/1.0");
