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

#include "translationwidget.h"

#include <QComboBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QToolButton>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>
#include <QDebug>
//#include "global.h"
#include <QMap>
TranslationWidget::TranslationWidget(QWidget *parent) :
    QWidget(parent),
    mSrcComboBox(new QComboBox(this)),
    mResComboBox(new QComboBox(this)),
    mSrcText(new QTextEdit(this)),
    mResText(new QTextBrowser(this)),
    mTranslateButton(new QPushButton(tr("Translate"),this)),
    mSwapButton(new QToolButton(this)),
    mMainLayout(new QVBoxLayout()),
    mButtonsLayout(new QHBoxLayout()),
    mNativeNames(true)

{
    mButtonsLayout->addWidget(mSrcComboBox);
    mButtonsLayout->addWidget(mSwapButton);
    mButtonsLayout->addWidget(mResComboBox);
    mButtonsLayout->addStretch();
    mButtonsLayout->addWidget(mTranslateButton);

    mMainLayout->addWidget(srcText());
    mMainLayout->addLayout(mButtonsLayout);
    mMainLayout->addWidget(mResText);

    setLayout(mMainLayout);


    mSrcComboBox->setSizePolicy(QSizePolicy::Maximum, mSrcComboBox->sizePolicy().verticalPolicy());
    mResComboBox->setSizePolicy(QSizePolicy::Maximum, mSrcComboBox->sizePolicy().verticalPolicy());

    setName("Translate");


    LanguageEngine engine;
    mLangList = engine.languages();

    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSourceLanguageChanged()));
    connect(mSwapButton, SIGNAL(clicked()), this, SLOT(onSwapButtonPressed()));


}


void TranslationWidget::onSourceLanguageChanged() {
    if(mTable.isEmpty() || mIsLinear)
        return;


    mResComboBox->clear();
    QList<QStringList> values = mTable.values();
    fillCombobox(mResComboBox, values.at(mSrcComboBox->currentIndex()));
//    mResComboBox->addItems());

}

void TranslationWidget::onTableChanged() {


    /*
     * Fill source combobox;
     */


    // Is Linear??
    mIsLinear = true;

    mSrcComboBox->clear();


    for(LanguageTable::iterator it = mTable.begin();it != mTable.end(); it++)  {
        if(it.value().count() > 1)
            mIsLinear = false;


    }


    fillCombobox(mSrcComboBox, mTable.keys());
//    QStringList keys = mTable.keys();

//    foreach (QString key, keys) {
//        QString icon = QString(":/flags/flags/%1.png").arg(key);
//        QString name;

//        Language entry = mLangList[key];
//        if(mNativeNames)
//            name = entry.nativeName();
//        else
//            name = entry.name();

//        mSrcComboBox->addItem(QIcon(icon), name);
//    }
}

void TranslationWidget::onSwapButtonPressed() {
}

void TranslationWidget::fillCombobox(QComboBox *cb, QStringList keys) {


    foreach (QString key, keys) {
        QString icon = QString(":/flags/flags/%1.png").arg(key);
        QString name;

        Language entry = mLangList[key];
        if(mNativeNames)
            name = entry.nativeName();
        else
            name = entry.name();

        cb->addItem(QIcon(icon), name);
    }
}
