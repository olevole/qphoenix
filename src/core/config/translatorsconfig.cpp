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
#include "loader.h"
#include "defines.h"

#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>


TranslatorsConfig::TranslatorsConfig(QWidget *parent) :
    QWidget(parent),
    mTranslatorLabel(new QLabel(tr("Translator"), this)),
    mTranslatorComboBox(new QComboBox(this)),
    mTranslatorGroupBox(new QGroupBox(tr("Translators"), this)),
    mTranslatorLayout(new QHBoxLayout),

    mOptionsGroupBox(new QGroupBox(tr("Config"), this)),
    mOptionsLayout(new QHBoxLayout),
    mMainLayout(new QVBoxLayout)
{
    setName(tr("Translators"));


    mTranslatorComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mTranslatorLayout->addWidget(mTranslatorLabel);
    mTranslatorLayout->addWidget(mTranslatorComboBox);
    mTranslatorGroupBox->setLayout(mTranslatorLayout);



    // Second layout
    mOptionsGroupBox->setLayout(mOptionsLayout);

    // Finally, main layout
    mMainLayout->addWidget(mTranslatorGroupBox);
    mMainLayout->addWidget(mOptionsGroupBox);


    mTranslatorGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    this->setLayout(mMainLayout);

    connect(mTranslatorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChange(int)));


    Loader ldr("/tmp/qphoenix-build/src/translators/mymemory");

    ModuleList list = ldr.modules();

    foreach (QObject *obj, list) {
        TranslatorInterface *iface = qobject_cast<TranslatorInterface *>(obj);
        mTranslatorsList <<  iface;
        mTranslatorComboBox->addItem(iface->name());
    }
}


void TranslatorsConfig::onIndexChange(const int i) {
    //! FIXME: optimisation: do not overload same widget!
    QLayoutItem *child;
    while ( (child = mOptionsLayout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    TranslatorInterface *iface = mTranslatorsList[i];
    if(!iface->isLoaded())
        iface->load();

    mOptionsLayout->addWidget(iface->configWidget());
}
