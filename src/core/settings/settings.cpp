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



void Settings::addPage(SettingsInterface *page) {
    const QString &name  = page->info()->name();



    QTreeWidgetItem *item = new QTreeWidgetItem();
    QGroupBox       *gb = new QGroupBox(name, this);

//    QGr
    item->setText(0, name);
    mTree->addTopLevelItem(item);

    mStackedWidget->addWidget(gb);
    mPagesList.append(page);
}

void Settings::removePage(const SettingsInterface *page) {
//    mStackedWidget
    for(int i = 0; i < mPagesList.count(); i++) {
        SettingsInterface *iface = mPagesList.at(i);
        const QString nameA = iface->info()->name();
        const QString nameB = page->info()->name();


        if(nameA == nameB) {
            delete mPagesList.at(i);
            delete mGroupboxList.at(i);
            delete mItemsList.at(i);

        }
    }

}

SettingsInterface *Settings::pageAt(const int i) {
    return mPagesList.at(i);
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
