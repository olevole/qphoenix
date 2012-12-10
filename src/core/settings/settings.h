#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "pluginapi.h"
#include "settingsinterface.h"






namespace Gui {


/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsInteface.
 */

class Settings : public QDialog,  Api::SettingsWidgetAPI
{
    Q_OBJECT
    Q_INTERFACES(Api::SettingsWidgetAPI)

public:
    explicit Settings(QWidget *parent = 0);


    /*  Inserting Settings page into the lmain
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */

    void addPage(const SettingsInterface *page){}
    void removePage(const SettingsInterface *page){}
    void pageAt(const int i){}
    int count() const {}

    
};

} // end Gui namespace
#endif // SETTINGS_H
