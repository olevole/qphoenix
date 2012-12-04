#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H



/*
 * This is a bacis interface for ALL kind of plugins.
 * Any kind-specific plugin MUST inherit PluginInterface
 *
 */


class PluginInterface
{
public:
    virtual ~EchoInterface() {}

    virtual QString name() const = 0;
    virtual QString version() const = 0;
    virtual QString description() const = 0;


};

 Q_DECLARE_INTERFACE(PluginInterface,
                     "com.trolltech.Plugin.PluginInterface/1.0");



#endif // PLUGININTERFACE_H
