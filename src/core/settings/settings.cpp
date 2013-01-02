#include "settings.h"
#include <QStackedLayout>
#include <QGroupBox>
#include <QLayout>
#include <QDebug>
#include <QPushButton>




#include "testpage.h"
#include "translator.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    mMainLayout(new QVBoxLayout),
    mHorizontalLayout(new QHBoxLayout),
    mBottomLayout(new QHBoxLayout),
    mStackedLayout(new QStackedLayout),
    mTree(new QTreeWidget(this)),
    mButtons(new QDialogButtonBox(this)),
    mDefaultsButton(new QPushButton(tr("Defaults"),this))
//    mSettingsDialog(new Settings(this))
{

    // Gui Init
    mHorizontalLayout->addWidget(mTree);
    mHorizontalLayout->addLayout(mStackedLayout);

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

//    TestPage *t = new TestPage();
//    TestPage *t2 = new TestPage();

//    Translator t3;

//    t3.show();


//    addPage(t);
//    addPage(t2);
//    addPage(&t3);
//    this->addPage(qobject_cast<QWidget *>(t));
//    this->addPage(t2);


//    QObject *o = new QObject();

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

//    connect()



}

Settings::~Settings() {

}

void Settings::addPage(QWidget *page) {
    SettingsPageInterface *iface = qobject_cast<SettingsPageInterface *>(page);


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

    if(name.isEmpty())
        name = "<UNKNOW>";




    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setIcon(0, icon);

    QGroupBox       *gb = new QGroupBox(name, this);
    gb->setLayout(new QHBoxLayout);
    gb->setFlat(true);
    gb->layout()->addWidget(qobject_cast<QWidget *>(page));


//    mPagesList.append(iface);
    mTree->insertTopLevelItem(mTree->topLevelItemCount(),item);
    mStackedLayout->addWidget(gb);

}

void Settings::removePage(const QWidget *page) {
    SettingsPageInterface *iface2;
    for(int i = 0; i < mPagesList.count(); i++) {
        SettingsPageInterface *iface = qobject_cast<SettingsPageInterface *>(page);


        const QString nameA = mPagesList.at(i)->name();
        const QString nameB = iface->name();

        if(nameA == nameB) {
            qDebug() << "<<<<";
              delete mPagesList.at(i);
        }
    }
}

QWidget *Settings::pageAt(const int i) {
    return mStackedLayout->widget(i);
}

void Settings::itemChangeHandle() {
    const int cur = mTree->currentIndex().row();
    mStackedLayout->setCurrentIndex(cur);
}



void Settings::save() {
    foreach (SettingsPageInterface *i, mPagesList) {
        i->save();
    }
}

void Settings::read() {
    foreach(SettingsPageInterface *i, mPagesList) {
        i->read();
    }
}

void Settings::reset() {
    foreach(SettingsPageInterface *i, mPagesList) {
        i->reset();
    }

}



