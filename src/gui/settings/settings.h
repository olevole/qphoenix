#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>






class Ui_Settings;
class SettingsBase;

namespace Gui {


/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsInteface.
 */

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);

    /*  Inserting Settings page into the lmain
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */
    void insertPage( SettingsBase &page);
    void deletePage(const SettingsBase &page);
    SettingsBase *pageAt(const int i) const;
signals:
    void currentPageChanged(const int i);
private:
    Ui_Settings *ui;
    QList<SettingsBase *> mSettingsPages;
    

    void createConnections();

//     Load default setting pages
    void loadSettings();
public slots:
    
};

} // end Gui namespace
#endif // SETTINGS_H
