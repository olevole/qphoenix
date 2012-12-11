#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "pluginapi.h"
#include "settingsinterface.h"




using namespace Api;


namespace Gui {

/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsInteface.
 */


/*
 * A list with Settings pages interfaces
 */
typedef QList<SettingsInterface *>SettingPageList;


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
//    int count() const {}
private:
    SettingPageList mPagesList;

    void save();
    void read();
    void defaults();
    
};

} // end Gui namespace
#endif // SETTINGS_H
