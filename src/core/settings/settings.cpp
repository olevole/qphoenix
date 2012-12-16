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

    // Gui Init
    mHorizontalLayout->addWidget(mTree);
    mHorizontalLayout->addWidget(mStackedWidget);

    mBottomLayout->addWidget(mDefaultsButton);
    mBottomLayout->addStretch();
    mBottomLayout->addWidget(mButtons);

    mMainLayout->addLayout(mHorizontalLayout);
    mMainLayout->addLayout(mBottomLayout);

    mTree->setHeaderHidden(true);

    mButtons->setStandardButtons(QDialogButtonBox::Apply |
                                 QDialogButtonBox::Cancel|
                                 QDialogButtonBox::Ok);

    setLayout(mMainLayout);

    mTree->setFixedWidth(150);
    mTree->setSizePolicy(QSizePolicy::Fixed, mTree->sizePolicy().verticalPolicy());
    resize(800, 600);

    // Then, loading settings pages

    TestPage *t = new TestPage();
    TestPage *t2 = new TestPage();


    addPage(t);
    addPage(t2);
//    this->addPage(qobject_cast<QWidget *>(t));
//    this->addPage(t2);


    QObject *o = new QObject();

//    this->addPage(o);


    // Okay, let's tell them to read configurations
    read();







    /*
     * Connections (put all in this section)
     */

    connect(mTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                          this, SLOT(itemChangeHandle()));

    connect(mButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(mButtons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(mDefaultsButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(mButtons, SIGNAL(clicked(QDialogButtonBox::Apply)), this, SLOT(save()));



}

Settings::~Settings() {

}

void Settings::addPage(QObject *page) {
    SettingsInterface *iface = qobject_cast<SettingsInterface *>(page);


    QString name;
    QIcon icon;


    if(iface == NULL) {
        qDebug() << "Unable to cast SettingsPage! Critical error, function terminated!";
        return;
    } else {
        //TODO: Fix this dangerous code!
        name = iface->name();
        icon = iface->icon();
    }




    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setIcon(0, icon);

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


        const QString nameA = mPagesList.at(i)->name();
        const QString nameB = iface->name();

        if(nameA == nameB) {
            qDebug() << "<<<<";
              delete mPagesList.at(i);
        }
    }
}

SettingsInterface *Settings::pageAt(const int i) {
    return mPagesList.at(i);
}

void Settings::itemChangeHandle() {
    const int cur = mTree->currentIndex().row();
    mStackedWidget->setCurrentIndex(cur + 1);
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

void Settings::reset() {
    foreach(SettingsInterface *i, mPagesList) {
        i->reset();
    }

}


//void Settings::accept() {
//    save();
//    QDialog::accept();
//}


