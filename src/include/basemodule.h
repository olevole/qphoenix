#ifndef ABSMODULE_H
#define ABSMODULE_H

#include "info.h"
#include <QString>

class BaseModule : public Info {
public:
    virtual ~BaseModule() {}

    virtual bool load() = 0;
    virtual bool unload() = 0;
    virtual QString errorString() const = 0;
};

Q_DECLARE_INTERFACE(BaseModule, "com.qphoenix.interfaces.basemodule/1.0")



#endif // ABSMODULE_H
