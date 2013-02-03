#include "dictionaryconfig.h"


#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

DictionaryConfig::DictionaryConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this))

{
//    mLoader.addSearchPath("dictionaries:");
    setIcon(QP_ICON("dictionary"));


    Loader ldr("dictionaries:");
    mDictionaries = ldr.modules();

            // = mLoader.modules();

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(mTable);

    this->setLayout(l);



    this->setName("Dictionaries");



    mTable->setColumnCount(3);
//    mTable->verticalHeader()->hide();

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
