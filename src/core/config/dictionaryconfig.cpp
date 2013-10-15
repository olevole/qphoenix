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
      mResultCountSpin(new QSpinBox(this)),
      mResultCountLabel(new QLabel(tr("Maximum dictionary results to show"), this))
{
    QPModuleLoader ldr("dictionaries:");
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

    mTable->setColumnCount(4);
    mTable->verticalHeader()->hide();
    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Enabled")));

    for (int i = 0; i < mDictionaries.count(); ++i) {
        QPModule module = mDictionaries[i];
        IDictionary *iface = qobject_cast<IDictionary *>(module.instance);
        iface->load();

        QPDictionary dict;
        dict.instance = iface;
        dict.data = module.data;

        mConvertedDicts.append(dict);

        mTable->insertRow(i);
        mTable->setRowHeight(i, 20);

        QStringList columns;
        columns << module.data.name << module.data.description << module.data.version;

        for (int j = 0; j < columns.size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(columns[j]);
            item->setFlags(item->flags() & (~(Qt::ItemIsEditable | Qt::ItemIsSelectable)));
            mTable->setItem(i, j, item);
        }
        QCheckBox *checkbox = new QCheckBox(this);
        mCheckBoxList << checkbox;
        mTable->setCellWidget(i, 3, checkbox);
    }
    mTable->resizeColumnsToContents();
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
    const int index = s.value("MaxResults", QP_DEFAULT_RESULT_COUNT).toInt();
    mResultCountSpin->setValue(index);
    s.endGroup();
}

void DictionaryConfig::reset() {
    mResultCountSpin->setValue(QP_DEFAULT_RESULT_COUNT);
}

QPDictionaryList DictionaryConfig::dictionaries() {
    return mConvertedDicts;
}

unsigned int DictionaryConfig::maxResults() {
    return mResultCountSpin->value();
}
