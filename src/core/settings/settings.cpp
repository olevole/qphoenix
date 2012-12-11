#include "settings.h"


using namespace  Gui;
using namespace Api;

Settings::Settings(QWidget *parent) :
    QDialog(parent)
{





}

//int Settings::count()

void Settings::save() {
    foreach (SettingsInterface *i, mPagesList) {
        i->save();
    }
}

void Settings::read() {
    foreach(SettingsInterface *i, mPagesList) {
        i->read();
    }
}

void Settings::defaults() {
    foreach(SettingsInterface *i, mPagesList) {
        i->defaults();
    }
}
