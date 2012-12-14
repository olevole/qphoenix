#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H



/*
 * This is a basic interface for ALL plugins
 */

#include <QString>

namespace Api {

class PluginInterface
{
public:
    virtual ~EchoInterface() {}

    virtual QString name() const = 0;
    virtual QString version() const = 0;
    virtual QString description() const = 0;
};


} // end Api namespace

Q_DECLARE_INTERFACE(PluginInterface,"com.qphoenix.interfaces.plugin/1.0");



#endif // PLUGININTERFACE_H
