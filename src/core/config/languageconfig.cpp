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
    mUnsetButton(new QPushButton(tr("Unset All"),this))
{

//    LanguageEngine engine = LanguageEngine::instance();
    mLangList = LanguageEngine::instance().languages();

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

    mTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);


    LanguageList::Iterator it = mLangList.begin();

    int i = 0;
    for(; it != mLangList.end(); ++it) {
        qDebug() << "ITERATION";

        QString name;

        if(mNativeNames)
            name = it.value().nativeName();
        else
            name = it.value().name();



        QString icon = QString(":/flags/flags/%1.png").arg(it.key());
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
        i++;
    }
//    mTable->setColumnWidth(1, 15);

}

void LanguageConfig::setCbState(const bool state) {
    foreach(QCheckBox *cb, mCheckboxList)
        cb->setChecked(state);
}
