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
    mMainLayout->addWidget(mSrcText);
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
    connect(mResComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onResultLanguageChanged()));

    connect(mSrcText, SIGNAL(textChanged()), this, SLOT(updateButtonState()));
    connect(mSwapButton, SIGNAL(clicked()), this, SLOT(swap()));
    connect(mSrcToolbar, SIGNAL(copyRequest()), this, SLOT(copySrcText()));
    connect(mResToolbar, SIGNAL(copyRequest()), this, SLOT(copyResText()));
    connect(&mWorker, SIGNAL(reply(QString)), mResText, SLOT(setPlainText(QString)));
    connect(mTranslateButton, SIGNAL(clicked()), this, SLOT(translate()));
    connect(mResText, SIGNAL(textChanged()), this, SIGNAL(finished()));

    updateButtonState();
    this->readCfg();
}

TranslationWidget::~TranslationWidget() {
    saveCfg();
}


QString TranslationWidget::getSourceText() const {
    return mSrcText->toPlainText();
}

QString TranslationWidget::getResultText() const {
    return mResText->toPlainText();
}

void TranslationWidget::setSourceText(const QString &text) {
    mSrcText->setPlainText(text);
}

void TranslationWidget::setResultText(const QString &text) {
    mResText->setPlainText(text);
}

void TranslationWidget::clearSourceText() {
    mSrcText->clear();
}

void TranslationWidget::clearResultText() {
    mResText->clear();
}

QString TranslationWidget::getSourceLanguageCode() {
    return mSrcComboBox->itemData(mSrcComboBox->currentIndex()).toString();
}

QString TranslationWidget::getResultLanguageCode() {
    return mResComboBox->itemData(mResComboBox->currentIndex()).toString();
}

QObject *TranslationWidget::qobject() {
    return this;
}

void TranslationWidget::addToolbarAction(QAction *action, TranslationWidgetToolbar toolbar) {
    switch(toolbar) {
    case MainToolbar:
        mMainToolBar->addAction(action);
        break;
    case SourceTextToolbar:
        mSrcToolbar->addAction(action);
        break;
    case ResultTextToolbar:
        mResToolbar->addAction(action);
        break;
    default:
        qWarning("Unknown TranslationWidgetToolbar");
    }
}

void TranslationWidget::setTranslator(ITranslator *t) {
    qDebug() << "Setting translator!!!!";
    mWorker.setTranslator(t);
    qDebug() << "Updating languages!!!!";
    updateLanguages();
}


void TranslationWidget::setTranslatorsConfig(TranslatorsConfig *cfg) {
    mTranslatorConfig = cfg;
    mEmbeddedComboBox = mTranslatorConfig->getEmbeddedComboBox();
    mMainToolBar->addWidget(mEmbeddedComboBox);
}

void TranslationWidget::onSourceLanguageChanged() {
    mLastSrcName = mSrcComboBox->currentText();
    if(mTable.isEmpty() || mIsLinear)
        return;

    QList<QStringList> values = mTable.values();
    fillCombobox(mResComboBox, values.at(mSrcComboBox->currentIndex()));

}

void TranslationWidget::onResultLanguageChanged() {
    mLastDestName = mResComboBox->currentText();
}

void TranslationWidget::updateButtonState() {
    const bool ready = (srcComboboxData() != resComboboxData()) && !mSrcText->toPlainText().isEmpty();
    mTranslateButton->setEnabled(ready);
}

void TranslationWidget::swap() {
    const int i = mSrcComboBox->currentIndex();
    mSrcComboBox->setCurrentIndex(mResComboBox->currentIndex());
    mResComboBox->setCurrentIndex(i);
}

void TranslationWidget::undo() {
    mSrcText->undo();
}

void TranslationWidget::redo() {
    mSrcText->redo();
}

void TranslationWidget::copySrcText() {
    qApp->clipboard()->setText(mSrcText->toPlainText());
}

void TranslationWidget::copyResText() {
    qApp->clipboard()->setText(mResText->toPlainText());
}

void TranslationWidget::fillCombobox(QComboBox *cb, QStringList keys) {
    onSourceLanguageChanged();
    onResultLanguageChanged();
    cb->clear();
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

void TranslationWidget::setIndexByKey(QComboBox *cb, const QString &key) {
    int match_index = 0;
    for (int i = 0; i < cb->count(); ++i) {
        if(cb->itemText(i) == key) {
            match_index = i;
            break;
        }
    }
    qDebug() << "Setting index: " << match_index;
    cb->setCurrentIndex(match_index);
}

void TranslationWidget::translate() {
    QString src_text = mSrcText->toPlainText();
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

    for(LanguageTable::iterator it = table.begin();it != table.end(); it++)
        if(it.value().count() > 1)
            mIsLinear = false;
    mTable = table;
     qDebug() << "LAST SRC NAME: " << mLastSrcName << "LAST DEST NAME: " << mLastDestName;
    const QString src = mLastSrcName;
    const QString dest = mLastDestName;
    fillCombobox(mSrcComboBox, table.keys());
    if(mIsLinear)
        fillCombobox(mResComboBox, table.keys());

    qDebug() << "LAST SRC NAME: " << src << "LAST DEST NAME: " << dest;

    setIndexByKey(mSrcComboBox, src);
    setIndexByKey(mResComboBox, dest);
}

void TranslationWidget::saveCfg() {
    QSettings s;
    s.beginGroup("TranslationWidget");
    s.setValue("src_index", mSrcComboBox->currentIndex());
    s.setValue("res_index", mResComboBox->currentIndex());
    s.endGroup();
}

void TranslationWidget::readCfg() {
        QSettings s;
        s.beginGroup("TranslationWidget");
        const int src  = s.value("src_index", 0).toInt();
        const int res  = s.value("res_index", 0).toInt();
        s.endGroup();
        mSrcComboBox->setCurrentIndex(mSrcComboBox->count() >= src ? src : -1);
        mResComboBox->setCurrentIndex(mResComboBox->count() >= res ? res : -1);
}

QString TranslationWidget::srcComboboxData() {
    return  mSrcComboBox->itemData(mSrcComboBox->currentIndex()).toString();
}

QString TranslationWidget::resComboboxData() {
    return mResComboBox->itemData(mResComboBox->currentIndex()).toString();
}
