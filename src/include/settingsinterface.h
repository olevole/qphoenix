#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>
#include "info.h"

namespace Api {

class SettingsInterface// : public Tools::Info
{
public:
    virtual ~SettingsInterface(){}

    // Read and save the settings
    virtual void save() = 0;
    virtual void read() = 0;
    virtual void defaults() = 0;


signals:
    
public slots:
    
};

}// end APi namespace

#endif // SETTINGSBASE_H
