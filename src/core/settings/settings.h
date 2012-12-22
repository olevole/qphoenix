#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "settingsinterface.h"
#include "settingspageinterface.h"
#include <QTreeWidget>
#include <QDialogButtonBox>





class QListWidget;
class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QTreeWidgetItem;
class QPushButton;



/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsInteface.
 */


/*
 * A list with Settings pages interfaces
 */
typedef QList<SettingsPageInterface *>SettingPageList;




class Settings : public QDialog,  SettingsInterface
{
    Q_OBJECT
    Q_INTERFACES(SettingsInterface)

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();


    /*  Inserting Settings page into the lmain
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */

    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);
private:



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

    void save();
    void read();
    void reset();

//    void accept();
//    void reject();
//    void reset();

};




#endif // SETTINGS_H
