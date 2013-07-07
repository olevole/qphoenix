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
#include "defines.h"

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
#include <QMap>
#include <QClipboard>
#include <QLabel>
#include <QSizePolicy>

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
    mMainToolBar(new QToolBar(this)),
    mNativeNames(true)
{
    mButtonsLayout->addWidget(mResToolbar);
    mButtonsLayout->addWidget(mSrcComboBox);
    mButtonsLayout->addWidget(mSwapButton);
    mButtonsLayout->addWidget(mResComboBox);
    mButtonsLayout->addStretch();
    mButtonsLayout->addWidget(mTranslateButton);
    mMainToolBar->setMovable(false);
    mMainToolBar->addSeparator();
    mMainToolBar->addWidget(new QLabel(tr("  Translator: "), this));

    mMainLayout->addWidget(mSrcToolbar);
    mMainLayout->addWidget(srcText());
    mMainLayout->addLayout(mButtonsLayout);
    mMainLayout->addWidget(mResText);
    setLayout(mMainLayout);

    mSrcComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mResComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setName("Translation");
    setIcon(QP_ICON("translator"));

    mWorker.setTimeout(QP_TRANSLATOR_TIMEOUT);

    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSourceLanguageChanged()));
    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtonState()));
    connect(mResComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtonState()));
    connect(mSrcText, SIGNAL(textChanged()), this, SLOT(updateButtonState()));
    connect(mSwapButton, SIGNAL(clicked()), this, SLOT(swap()));
    connect(mSrcToolbar, SIGNAL(copyRequest()), this, SLOT(copySrcText()));
    connect(mResToolbar, SIGNAL(copyRequest()), this, SLOT(copyResText()));
    connect(&mWorker, SIGNAL(reply(QString)), resText(), SLOT(setPlainText(QString)));
    connect(this->translateButton(), SIGNAL(clicked()), this, SLOT(translate()));
    connect(mResText, SIGNAL(textChanged()), this, SIGNAL(finished()));



    updateButtonState();
    this->readCfg();
}

TranslationWidget::~TranslationWidget() {
    saveCfg();
}



void TranslationWidget::setTranslator(ITranslator *t) {
    qDebug() << "Setting translator!!!!";
    mWorker.setTranslator(t);
    qDebug() << "Updating languages!!!!";
    updateLanguages();
//    readCfg();
}


void TranslationWidget::setTranslatorsConfig(TranslatorsConfig *cfg) {
    mTranslatorConfig = cfg;
    mEmbeddedComboBox = mTranslatorConfig->getEmbeddedComboBox();
    mMainToolBar->addWidget(mEmbeddedComboBox);
    connect(mEmbeddedComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(requestKeysUpdate()));


}

void TranslationWidget::onSourceLanguageChanged() {
    if(mTable.isEmpty() || mIsLinear)
        return;
    mResComboBox->clear();
    QList<QStringList> values = mTable.values();
    fillCombobox(mResComboBox, values.at(mSrcComboBox->currentIndex()));
    mResComboBox->setCurrentIndex(mResComboBox->count() ? 0 : -1);
}

//void TranslationWidget::onTranslatorChanged() {
//    qDebug() << "CALLEDD1111!";
//    updateLanguages();
//    setEnabledKeys(m->keysForEnabled());
//}


void TranslationWidget::updateButtonState() {
    const bool ready = (srcComboboxData() != resComboboxData()) && !srcText()->toPlainText().isEmpty();
    mTranslateButton->setEnabled(ready);
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
    for (int i = 0; i < keys.count(); ++i) {
        QString key =  keys[i];
        QString icon = QString(":/flags/%1.png").arg(key);
        QString name;
        Language entry = QP_LANG_FACTORY[key];
        if(mNativeNames)
            name = entry.nativeName();
        else
            name = entry.name();
        cb->addItem(QIcon(icon), name, key);
        cb->setItemData(i, key);

    }
}

void TranslationWidget::translate() {
    QString src_text = srcText()->toPlainText();
    mWorker.query(srcComboboxData(), resComboboxData(), src_text);
}

void TranslationWidget::updateLanguages() {
    ITranslator *tr = mWorker.translator();
    LanguageTable table = tr->table();

    Q_ASSERT(tr != NULL);
//    Q_ASSERT(!mKeys.isEmpty());

    /*!
     * Processing table (remove disbled language codes)
     */

    for(LanguageTable::iterator i = table.begin(); i != table.end();) {
        const QString &key = i.key();
        if(!mKeys.contains(key)) {
            i = table.erase(i);
        } else {
            QStringList values = i.value();
            for (int j = 0; j < values.count(); ++j) {
                if(!mKeys.contains(values.at(j)))
                    values.removeAt(j);
            }
            table[key] = values;
            ++i;
        }
    }

    /*!
     * Updating comboboxes..
     */
    mIsLinear = true;
    mSrcComboBox->clear();
    mResComboBox->clear();
    for(LanguageTable::iterator it = table.begin();it != table.end(); it++)
        if(it.value().count() > 1)
            mIsLinear = false;
    mTable = table;
    fillCombobox(mSrcComboBox, table.keys());
    if(mIsLinear)
        fillCombobox(mResComboBox, table.keys());
}



void TranslationWidget::saveCfg() {
    QSettings s;
    s.beginGroup("TranslationWidget");
    s.setValue("src_index", mSrcComboBox->currentIndex());
    s.setValue("res_index", mResComboBox->currentIndex());
//    s.setValue("TranslatorIndex", mEmbeddedComboBox->currentIndex());
    s.endGroup();
}

void TranslationWidget::readCfg() {
        QSettings s;
        s.beginGroup("TranslationWidget");
        const int src  = s.value("src_index", 0).toInt();
        const int res  = s.value("res_index", 0).toInt();
//        const int index = s.value("TranslatorIndex", -1).toInt();
        s.endGroup();
        mSrcComboBox->setCurrentIndex(mSrcComboBox->count() >= src ? src : -1);
        mResComboBox->setCurrentIndex(mResComboBox->count() >= res ? res : -1);
//        mEmbeddedComboBox->setCurrentIndex(index);
}

QString TranslationWidget::srcComboboxData() {
    return  srcComboBox()->itemData(srcComboBox()->currentIndex()).toString();
}

QString TranslationWidget::resComboboxData() {
    return resComboBox()->itemData(resComboBox()->currentIndex()).toString();
}
