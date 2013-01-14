#ifndef SETTINGS_H
#define SETTINGS_H

#include "configinterface.h"
#include "configpageinterface.h"

#include <QTreeWidget>
#include <QDialogButtonBox>
#include <QDialog>






class QListWidget;
class QStackedLayout;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QTreeWidgetItem;
class QPushButton;
//class Settings;


/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsInteface.
 */


/*
 * A list with Settings pages interfaces
 */
typedef QList<ConfigPageInterface *>ConfigPageList;




class Config : public QDialog,  ConfigInterface
{
    Q_OBJECT
    Q_INTERFACES(ConfigInterface)

public:
    explicit Config(QWidget *parent = 0);
    ~Config();


    /*  Inserting Settings page into the lmain
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */

    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);
private:



    ConfigPageList mPagesList;

    // GUI elements
    QVBoxLayout *mMainLayout;
    QHBoxLayout *mHorizontalLayout;
    QHBoxLayout *mBottomLayout;
    QStackedLayout *mStackedLayout;
    QTreeWidget *mTree;
    QDialogButtonBox *mButtons;
    QPushButton *mDefaultsButton;

//    Settings *mSettingsDialog;
private slots:
    void itemChangeHandle();

    void save();
    void read();
    void reset();
};




#endif // SETTINGS_H