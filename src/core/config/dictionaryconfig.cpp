#include "dictionaryconfig.h"


#include <QTableWidget>
#include <QVBoxLayout>

DictionaryConfig::DictionaryConfig(QWidget *parent)
    :QWidget(parent),
      mTable(new QTableWidget(this))

{
    mLoader.addSearchPath("dictionaries:");

    mDictionaries = mLoader.modules();

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(mTable);

    this->setLayout(l);


    this->setName("Dictionaries");

}
