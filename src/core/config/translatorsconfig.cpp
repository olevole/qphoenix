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

#include "translatorsconfig.h"
#include "defines.h"

#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QSettings>


QPTranslatorsConfig::QPTranslatorsConfig(QWidget *parent) :
    QWidget(parent),
    mTranslatorLabel(new QLabel(tr("Translator"), this)),
    mTranslatorComboBox(new QComboBox(this)),
    mTranslatorGroupBox(new QGroupBox(this)),
    mTranslatorLayout(new QHBoxLayout),
    mOptionsGroupBox(new QGroupBox(tr("Config"), this)),
    mOptionsLayout(new QHBoxLayout),
    mTab1(new QVBoxLayout),
    mTabWidget(new QTabWidget(this)),
    mSettings(new QSettings(this))
{
    mTranslatorComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mTranslatorLayout->addWidget(mTranslatorLabel);
    mTranslatorLayout->addWidget(mTranslatorComboBox);
    mTranslatorGroupBox->setLayout(mTranslatorLayout);

    mOptionsGroupBox->setLayout(mOptionsLayout);

    mTab1->addWidget(mTranslatorGroupBox);
    mTab1->addWidget(mOptionsGroupBox);

    mTabWidget->addTab(new QWidget(this), tr("Translators"));
    mTabWidget->addTab(new QWidget(this), tr("Preferences"));
    mTabWidget->widget(0)->setLayout(mTab1);

    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(mTabWidget);

    mTranslatorGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    QPModuleLoader ldr("translators:");

    mModuleList = ldr.modules();

    foreach (QPModule module, mModuleList)
        mTranslatorComboBox->addItem(module.data.name);

    connect(mTranslatorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChange(int)));

    mSettings->beginGroup(QP_TRANSLATORS_CONFIG_GROUP);
}

QPTranslatorsConfig::~QPTranslatorsConfig() {
}

void QPTranslatorsConfig::save() {
    mSettings->setValue("CurrentTranslator", mTranslatorComboBox->currentIndex());
}

void QPTranslatorsConfig::read() {
    mTranslatorComboBox->setCurrentIndex(mSettings->value("CurrentTranslator", 0).toInt());
}

void QPTranslatorsConfig::reset() {
}

QStringList QPTranslatorsConfig::getTranslatorsNames() const {
    QStringList names;
    foreach(QPModule module, mModuleList)
        names << module.data.name;
    return names;
}

QPTranslator QPTranslatorsConfig::currentTranslator() {
    const int i = mTranslatorComboBox->currentIndex();

    if(i == -1)
        qFatal("Invalid translator index!");

    QPModule module = mModuleList[i];
    QPTranslator translator;
    translator.instance = qobject_cast<ITranslator *>(module.instance);
    translator.data = module.data;
    return translator;
}

void QPTranslatorsConfig::setTranslatorIndex(int idx) {
    mTranslatorComboBox->setCurrentIndex(idx);
}

void QPTranslatorsConfig::onIndexChange(const int i) {
    emit translatorIndexChanged(i);


    ITranslator *iface = qobject_cast<ITranslator *>(mModuleList[i].instance);

    if(!iface->isLoaded())
        iface->load();

    QWidget *cw = iface->configWidget();

    if(cw == NULL)
        return;

    QLayoutItem *child;
    while ((child = mOptionsLayout->takeAt(0)) != 0) {
        if(child->widget() != cw) {
            delete child->widget();
            delete child;
        }
    }
    mOptionsLayout->addWidget(cw);
}
