#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>

/*!
 * \brief The ConfigInterface class
 *
 * This interface allow plugins to access main
 * config dialog (add their own setting pages)
 */


class ConfigInterface {
public:
    virtual ~ConfigInterface() {}

    virtual void addPage(QWidget *page) = 0;
    virtual void removePage(const QWidget *page) = 0;
    virtual QWidget *pageAt(const int i) = 0;
};

Q_DECLARE_INTERFACE(ConfigInterface, "com.qphoenix.interfaces.settingspage/1.0")




#endif // SETTINGSBASE_H
