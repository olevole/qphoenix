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

#include <QComboBox>
#include <QLineEdit>
#include <QTextBrowser>
#include <QToolButton>
#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCompleter>
#include <QStringListModel>
#include <QRegExpValidator>
#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <QClipboard>
#include <QToolBar>
#include <QAction>
#include <QFile>
#include <QTime>
#include <QWebFrame>
#include "dictionarywidget.h"
#include "dictionarytemplate.h"
#include "defines.h"
#include "languages.h"

DictionaryQueryLine::DictionaryQueryLine(QPDictionaryThread *thread, QWidget *parent)
    : QLineEdit(parent),
      mQueryTimer(new QTimer(this)),
      mCompleter(new QCompleter(this)),
      mModel(new QStringListModel(this)),
      mThread(thread)
{
    mModel->setStringList(QStringList() << "a" << "b" << "foo" << "bar");
    mCompleter->setModel(mModel);
    setCompleter(mCompleter);
    setPlaceholderText(tr("Input text..."));
}

DictionaryWidget::DictionaryWidget(QWidget *parent) :
    QWidget(parent),
    mLock(false),
    mIsEmpty(true),
    mMainToolBar(new QToolBar(this)),
    mLanguagesComboBox(new QComboBox(this)),
    mSrcText(new DictionaryQueryLine(&mDictThread, this)),
    mResText(new QWebView(this)),
    mTemplate(new DictionaryTemplate(this))
{

    mResText->setZoomFactor(QP_DICT_DEFAULT_ZOOM_FACTOR);
    mMainToolBar->addSeparator();
    mMainToolBar->setMovable(false);

    QHBoxLayout *mLineLayout = new QHBoxLayout;
    QVBoxLayout *mMainLayout = new QVBoxLayout;

    mLineLayout->addWidget(mLanguagesComboBox);
    mLineLayout->addWidget(mSrcText);
    mMainLayout->addLayout(mLineLayout);

    QFrame *fr = new QFrame(this);
    fr->setFrameShape(QFrame::StyledPanel);
    fr->setLayout(new QVBoxLayout);
    fr->layout()->addWidget(mResText);

    mMainLayout->addWidget(fr);
    setLayout(mMainLayout);

    QAction *aZoomOut = new QAction(QP_ICON("zoom-out"), tr("Zoom Out"), this);
    QAction *aZoomIn = new QAction(QP_ICON("zoom-in"), tr("Zoom In"), this);
    aZoomIn->setAutoRepeat(true);
    aZoomOut->setAutoRepeat(true);
    mMainToolBar->addAction(aZoomOut);
    mMainToolBar->addAction(aZoomIn);

    connect(&mDictThread, SIGNAL(reply(QStringList, QString)), this, SLOT(displayData(QStringList,QString)));
    connect(&mDictThread, SIGNAL(reply(QStringList)), this, SLOT(setCompletions(QStringList)));
    connect(&mDictThread, SIGNAL(finished()), this, SLOT(onFinish()));

    connect(aZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(aZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    mDictThread.setTimeout(QP_DICTIONARY_TIMEOUT);
}

// API Methods
QString DictionaryWidget::getSourceText() const {
    return mSrcText->text();
}

QString DictionaryWidget::getResultText() const {
    return mResText->page()->mainFrame()->toHtml();
}

void DictionaryWidget::clearSourceText() {
    mSrcText->clear();
}

void DictionaryWidget::clearResultText() {
    mResText->setHtml("");
}

void DictionaryWidget::undo() {
    mSrcText->undo();
}

void DictionaryWidget::redo() {
    mSrcText->redo();
}

// End of API methods


void DictionaryWidget::displayData(const QStringList &lst, const QString &name) {
    if(!lst.isEmpty()) {
        mIsEmpty = false;
        mTemplate->createSection(lst, name);
        mResText->setHtml(mTemplate->toHtml());
    }
}

void DictionaryWidget::setNativeNames(bool b) {
    mNativeNames = b;
}

void DictionaryWidget::setMaxItems(unsigned int count) {
    mMaxItemCount = count;
}

void DictionaryWidget::setDictionaryList(QPDictionaryList dicts) {
    LanguagePairList list;

    if(dicts.isEmpty()) {
        mSrcText->setDisabled(true);
        qWarning() << "Warning! Dictionaries is empty!";
        return;
    }

    mDicts = dicts;
    mDictThread.setDictionaryList(mDicts);
    foreach(QPDictionary dict, dicts) {
        LanguageTable table = dict.data.lang_table;
        foreach(QString key, table.keys()) {
            const QStringList values = table[key];
            foreach(QString value, values) {
                list << LanguagePair(key, value);
                list << LanguagePair(value, key);
            }
        }
    }
    qSort(list);
    setLanguagePairs(list);
}

void DictionaryWidget::zoomIn() {
    mResText->setZoomFactor(mResText->zoomFactor()+0.1);
}

void DictionaryWidget::zoomOut() {
    mResText->setZoomFactor(mResText->zoomFactor()-0.1);
}

void DictionaryWidget::setLanguagePairs(const LanguagePairList &lst) {
    mLanguagesComboBox->clear();
    foreach(LanguagePair pair, lst) {
        QString first, second;
        first = QP_LANGUAGE_DB->find(pair.first).name(mNativeNames);
        second = QP_LANGUAGE_DB->find(pair.second).name(mNativeNames);

        if(!first.isEmpty() && !second.isEmpty()) {
            QString str = QString("%1-%2").arg(first, second);
            mLanguagesComboBox->addItem(str);
            mPairs << pair;
        } else {
            qWarning() << "This language pair is not supported in " << QP_APP_NAME  << QP_APP_VERSION << ":" << pair;
        }
    }
}

void DictionaryWidget::onQueryComp() {
    if(!mLock)
        mDictThread.queryCompletions(mPairs.at(mLanguagesComboBox->currentIndex()).first,
                                     mPairs.at(mLanguagesComboBox->currentIndex()).second,
                                     mSrcText->text());
}

void DictionaryWidget::onQueryWord() {
    mIsEmpty = true;
    mLock = true;
    mDictThread.query(mPairs.at(mLanguagesComboBox->currentIndex()).first,
                      mPairs.at(mLanguagesComboBox->currentIndex()).second,
                      mSrcText->text());
}

void DictionaryWidget::onFinish() {
    mLock = false;
    if(mIsEmpty) {
        mResText->setHtml(DictionaryTemplate::NotFound());
        mResText->update();
    }
    mTemplate->clear();
}
