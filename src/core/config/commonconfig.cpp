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

#include "commonconfig.h"
#include <QTabWidget>
#include <QCheckBox>
#include <QSettings>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

CommonConfig::CommonConfig(QWidget *parent) :
    QWidget(parent),
    mTabWidget(new QTabWidget(this))
{
    createLanguagePage();
    createNetworkPage();
}

void CommonConfig::save() {
    QSettings s;
    s.beginGroup("Common");
    s.setValue("UseNativeNames", mUseNativeCheckbox->isChecked());

}

void CommonConfig::read() {
    QSettings s;
    s.beginGroup("Common");
    mUseNativeCheckbox->setChecked(s.value("UseNativeNames", false).toBool());
}

void CommonConfig::reset() {
    mUseNativeCheckbox->setChecked(false);
}

bool CommonConfig::getNativeNamesEnabled() {
    return mUseNativeCheckbox->isChecked();
}

void CommonConfig::createLanguagePage() {

    mUseNativeCheckbox = new QCheckBox(this);
    mLanguageCombobox = new QComboBox(this);
    mLanguageLabel = new QLabel(this);

    mUseNativeCheckbox->setText(tr("Use native language names"));
    mLanguageLabel->setText(tr("Inteface language"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    mainLayout->addWidget(mTabWidget);

    QWidget *page1 = new QWidget(mTabWidget);
    QVBoxLayout *page1_layout = new QVBoxLayout;
    QHBoxLayout *languageLayout = new QHBoxLayout;
    languageLayout->addWidget(mLanguageLabel);
    languageLayout->addWidget(mLanguageCombobox);
    page1->setLayout(page1_layout);
    page1_layout->addWidget(mUseNativeCheckbox);
    page1_layout->addLayout(languageLayout);
    page1_layout->addStretch();

    mTabWidget->addTab(page1, tr("Language"));
}

void CommonConfig::createNetworkPage() {

}
