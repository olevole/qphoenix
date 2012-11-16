#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class SettingsBase;


/*
 *  This is an implementation of main settings dialog.
 *  All settings pages MUST include SettingsBase
 */

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QDialog *parent = 0);

    /*  Inserting Settings page into the main
     *  settings dialog.
     */
    void insertPage(const SettingsBase &page);

    /* Returns page obj by index
     */
    SettingsBase & pageAt(int i) const;
    
signals:
    
public slots:
    
};

#endif // SETTINGS_H
