#include "dictionaryconfig.h"


#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTabWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>

DictionaryConfig::DictionaryConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this)),
      mTabWidget(new QTabWidget(this)),
      mRememberPair(new QCheckBox(tr("Remember Language Pair"), this))

{
    setIcon(QP_ICON("dictionary"));


    Loader ldr("dictionaries:");
    mDictionaries = ldr.modules();




    QVBoxLayout *tab1 = new QVBoxLayout;
    tab1->addWidget(mTable);

    QVBoxLayout *tab2 = new QVBoxLayout;
    tab2->addWidget(mRememberPair);
    tab2->addStretch();


    mTabWidget->addTab(new QWidget(this), "Dictionaries");
    mTabWidget->addTab(new QWidget(this), "Preferences");

    mTabWidget->widget(0)->setLayout(tab1);
    mTabWidget->widget(1)->setLayout(tab2);



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTabWidget);
    this->setLayout(mainLayout);
    this->setName("Dictionaries");



    mTable->setColumnCount(3);
    mTable->verticalHeader()->hide();

    mTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Description")));
    mTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Version")));
    mTable->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("#")));


    for (int i = 0; i < mDictionaries.count(); ++i) {
        QObject *d = mDictionaries[i];
        IDictionary *iface = qobject_cast<IDictionary *>(d);
        iface->load();

        mTable->insertRow(i);
        mTable->setRowHeight(i, 20);

        mTable->setItem(i, 1, new QTableWidgetItem(iface->name()));
    }


}
