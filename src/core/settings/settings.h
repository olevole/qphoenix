#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "pluginapi.h"
#include "settingsinterface.h"
#include <QTreeWidget>
#include <QDialogButtonBox>



using namespace Api;
using namespace Tools;

class QListWidget;
class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QTreeWidgetItem;


namespace Gui {

class QPushButton;
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

    void addPage(QObject *page);
    void removePage(const QObject *page);
    SettingsInterface *pageAt(const int i);
private:
    void save();
    void read();
    void defaults();



    SettingPageList mPagesList;
//    QList<QGroupBox *> mGroupboxList;
//    QList<QTreeWidgetItem *> mItemsList;


    // GUI elements

    QVBoxLayout *mMainLayout;
    QHBoxLayout *mHorizontalLayout;
    QHBoxLayout *mBottomLayout;
    QStackedWidget *mStackedWidget;
    QTreeWidget *mTree;
    QDialogButtonBox *mButtons;
    QPushButton *mDefaultsButton;
private slots:
    void itemChangeHandle();

    
};


} // end Gui namespace


#endif // SETTINGS_H