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
#include <QToolBar>
#include <QAction>
#include <QApplication>
//#include "global.h"
#include <QMap>
#include <QClipboard>


TranslationToolBar::TranslationToolBar(QWidget *parent)
    :QToolBar(parent),
      mCopyAction(new QAction(QIcon::fromTheme("edit-copy"), "Copy", this))
{
    this->addAction(mCopyAction),

    setIconSize(QSize(16,16));
    connect(mCopyAction,SIGNAL(triggered()), this, SIGNAL(copyRequest()));
}

void TranslationToolBar::setCopyActionEnabled(const bool b) {
    mCopyAction->setEnabled(b);
}

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

    mSrcToolbar(new TranslationToolBar(this)),
    mResToolbar(new TranslationToolBar(this)),
    mNativeNames(true)

{
    mButtonsLayout->addWidget(mResToolbar);
    mButtonsLayout->addWidget(mSrcComboBox);
    mButtonsLayout->addWidget(mSwapButton);
    mButtonsLayout->addWidget(mResComboBox);
    mButtonsLayout->addStretch();
    mButtonsLayout->addWidget(mTranslateButton);


    mMainLayout->addWidget(mSrcToolbar);
    mMainLayout->addWidget(srcText());
    mMainLayout->addLayout(mButtonsLayout);

    mMainLayout->addWidget(mResText);
    setLayout(mMainLayout);


    mSrcComboBox->setSizePolicy(QSizePolicy::Maximum, mSrcComboBox->sizePolicy().verticalPolicy());
    mResComboBox->setSizePolicy(QSizePolicy::Maximum, mSrcComboBox->sizePolicy().verticalPolicy());

    setName("Translate");


    mLangList = QP_LANG_FACTORY->languages();

    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSourceLanguageChanged()));
    connect(mSwapButton, SIGNAL(clicked()), this, SLOT(swap()));
    connect(mSrcToolbar, SIGNAL(copyRequest()), this, SLOT(copySrcText()));
    connect(mResToolbar, SIGNAL(copyRequest()), this, SLOT(copyResText()));
}


void TranslationWidget::onSourceLanguageChanged() {
    if(mTable.isEmpty() || mIsLinear)
        return;


    mResComboBox->clear();
    QList<QStringList> values = mTable.values();
    fillCombobox(mResComboBox, values.at(mSrcComboBox->currentIndex()));
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
}

void TranslationWidget::swap() {
    const int i = srcComboBox()->currentIndex();
    mSrcComboBox->setCurrentIndex(mResComboBox->currentIndex());
    mResComboBox->setCurrentIndex(i);
}

void TranslationWidget::copySrcText() {
    qApp->clipboard()->setText(mSrcText->toPlainText());
}

void TranslationWidget::copyResText() {
    qApp->clipboard()->setText(mResText->toPlainText());
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

        cb->addItem(QIcon(icon), name, key);
    }
}
