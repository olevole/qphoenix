#include "settings.h"
#include "settingsbase.h"
#include "ui_settings.h"



Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)

{
    ui->setupUi(this);
    createConnections();
    loadSettings();

}

void Settings::createConnections() {
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)),
            this, SIGNAL(currentPageChanged(int)));
}

void Settings::loadSettings() {

}

void Settings::insertPage( SettingsBase &page) {
    ui->listWidget->addItem(page.title());
    ui->stackedWidget->addWidget((QWidget*)&page);
    mSettingsPages << &page;
}

void Settings::deletePage(const SettingsBase &page) {
    for(int i = 0; i < mSettingsPages.count(); i++)
        if(mSettingsPages[i]->title() == page.title()) {
            delete ui->listWidget->item(i);
            mSettingsPages.removeAt(i);
        }
}

SettingsBase *Settings::pageAt(const int i) const {
    return mSettingsPages[i];
}


