#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>
#include "info.h"


//#define QP_SETTINGS_CAST(a, b) a = qobject_cast<SettingsInterface *>(b)

namespace Api {



class SettingsInterface// : public Tools::Info
{
public:
    virtual ~SettingsInterface(){}

    // Read and save the settings
    virtual void save() = 0;
    virtual void read() = 0;
    virtual void reset() = 0;
//    virtual Tools::Info info()  = 0;
    virtual Tools::Info *info() const = 0;


signals:
    
public slots:
    
};

}// end APi namespace

Q_DECLARE_INTERFACE(Api::SettingsInterface, "com.qphoenix.interfaces.settings/1.0");

#endif // SETTINGSBASE_H
