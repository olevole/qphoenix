#include <QStackedLayout>
#include <QGroupBox>
#include <QLayout>
#include <QDebug>
#include <QPushButton>

#include "config.h"
#include "iconfigpage.h"
#include "translatorsconfig.h"
#include "defines.h"

Config::Config(QWidget *parent) :
    QDialog(parent),
    mMainLayout(new QVBoxLayout),
    mHorizontalLayout(new QHBoxLayout),
    mBottomLayout(new QHBoxLayout),
    mStackedLayout(new QStackedLayout),
    mTree(new QTreeWidget(this)),
    mButtons(new QDialogButtonBox(this)),
    mDefaultsButton(new QPushButton(tr("Defaults"),this))
{

    // Gui Init
    mHorizontalLayout->addWidget(mTree);
    mHorizontalLayout->addLayout(mStackedLayout);

    mBottomLayout->addWidget(mDefaultsButton);
    mBottomLayout->addStretch();
    mBottomLayout->addWidget(mButtons);


    setWindowTitle("Settings");


//    QFrame *frame = new QFrame(this);
//    frame->setFrameShape(QFrame::HLine);

    mMainLayout->addLayout(mHorizontalLayout);
//    mMainLayout->addWidget(frame);
    mMainLayout->addLayout(mBottomLayout);

    mTree->setHeaderHidden(true);

    mButtons->setStandardButtons(QDialogButtonBox::Apply |
                                 QDialogButtonBox::Cancel|
                                 QDialogButtonBox::Ok);

    setLayout(mMainLayout);
    resize(600, 500);

    mTree->setFixedWidth(150);
    mTree->setSizePolicy(QSizePolicy::Fixed, mTree->sizePolicy().verticalPolicy());



    /*
     * Connections (put all in this section)
     */

    connect(mTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                          this, SLOT(itemChangeHandle()));

    connect(mButtons, SIGNAL(accepted()), this, SLOT(save()));
    connect(mButtons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(mDefaultsButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(mButtons, SIGNAL(clicked(QDialogButtonBox::Apply)), this, SLOT(save()));

    // Okay, let's tell them to read configurations
    read();

}

Config::~Config() {

}

void Config::addPage(QWidget *page) {
    IConfigPage *iface = qobject_cast<IConfigPage *>(page);



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


    mPagesList.append(iface);
    mTree->insertTopLevelItem(mTree->topLevelItemCount(),item);
    mStackedLayout->addWidget(gb);

    read();

}

void Config::removePage(const QWidget *page) {
    for(int i = 0; i < mPagesList.count(); i++) {
        IConfigPage *iface = qobject_cast<IConfigPage *>(page);


        const QString nameA = mPagesList.at(i)->name();
        const QString nameB = iface->name();

        if(nameA == nameB) {
            qDebug() << "<<<<";
              delete mPagesList.at(i);
        }
    }
}

QWidget *Config::pageAt(const int i) {
    return mStackedLayout->widget(i);
}

void Config::itemChangeHandle() {
    const int cur = mTree->currentIndex().row();
    mStackedLayout->setCurrentIndex(cur);
}



void Config::save() {
    foreach (IConfigPage *i, mPagesList)
        i->save();


    this->accept();
}

void Config::read() {
    foreach(IConfigPage *i, mPagesList)
        i->read();
}

void Config::reset() {
    foreach(IConfigPage *i, mPagesList)
        i->reset();
}



