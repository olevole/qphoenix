#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class SettingsBase;


/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsBase.
 */

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QDialog *parent = 0);

    /*  Inserting Settings page into the main
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */
    void insertPage(const SettingsBase &page);
    void deletePage(const SettingsBase &page);
    SettingsBase & pageAt(int i) const;
    
signals:
    
public slots:
    
};

#endif // SETTINGS_H
