/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QSettings>

#include "languageconfig.h"


LanguageConfig::LanguageConfig(QWidget *parent) :
    QWidget(parent),
    mSettings(new QSettings(this)),
    mTableWidget(new QTableWidget(this)),
    mSetButton(new QPushButton(tr("Set All"),this)),
    mUnsetButton(new QPushButton(tr("Unset All"),this))
{    
    QHBoxLayout *buttons  = new QHBoxLayout;
    buttons->addWidget(mSetButton);
    buttons->addWidget(mUnsetButton);
    buttons->addStretch();

    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(mTableWidget);
    main->addLayout(buttons);
    this->setLayout(main);

    mTableWidget->setColumnCount(2);
    mTableWidget->verticalHeader()->hide();
    mTableWidget->horizontalHeader()->setStretchLastSection(true);
    mTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    mTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Enabled")));

    mLangList = QP_LANGUAGE_DB->languages();

    mTableWidget->resizeColumnsToContents();
    mTableWidget->setRowCount(mLangList.size());

    for (int i = 0; i < mLangList.count(); ++i) {
        Language lang = mLangList[i];
        const QIcon icon = QIcon(QString(":/flags/flags/%1.png").arg(lang.code()));
        const QString name = lang.name(mNativeNames);

        QTableWidgetItem *item_name = new QTableWidgetItem;
        item_name->setText(name);
        item_name->setIcon(icon);
        item_name->setFlags(item_name->flags() & (~(Qt::ItemIsEditable | Qt::ItemIsSelectable)));
        mTableWidget->setItem(i, 0, item_name);

        QCheckBox *enabled = new QCheckBox(this);
        mCheckBoxList << enabled;
        mTableWidget->setCellWidget(i, 1, enabled);
    }
    mTableWidget->resizeColumnsToContents();
    connect(mSetButton, SIGNAL(clicked()), this, SLOT(pickAll()));
    connect(mUnsetButton, SIGNAL(clicked()), this, SLOT(unpickAll()));

    mSettings->beginGroup(QP_LANGUAGE_CONFIG_GROUP);
}

void LanguageConfig::save() {
    mSettings->setValue("EnabledLanguages", getEnabledLanguages());
}

void LanguageConfig::read() {

    const QStringList list = mSettings->value("EnabledLanguages").toStringList();
    if(list.isEmpty()) {
        pickAll();
        return;
    }

    unpickAll();
    foreach(QString lang, list) {
        for (int i = 0; i < mCheckBoxList.size(); ++i) {
            Language lang0 = mLangList[i];
            if(lang0.code() == lang)
                mCheckBoxList[i]->setChecked(true);
        }
    }
}

void LanguageConfig::reset() {
    pickAll();
}

QStringList LanguageConfig::getEnabledLanguages() const {
    QStringList list;
    for (int i = 0; i < mLangList.count(); ++i) {
        Language lang = mLangList[i];
        if(mCheckBoxList[i]->isChecked()) {
            list << lang.code();
        }
    }
    return list;
}

void LanguageConfig::setNativeNames(bool b) {
}

void LanguageConfig::pickAll() {
    foreach(QCheckBox *checkbox, mCheckBoxList)
        checkbox->setChecked(true);
}

void LanguageConfig::unpickAll() {
    foreach(QCheckBox *checkbox, mCheckBoxList)
        checkbox->setChecked(false);
}
