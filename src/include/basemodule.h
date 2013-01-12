#ifndef ABSMODULE_H
#define ABSMODULE_H

#include "abstractinfocontainer.h"
#include <QString>

class BaseModule : public AbstractInfoContainer {
public:
    virtual ~BaseModule() {}

    virtual bool init() = 0;
    virtual QString errorString() const = 0;
};

Q_DECLARE_INTERFACE(BaseModule, "com.qphoenix.interfaces.basemodule/1.0")



#endif // ABSMODULE_H
