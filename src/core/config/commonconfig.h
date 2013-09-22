#ifndef COMMONCONFIG_H
#define COMMONCONFIG_H

#include <QWidget>
#include "iconfigpage.h"

class CommonConfig : public QWidget, public IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    explicit CommonConfig(QWidget *parent = 0);

    virtual void save();
    virtual void read();
    virtual void reset();
};

#endif // COMMONCONFIG_H
