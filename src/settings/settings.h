#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>


namespace Ui {
class Settings;
}

class SettingsBase;


/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsBase.
 */

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);

    /*  Inserting Settings page into the main
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */
    void insertPage( SettingsBase &page);
    void deletePage(const SettingsBase &page);
    SettingsBase *pageAt(const int i) const;
signals:
    void currentPageChanged(const int i);
private:
    Ui::Settings *ui;
    QList<SettingsBase *> mSettingsPages;
    

    void createConnections();

    // Load default setting pages
    void loadSettings();
public slots:
    
};

#endif // SETTINGS_H
