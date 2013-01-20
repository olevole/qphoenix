#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "languageconfig.h"

LanguageConfig::LanguageConfig(QWidget *parent) :
    QWidget(parent),
    mTable(new QTableWidget(this)),
    mSetButton(new QPushButton(tr("Set All"),this)),
    mUnsetButton(new QPushButton(tr("Unset All"),this))
{

    LanguageEngine engine;
    mLangList = engine.languages();

    QHBoxLayout *buttons  = new QHBoxLayout;
    buttons->addWidget(mSetButton);
    buttons->addWidget(mUnsetButton);
    buttons->addStretch();

    QVBoxLayout *main = new QVBoxLayout;

    main->addWidget(mTable);
    main->addLayout(buttons);

    this->setLayout(main);


    setName("Languages");

    createTable();


    connect(mSetButton, SIGNAL(clicked()), this, SLOT(setAll()));
    connect(mUnsetButton, SIGNAL(clicked()), this, SLOT(unsetAll()));
}


void LanguageConfig::setAll() {
    setCbState(true);
}

void LanguageConfig::unsetAll() {
    setCbState(false);
}


void LanguageConfig::createTable() {
    mTable->setColumnCount(2);

    mTable->verticalHeader()->hide();
    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Enabled"));

    mTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    QStringList  keys = mLangList.keys();

    LanguageList::Iterator it = mLangList.begin();


    for(int i = 0; i < keys.count(); i++) {
        qDebug() << "ITERATION";

        QString key = keys.at(i);
        QString name;

        if(mNativeNames)
            name = mLangList[key].nativeName();
        else
            name = mLangList[key].name();


        QString icon = QString(":/flags/flags/%1.png").arg(key);
        mTable->insertRow(i);

        QTableWidgetItem *item = new QTableWidgetItem;

        item->setFlags(item->flags() & (~(Qt::ItemIsEditable | Qt::ItemIsSelectable)));
        item->setText(name);
        item->setIcon(QIcon(icon));

        QCheckBox *cb = new QCheckBox(this);
        mCheckboxList << cb;

        mTable->setCellWidget(i, 1, cb);

        mTable->setItem(i, 0, new QTableWidgetItem(QIcon(icon), name));
        mTable->setRowHeight(i, 20);


    }

}

void LanguageConfig::setCbState(const bool state) {
    foreach(QCheckBox *cb, mCheckboxList)
        cb->setChecked(state);
}
