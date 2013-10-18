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

#include <QStackedLayout>
#include <QGroupBox>
#include <QLayout>
#include <QDebug>
#include <QPushButton>
#include <QSettings>
#include <QListWidget>

#include "config.h"
#include "iconfigpage.h"
#include "translatorsconfig.h"
#include "defines.h"

Config::Config(QWidget *parent) :
    QDialog(parent),
    mMainLayout(new QVBoxLayout),
    mHorizontalLayout(new QHBoxLayout),
    mBottomLayout(new QHBoxLayout),
    mStackedLayout(new QStackedLayout),
    mListWidget(new QListWidget(this)),
    mButtons(new QDialogButtonBox(this)),
    mDefaultsButton(new QPushButton(tr("Defaults"),this))
{
    setWindowTitle(tr("Settings"));
    resize(QP_CONFIG_DIALOG_DEFAULT_HEIGH, QP_CONFIG_DIALOG_DEFAULT_WIDTH);

    mHorizontalLayout->addWidget(mListWidget);
    mHorizontalLayout->addLayout(mStackedLayout);

    mBottomLayout->addWidget(mDefaultsButton);
    mBottomLayout->addStretch();
    mBottomLayout->addWidget(mButtons);

    mMainLayout->addLayout(mHorizontalLayout);
    mMainLayout->addLayout(mBottomLayout);


    mButtons->setStandardButtons(QDialogButtonBox::Apply |
                                 QDialogButtonBox::Cancel|
                                 QDialogButtonBox::Ok);

    setLayout(mMainLayout);

    mListWidget->setFixedWidth(150);
    mListWidget->setSizePolicy(QSizePolicy::Fixed, mListWidget->sizePolicy().verticalPolicy());

    connect(mListWidget, SIGNAL(currentRowChanged(int)), mStackedLayout, SLOT(setCurrentIndex(int)));
    connect(mButtons, SIGNAL(accepted()), this, SLOT(save()));
    connect(mButtons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(mDefaultsButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(mButtons, SIGNAL(clicked(QDialogButtonBox::Apply)), this, SLOT(save()));
    connect(mStackedLayout, SIGNAL(widgetRemoved(int)), this, SLOT(onWidgetRemove(int)));

    read();
}

Config::~Config() {
    save();
}

void Config::addPage(QWidget *page, const QString &name, const QIcon &icon) {
    IConfigPage *iface = qobject_cast<IConfigPage *>(page);

    if(iface == NULL)
        return;

    mPagesList.append(iface);
    mListWidget->addItem(new QListWidgetItem(icon, name));
    mStackedLayout->addWidget(page);
    read();
}

void Config::removePage(QWidget *page) {
    mStackedLayout->removeWidget(page);
}

QWidget *Config::pageAt(int i) {
    if(mStackedLayout->count() <= i) {
        qFatal("Page index out of range!");
    }
    return mStackedLayout->widget(i);
}


void Config::onWidgetRemove(int idx) {
    delete mPagesList[idx];
    delete mListWidget->itemAt(idx, 0);
}

void Config::save() {
    QSettings s;
    s.beginGroup("ConfigDialog");
    s.setValue("Geometry", saveGeometry());
    s.endGroup();

    foreach (IConfigPage *i, mPagesList)
        i->save();
    this->accept();
}

void Config::read() {
    QSettings s;
    s.beginGroup("ConfigDialog");
    restoreGeometry(s.value("Geometry").toByteArray());
    s.endGroup();

    foreach(IConfigPage *i, mPagesList)
        i->read();
}

void Config::reset() {
    foreach(IConfigPage *i, mPagesList)
        i->reset();
}



