#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QGroupBox>



class SettingsInterface {
public:
    virtual ~SettingsInterface() {}

    virtual void addPage(QWidget *page) = 0;
    virtual void removePage(const QWidget *page) = 0;
    virtual QWidget *pageAt(const int i) = 0;
};

Q_DECLARE_INTERFACE(SettingsInterface, "com.qphoenix.interfaces.settingspage/1.0")




#endif // SETTINGSBASE_H
