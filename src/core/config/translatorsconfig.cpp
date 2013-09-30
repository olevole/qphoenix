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


TranslatorsConfig::TranslatorsConfig(QWidget *parent) :
    QWidget(parent),
    mTranslatorLabel(new QLabel(tr("Translator"), this)),
    mTranslatorComboBox(new QComboBox(this)),
    mEmbeddedTranslatorComboBox(new QComboBox(this)),
    mTranslatorGroupBox(new QGroupBox(this)),
    mTranslatorLayout(new QHBoxLayout),

    mOptionsGroupBox(new QGroupBox(tr("Config"), this)),
    mOptionsLayout(new QHBoxLayout),
    mTab1(new QVBoxLayout),
    mTabWidget(new QTabWidget(this))
{
    mTranslatorComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mTranslatorLayout->addWidget(mTranslatorLabel);
    mTranslatorLayout->addWidget(mTranslatorComboBox);
    mTranslatorGroupBox->setLayout(mTranslatorLayout);

    // Second layout
    mOptionsGroupBox->setLayout(mOptionsLayout);

    // Finally, main layout
    mTab1->addWidget(mTranslatorGroupBox);
    mTab1->addWidget(mOptionsGroupBox);

    mTabWidget->addTab(new QWidget(this), tr("Translators"));
    mTabWidget->addTab(new QWidget(this), tr("Preferences"));
    mTabWidget->widget(0)->setLayout(mTab1);

    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(mTabWidget);

    mTranslatorGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    connect(mTranslatorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChange(int)));
    connect(mTranslatorComboBox, SIGNAL(currentIndexChanged(int)), mEmbeddedTranslatorComboBox, SLOT(setCurrentIndex(int)));
    connect(mEmbeddedTranslatorComboBox, SIGNAL(currentIndexChanged(int)), mTranslatorComboBox, SLOT(setCurrentIndex(int)));

    NewLoader ldr("translators:");

    mModuleList = ldr.modules();

    foreach (Module module, mModuleList) {
        mTranslatorComboBox->addItem(module.data.name);
        mEmbeddedTranslatorComboBox->addItem(module.data.name);
    }
}

TranslatorsConfig::~TranslatorsConfig() {
    QSettings s;
    s.beginGroup("Translators");
    s.setValue("CurrentTranslator", mTranslatorComboBox->currentIndex());
    s.endGroup();
}

void TranslatorsConfig::save() {
}

void TranslatorsConfig::read() {
    QSettings s;
    s.beginGroup("Translators");
    const int index = s.value("CurrentTranslator", 0).toInt();
    s.endGroup();

    mTranslatorComboBox->setCurrentIndex(index == -1 ? 0 : index);

}

void TranslatorsConfig::reset() {
}

void TranslatorsConfig::onIndexChange(const int i) {
    if(i >= mModuleList.size() || i < 0)
        qFatal("Translator index out of range!");
    qDebug() << "INDEX IS: " << i;
    ITranslator *iface = qobject_cast<ITranslator *>(mModuleList[i].instance);
    if(!iface->isLoaded())
        iface->load();

    QWidget *cw = iface->configWidget();

    QLayoutItem *child;
    while ((child = mOptionsLayout->takeAt(0)) != 0) {
        if(child->widget() != cw) {
            delete child->widget();
            delete child;
        }
    }
    if(cw == NULL)
        return;
    mOptionsLayout->addWidget(cw);
    mOptionsLayout->addStretch(); //TODO: Does not work. Fix!
}
