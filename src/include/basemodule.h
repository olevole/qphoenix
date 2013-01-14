#ifndef ABSMODULE_H
#define ABSMODULE_H

#include "info.h"
#include <QString>



/*!
 * \brief The BaseModule class
 *
 * This is a base class for ALL modules (translators, dictionaries, plugins)
 * Class BaseModule MUST be inherited by all kinds of modules.
 */

class BaseModule : public Info {
public:
    virtual ~BaseModule() {}


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
     * \brief errorString
     * \return Description of plugin load\unload error
     * this is optional.
     */
    virtual QString errorString() const
    {return QString();}
};

Q_DECLARE_INTERFACE(BaseModule, "com.qphoenix.interfaces.basemodule/1.0")



#endif // ABSMODULE_H