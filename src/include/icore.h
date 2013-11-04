#pragma once


#include <QShortcut>

class ICore {
public:
    virtual ~ICore() {}

    bool registerShortcut(const QShortcut &shortcut, const QString &description);
    bool registerLanguage(const QString &code, const QString &name, const QIcon = QIcon());
};
