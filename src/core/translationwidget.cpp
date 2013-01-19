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
    mLanguageList(LanguageFactory::list()),
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


    setName("Translate");


    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSourceLanguageChanged()));
    connect(mSwapButton, SIGNAL(clicked()), this, SLOT(onSwapButtonPressed()));


}


void TranslationWidget::onSourceLanguageChanged() {
    if(mTable.isEmpty() || mIsLinear)
        return;

    mResComboBox->clear();



    QStringList keys = mTable[mTable.keys().at(mSrcComboBox->currentIndex())];

    qDebug() << "Keys : " << keys;

    keys = LanguageFactory::keysToNames(keys, QP_LANG_LIST, mNativeNames);
    mResComboBox->addItems(keys);

}

void TranslationWidget::onTableChanged() {


    /*
     * Fill source combobox;
     */

    mSrcComboBox->clear();

    QStringList keys = mTable.keys();

    mIsLinear = false;
    foreach (QString key , keys)
        if(mTable[key].count() < 1)
            mIsLinear = true;


    foreach (QString key , keys) {
        QString text = QP_LANG_LIST[key].first;
        if(mNativeNames)
            text = QP_LANG_LIST[key].second;

        mSrcComboBox->addItem(text);
        if(mIsLinear)
            mResComboBox->addItem(text);




    }





//    mIsLinear = true;

//    const QStringList keys = mTable.keys();
//    foreach(QString key, keys) {
//        if(mTable[key].count() > 1) {
//            mIsLinear = false;
//            break;
//        }
//    }

////    mIsLinear =true;

//    mSrcComboBox->addItems(keys);

//    if(mIsLinear) {
//        mResComboBox->addItems(keys);
//    }
//    qDebug() << "Keys: " << keys << " IsLinear? " << mIsLinear;

}

void TranslationWidget::onSwapButtonPressed() {
}
