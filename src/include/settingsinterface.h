#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>
#include "global.h"

#include "pluginapi.h"

namespace Api {



class SettingsInterface : public AbstractInfoContainer
{
public:
    virtual ~SettingsInterface(){}

    // Read and save the settings
    virtual void save() = 0;
    virtual void read() = 0;
    virtual void reset() = 0;



};

}// end APi namespace

Q_DECLARE_INTERFACE(Api::SettingsInterface, "com.qphoenix.interfaces.settings/1.0");

#endif // SETTINGSBASE_H
