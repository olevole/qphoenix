#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "languageconfig.h"

LanguageConfig::LanguageConfig(QWidget *parent) :
    QWidget(parent),
    mTable(new QTableWidget(this)),
    mSetButton(new QPushButton(tr("Set All"),this)),
    mUnsetButton(new QPushButton(tr("Unset All"),this))
{

    QHBoxLayout *buttons  = new QHBoxLayout;
    buttons->addWidget(mSetButton);
    buttons->addWidget(mUnsetButton);
    buttons->addStretch();

    QVBoxLayout *main = new QVBoxLayout;

    main->addWidget(mTable);
    main->addLayout(buttons);

    this->setLayout(main);


    setName("Languages");
}
