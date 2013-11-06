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



DictionaryWidget::DictionaryWidget(QWidget *parent) :
    QWidget(parent),
    mState(Idle),

    mIsEmpty(true),
    mMainToolBar(new QToolBar(this)),
    mLanguagesComboBox(new QComboBox(this)),
    mCompleter(new QCompleter(this)),
    mSrcText(new QLineEdit(this)),
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

    mSrcText->setCompleter(mCompleter);

    connect(mSrcText, SIGNAL(textChanged(QString)), &mTimer, SLOT(start()));
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(requestCompletions()));

    connect(mCompleter, SIGNAL(activated(QString)), this, SLOT(requestData(QString)));
    connect(mSrcText, SIGNAL(returnPressed()), this, SLOT(requestData()));

    connect(&mThread, SIGNAL(reply(QStringList)), this, SLOT(showCompletions(QStringList)));
    connect(&mThread, SIGNAL(reply(QStringList,QString)), this, SLOT(showData(QStringList,QString)));
    connect(&mThread, SIGNAL(finished()), this, SLOT(finish()));

    connect(aZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(aZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    mTimer.setInterval(1000);
    mTimer.setSingleShot(true);
    mThread.setTimeout(QP_DICTIONARY_TIMEOUT);
}

// API Methods

QString DictionaryWidget::getSourceLanguageCode() const {
    return mPairs.at(mLanguagesComboBox->currentIndex()).first;
}

QString DictionaryWidget::getResultLanguageCode() const {
    return mPairs.at(mLanguagesComboBox->currentIndex()).second;
}

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


void DictionaryWidget::showData(const QStringList &lst, const QString &name) {
    if(!lst.isEmpty() && mState == WaitingResponse) {
        mIsEmpty = false;
        mTemplate->createSection(lst, name);
        mResText->setHtml(mTemplate->toHtml());
    }
}

void DictionaryWidget::showCompletions(const QStringList &comp) {
    if(mState == WaitingCompletions) {
        mTimer.stop();
        if(comp.size() <= 1) {
            requestData();
        } else {
            mCompleter->setModel(new QStringListModel(comp));
            mCompleter->complete();
        }
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

    mSrcText->setDisabled(dicts.isEmpty());
    if(dicts.isEmpty())
        return;

    mDicts = dicts;
    mThread.setDictionaryList(mDicts);
    foreach(QPDictionary dict, dicts) {
        LanguageTable table = dict.data.lang_table;
        foreach(QString key, table.keys()) {
            const QStringList values = table[key];
            foreach(QString value, values) {
                LanguagePair pair1(key, value);
                LanguagePair pair2(value, key);
                if(!list.contains(pair1))
                    list << pair1;
                if(!list.contains(pair2))
                    list << pair2;
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

void DictionaryWidget::requestCompletions() {
    if(mState == Idle) {
        mState = WaitingCompletions;
        mThread.queryCompletions(getSourceLanguageCode(), getResultLanguageCode(), mSrcText->text());
    }
}

void DictionaryWidget::requestData(const QString &word) {
    if(mState == Idle || mState == WaitingCompletions) {
        mTimer.stop();
        mState = WaitingResponse;
        mThread.query(getSourceLanguageCode(), getResultLanguageCode(), word);
    }
}

void DictionaryWidget::requestData() {
    requestData(mSrcText->text());
}

void DictionaryWidget::finish() {
    if(mState != WaitingResponse)
        return;

    mState = Idle;
    mTemplate->clear();
    mThread.quit();

    if(mIsEmpty) {
        mResText->setHtml(DictionaryTemplate::NotFound());
        mResText->update();
    }
}


