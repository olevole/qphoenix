#pragma once

#include <QString>

class QObject;



/*!
 * \brief The IModule class
 *
 * This is a base class for ALL modules (translators, dictionaries, plugins)
 * Class IModule MUST be inherited by all kinds of modules.
 */

class IModule/* : public Info */{
public:
    virtual ~IModule() {}


    /*!
     * \brief load
     * \return true module was successfully loaded, otherwise -false
     * Initialise plugin (prepare plugin to work). It means creating
     * widgets, loading configs, etc. Do it in this method INSTEAD
     * of consturctor!!!!
     */
    virtual bool load() = 0;

    /*!
     * \brief unload
     * \return true module was successfully unloaded, otherwise -false
     * Unload plugin (removing all widgets, etc)
     */

    virtual bool unload() = 0;


    /*!
     * \brief isLoaded
     * \return true if plugin is loaded, othervise - fasle
     */
    virtual bool isLoaded() const = 0;

};

Q_DECLARE_INTERFACE(IModule, "com.qphoenix.interfaces.imodule/1.0")
