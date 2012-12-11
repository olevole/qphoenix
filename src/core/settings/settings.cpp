#include "settings.h"
#include <QStackedWidget>
#include <QGroupBox>
#include <QLayout>

using namespace  Gui;
using namespace Api;


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    mMainLayout(new QVBoxLayout),
    mHorizontalLayout(new QHBoxLayout),
    mStackedWidget(new QStackedWidget(this)),
    mTree(new QTreeWidget(this)),
    mButtons(new QDialogButtonBox(this))
{

    mHorizontalLayout->addWidget(mTree);
    mHorizontalLayout->addWidget(mStackedWidget);

    mMainLayout->addLayout(mHorizontalLayout);
    mMainLayout->addWidget(mButtons);

    this->setLayout(mMainLayout);


    mStackedWidget->addWidget(new QGroupBox(this));




}



void Settings::addPage(const SettingsInterface *page) {
    const QString &name  = page->info()->name();



    QTreeWidgetItem *item = new QTreeWidgetItem();
    QGroupBox       *gb = new QGroupBox(name, this);

//    QGr
    item->setText(0, name);
    mTree->addTopLevelItem(item);

    mStackedWidget->addWidget(gb);
}





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
