#include "dictionaryconfig.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTabWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QSettings>

DictionaryConfig::DictionaryConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this)),
      mTabWidget(new QTabWidget(this)),
//      mRememberPair(new QCheckBox(tr("Store Language Pair"), this)),
      mResultCountLabel(new QLabel(tr("Maximum dictionary results to show"), this)),
      mResultCountSpin(new QSpinBox(this))
{
    setIcon(QP_ICON("dictionary"));
    Loader ldr("dictionaries:");
    mDictionaries = ldr.modules();

    QVBoxLayout *tab1 = new QVBoxLayout;
    tab1->addWidget(mTable);

    QVBoxLayout *tab2 = new QVBoxLayout;

    QHBoxLayout *result_layout = new QHBoxLayout;
    result_layout->addWidget(mResultCountLabel);
    result_layout->addWidget(mResultCountSpin);
    tab2->addLayout(result_layout);
    tab2->addStretch();

    mTabWidget->addTab(new QWidget(this), "Dictionaries");
    mTabWidget->addTab(new QWidget(this), "Preferences");

    mTabWidget->widget(0)->setLayout(tab1);
    mTabWidget->widget(1)->setLayout(tab2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTabWidget);
    this->setLayout(mainLayout);
    this->setName("Dictionaries");

    mTable->setColumnCount(4);
    mTable->verticalHeader()->hide();
    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem("#"));

    for (int i = 0; i < mDictionaries.count(); ++i) {
        QObject *d = mDictionaries[i];
        IDictionary *iface = qobject_cast<IDictionary *>(d);
        iface->load();

        mConvertedDicts.append(iface);

        mTable->insertRow(i);
        mTable->setRowHeight(i, 20);

        mTable->setItem(i, 0, new QTableWidgetItem(iface->name()));
        mTable->setItem(i, 1, new QTableWidgetItem(iface->description()));
        mTable->setItem(i, 2, new QTableWidgetItem(iface->version()));
    }
}

void DictionaryConfig::save() {
    QSettings s;
    s.beginGroup("Dictionaries");
    s.setValue("MaxResults", mResultCountSpin->value());
    s.endGroup();
}

void DictionaryConfig::read() {
    QSettings s;
    s.beginGroup("Dictionaries");
    const int index = s.value("MaxResults", 0).toInt();
    mResultCountSpin->setValue(index);
    s.endGroup();
}

void DictionaryConfig::reset() {
    mResultCountSpin->setValue(QP_DEFAULT_RESULT_COUNT);
}
