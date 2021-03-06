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
#include <QProgressBar>
#include <QSizePolicy>
#include <QSettings>

QPTranslationToolBar::QPTranslationToolBar(QWidget *parent)
    :QToolBar(parent),
      mCopyAction(new QAction(QIcon::fromTheme("edit-copy"), "Copy", this))
{
    this->addAction(mCopyAction),
    setIconSize(QSize(16,16));
    connect(mCopyAction,SIGNAL(triggered()), this, SIGNAL(copyRequest()));
}

void QPTranslationToolBar::setCopyActionEnabled(const bool b) {
    mCopyAction->setEnabled(b);
}

QPLanguageComboBox::QPLanguageComboBox(QWidget *parent)
    :QComboBox(parent)
{
}

QString QPLanguageComboBox::currentData() const {
    return this->itemData(this->currentIndex()).toString();
}

void QPLanguageComboBox::setIndexByKey(const QString &key) {
    for (int i = 0; i < count(); ++i) {
        const QString itemtext = itemData(i).toString();
        if(itemtext == key) {
            setCurrentIndex(i);
        }
    }
}

QPTranslationWidget::QPTranslationWidget(QWidget *parent) :
    QWidget(parent),
    mSettings(new QSettings(this)),
    mTranslatorsComboBox(new QComboBox(this)),
    mMainToolBar(new QToolBar(this)),
    mSrcToolbar(new QPTranslationToolBar(this)),
    mResToolbar(new QPTranslationToolBar(this)),
    mSrcComboBox(new QPLanguageComboBox(this)),
    mResComboBox(new QPLanguageComboBox(this)),
    mSrcText(new QTextEdit(this)),
    mResText(new QTextBrowser(this)),
    mTranslateButton(new QPushButton(tr("Translate"),this)),
    mSwapButton(new QToolButton(this)),
    mMainLayout(new QVBoxLayout()),
    mButtonsLayout(new QHBoxLayout()),
    mNativeNames(true),
    mLanguageTableIsFlat(false)
{
    mSwapButton->setIcon(QP_ICON("system-switch-user"));
    mTranslateButton->setIcon(QP_ICON("go-next"));
    mTranslateButton->setShortcut(QKeySequence("Ctrl+T"));
    mButtonsLayout->addWidget(mResToolbar);
    mButtonsLayout->addWidget(mSrcComboBox);
    mButtonsLayout->addWidget(mSwapButton);
    mButtonsLayout->addWidget(mResComboBox);
    mButtonsLayout->addStretch();
    mButtonsLayout->addWidget(mTranslateButton);
    mMainToolBar->setMovable(false);
    mMainToolBar->addSeparator();
    mMainToolBar->addWidget(new QLabel(tr("  Translator: "), this));
    mMainToolBar->addWidget(mTranslatorsComboBox);

    mMainLayout->addWidget(mSrcToolbar);
    mMainLayout->addWidget(mSrcText);
    mMainLayout->addLayout(mButtonsLayout);
    mMainLayout->addWidget(mResText);
    setLayout(mMainLayout);

    mSettings->beginGroup("TranslationWidget");

    mSrcComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mResComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(mTranslatorsComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(translatorIndexChanged(int)));
    connect(mTranslatorsComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboxes()));

    connect(mSwapButton, SIGNAL(clicked()), this, SLOT(swap()));
    connect(mSrcToolbar, SIGNAL(copyRequest()), this, SLOT(copySourceText()));
    connect(mResToolbar, SIGNAL(copyRequest()), this, SLOT(copyResultText()));
    connect(mTranslateButton, SIGNAL(clicked()), this, SLOT(translate()));
    connect(mResText, SIGNAL(textChanged()), this, SIGNAL(finished()));

    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateResultComboBox()));

    connect(&mThread, SIGNAL(reply(QString)), this, SLOT(onResponse(QString)));

    connect(mSrcComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeHandler()));
    connect(mResComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeHandler()));
    connect(mSrcText, SIGNAL(textChanged()), this, SLOT(changeHandler()));
}

QPTranslationWidget::~QPTranslationWidget() {
    saveCfg();
}


// !!Begin API methods!!

QString QPTranslationWidget::getSourceText() const {
    return mSrcText->toPlainText();
}

QString QPTranslationWidget::getResultText() const {
    return mResText->toPlainText();
}

void QPTranslationWidget::setSourceText(const QString &text) {
    mSrcText->setPlainText(text);
}

void QPTranslationWidget::setResultText(const QString &text) {
    mResText->setPlainText(text);
}

void QPTranslationWidget::clearSourceText() {
    mSrcText->clear();
}

void QPTranslationWidget::clearResultText() {
    mResText->clear();
}

QString QPTranslationWidget::getSourceLanguageCode() {
    return mSrcComboBox->itemData(mSrcComboBox->currentIndex()).toString();
}

QString QPTranslationWidget::getResultLanguageCode() {
    return mResComboBox->itemData(mResComboBox->currentIndex()).toString();
}

void QPTranslationWidget::setSourceLanguage(const QString &code) {
    mSrcComboBox->setIndexByKey(code);
}

void QPTranslationWidget::setResulteLanguage(const QString &code) {
    mResComboBox->setIndexByKey(code);
}

QObject *QPTranslationWidget::qobject() {
    return this;
}

void QPTranslationWidget::addToolbarAction(QAction *action, TranslationWidgetToolbar toolbar) {
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

void QPTranslationWidget::swap() {
    const QString src_data = mSrcComboBox->currentData();
    const QString res_data = mResComboBox->currentData();

    mSrcComboBox->setIndexByKey(res_data);
    mResComboBox->setIndexByKey(src_data);
}

void QPTranslationWidget::undo() {
    mSrcText->undo();
}

void QPTranslationWidget::redo() {
    mSrcText->redo();
}

void QPTranslationWidget::copySourceText() {
    qApp->clipboard()->setText(mSrcText->toPlainText());
}

void QPTranslationWidget::copyResultText() {
    qApp->clipboard()->setText(mResText->toPlainText());
}

void QPTranslationWidget::translate() {
    emit started();
    emit message(tr("Translating...."));
    const QString src_text = mSrcText->toPlainText();
    mThread.query(mSrcComboBox->currentData(), mResComboBox->currentData(), src_text);

}

// !!End API methods!!

void QPTranslationWidget::setTranslatorsNames(const QStringList &lst) {
    mTranslatorsComboBox->clear();
    foreach(QString name, lst)
        mTranslatorsComboBox->addItem(name);
}

void QPTranslationWidget::setTranslator(QPTranslator &translator) {
    mTranslator = translator.instance;
    bool ret = mTranslator->load();
    if(!ret) {
        qWarning() << "Cannot load translator: " << translator.data.name;
        return;
    }
    mThread.setTranslator(mTranslator);
    mTable = translator.data.lang_table;
    mLanguageTableIsFlat = true;
    foreach(QStringList langs, mTable)
        if(!langs.isEmpty())
            mLanguageTableIsFlat = false;
    updateComboxes();
}

void QPTranslationWidget::setTranslatorIndex(int idx) {
    mTranslatorsComboBox->setCurrentIndex(idx);
}

void QPTranslationWidget::onResponse(const QString &txt) {
    emit message(tr("Translated."));
    emit finished();
    mResText->setText(txt);
}

void QPTranslationWidget::updateComboxes() {
    const QString src_code = mSrcComboBox->currentData();
    const QString res_code = mResComboBox->currentData();

    mSrcComboBox->clear();
    mResComboBox->clear();

    int counter = 0;

    foreach(QString key, mTable.keys()) {
        const QString name = QP_LANGUAGE_DB->find(key).name(mNativeNames);
        const QIcon icon = QIcon(QString(":/flags/flags/%1.png").arg(key));
        if(mEnabledLanguages.contains(key)) {
            mSrcComboBox->addItem(icon, name, key);
            if(mLanguageTableIsFlat) {
                mResComboBox->addItem(icon, name, key);
            }
        }
        counter++;
    }
    updateResultComboBox();
    mSrcComboBox->setIndexByKey(res_code);
    mResComboBox->setIndexByKey(src_code);
}

void QPTranslationWidget::updateResultComboBox() {
    const QString key = mSrcComboBox->currentData();
    if(mLanguageTableIsFlat)
        return;

    mResComboBox->clear();

    const QStringList langs = mTable[key];
    int counter = 0;
    foreach(QString lang, langs) {
        const QString name = QP_LANGUAGE_DB->find(lang).name(mNativeNames);
        const QIcon icon = QIcon(QString(":/flags/flags/%1.png").arg(lang));
        if(mEnabledLanguages.contains(lang)) {
            mResComboBox->addItem(icon, name, lang);
        }
        counter++;
    }
}

void QPTranslationWidget::saveCfg() {
    mSettings->setValue("SourceLanguage", mSrcComboBox->currentData());
    mSettings->setValue("ResultLanguage", mResComboBox->currentData());
}

void QPTranslationWidget::readCfg() {
    mSrcComboBox->setIndexByKey(mSettings->value("SourceLanguage", "").toString());
    mResComboBox->setIndexByKey(mSettings->value("ResultLanguage", "").toString());
}

void QPTranslationWidget::changeHandler() {
    if(mSrcText->toPlainText().isEmpty() || (mSrcComboBox->currentData() == mResComboBox->currentData())) {
        mTranslateButton->setDisabled(true);
    } else {
        mTranslateButton->setEnabled(true);
    }
}
