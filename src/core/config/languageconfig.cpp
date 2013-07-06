#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QSettings>
#include <QDebug>
#include "languageconfig.h"

LanguageConfig::LanguageConfig(QWidget *parent) :
    QWidget(parent),
    mTable(new QTableWidget(this)),
    mSetButton(new QPushButton(tr("Set All"),this)),
    mNativeNames(false),
    mUnsetButton(new QPushButton(tr("Unset All"),this))
{
    mLangList = LanguageEngine::instance()->languages();

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


void LanguageConfig::save() {
    QSettings s;
    s.beginGroup("Languages");
    s.setValue("EnabledLanguages", keysForEnabled());
    s.endGroup();
}

void LanguageConfig::read() {
    QStringList keys = mLangList.keys();

    QSettings s;
    s.beginGroup("Languages");
    QStringList enabled = s.value("EnabledLanguages", keys).toStringList();
    s.endGroup();

    if(enabled.isEmpty()) {
        unsetAll();
    } else if(enabled == keys) {
        setAll();
    } else {
        for (int i = 0; i < keys.count(); ++i) {
            bool b = enabled.contains(keys.at(i));
            mCheckboxList.at(i)->setChecked(b);
        }
    }
}

void LanguageConfig::reset() {
    setCbState(true);
}

QStringList LanguageConfig::keysForEnabled() const {
    QStringList enabled;
    const QStringList keys = mLangList.keys();

    for (int i = 0; i < mTable->rowCount(); ++i)
        if(mCheckboxList.at(i)->isChecked())
            enabled << keys.at(i);
    return enabled;
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
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem("*"));

    LanguageList::Iterator it = mLangList.begin();

    //TODO: Fix issue with ugly columns
    int i = 0;
    for(; it != mLangList.end(); ++it) {
        QString name;
        if(mNativeNames)
            name = it.value().nativeName();
        else
            name = it.value().name();
        QString icon = QString(":/flags/flags/%1.png").arg(it.key());
        mTable->insertRow(i);

        QCheckBox *cb = new QCheckBox(this);
        mCheckboxList << cb;

        mTable->setCellWidget(i, 1, cb);
        mTable->setItem(i, 0, new QTableWidgetItem(QIcon(icon), name));
        mTable->setRowHeight(i, 20);
        i++;
    }
//    mTable->setColumnWidth(1, 20);
    mTable->resizeColumnsToContents();
}

void LanguageConfig::setCbState(const bool state) {
    foreach(QCheckBox *cb, mCheckboxList)
        cb->setChecked(state);
}
