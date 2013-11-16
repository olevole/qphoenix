#pragma once


#include <QShortcut>
#include <QAction>

class ICore {
public:
    virtual ~ICore() {}


    enum Error {
        ERR_UNKNOW = 0,
        ERR_ACTION_REGISTERED,
        ERR_ACTION_INVALID,
        ERR_LANGUAGE_REGISTERED,
        ERR_LANGUAGE_INVALID
    };

    bool registerAction(const QAction &shortcut, const QString &description);
    bool registerLanguage(const QString &code, const QString &name, const QIcon = QIcon());



    Error error();
};


Q_DECLARE_INTERFACE(ICore, "com.qphoenix.interfaces.core/1.0")
