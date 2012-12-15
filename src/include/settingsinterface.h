#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>
#include "info.h"




namespace Api {

using namespace Tools;


class SettingsInterface// : public Tools::Info
{
public:
    virtual ~SettingsInterface(){}

    // Read and save the settings
    virtual void save() = 0;
    virtual void read() = 0;
    virtual void reset() = 0;

    virtual Info *info() const = 0;

};

}// end APi namespace

Q_DECLARE_INTERFACE(Api::SettingsInterface, "com.qphoenix.interfaces.settings/1.0");

#endif // SETTINGSBASE_H
