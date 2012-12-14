#include "settings.h"
#include <QStackedWidget>
#include <QGroupBox>
#include <QLayout>
#include <QDebug>
#include <QPushButton>


using namespace  Gui;
using namespace Api;

#include "testpage.h"


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    mMainLayout(new QVBoxLayout),
    mHorizontalLayout(new QHBoxLayout),
    mBottomLayout(new QHBoxLayout),
    mStackedWidget(new QStackedWidget(this)),
    mTree(new QTreeWidget(this)),
    mButtons(new QDialogButtonBox(this)),
    mDefaultsButton(new QPushButton(tr("Defaults"),this))
{


//    mDefaultsButton->setText(tr("Defaults"));

    mHorizontalLayout->addWidget(mTree);
    mHorizontalLayout->addWidget(mStackedWidget);


    mBottomLayout->addWidget(mDefaultsButton);
    mBottomLayout->addStretch();
    mBottomLayout->addWidget(mButtons);

    mMainLayout->addLayout(mHorizontalLayout);
    mMainLayout->addLayout(mBottomLayout);

    mTree->setHeaderHidden(true);



//    mMainLayout->addWidget(mButtons);

    mButtons->setStandardButtons(QDialogButtonBox::Apply |
                                 QDialogButtonBox::Cancel);

    this->setLayout(mMainLayout);


    mStackedWidget->addWidget(new QGroupBox(this));


    TestPage *t = new TestPage();
    TestPage *t2 = new TestPage();


    this->addPage(t);
    this->addPage(t2);

//    this->removePage(t);

//    this->removePage(iface);


    this->save();
    this->read();
    this->defaults();


//    mTree->setFixedSize( mTree->size().height(), 100);
    mTree->setFixedWidth(150);
    mTree->setSizePolicy(QSizePolicy::Fixed, mTree->sizePolicy().verticalPolicy());
    this->resize(800, 600);




    /*!
     * Connections (put all in this section)
     */

    connect(mTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                          this, SLOT(itemChangeHandle()));


}



void Settings::addPage(QObject *page) {
    SettingsInterface *iface = qobject_cast<SettingsInterface *>(page);

    const QString name  = iface->info()->name();

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);

    QGroupBox       *gb = new QGroupBox(name, this);
    gb->setLayout(new QHBoxLayout);
    gb->setFlat(true);
    gb->layout()->addWidget(qobject_cast<QWidget *>(page));


    mPagesList.append(iface);
    mTree->insertTopLevelItem(0,item);
    mStackedWidget->addWidget(gb);

}

void Settings::removePage(const QObject *page) {
    for(int i = 0; i < mPagesList.count(); i++) {
        SettingsInterface *iface = qobject_cast<SettingsInterface *>(page);

        const QString nameA = mPagesList.at(i)->info()->name();
        const QString nameB = iface->info()->name();

        if(nameA == nameB) {
            qDebug() << "<<<<";
              delete mPagesList.at(i);
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



void Settings::itemChangeHandle() {
    const int cur = mTree->currentIndex().row();
    mStackedWidget->setCurrentIndex(cur + 1);
}
