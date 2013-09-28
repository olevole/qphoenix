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
#include "dictionarywidget.h"
#include "dictionarytemplate.h"
#include "defines.h"
#include "languages.h"

DictionaryWidget::DictionaryWidget(QWidget *parent) :
    QWidget(parent),
    mLanguagesComboBox(new QComboBox(this)),
    mSrcText(new QLineEdit(this)),
    mResText(new QWebView(this)),
    mCompleter(new QCompleter(this)),
    mCompleterModel(new QStringListModel(this)),
    mQueryTimer(new QTimer(this)),
    mMainToolBar(new QToolBar(this)),
    mLock(false),
    mIsEmpty(true),
    mTemplate(new DictionaryTemplate(this))

{
    setName(tr("Dictionary"));
    setIcon(QP_ICON("dictionary"));
    setInputTimeout(1000);

    mResText->setZoomFactor(QP_DICT_DEFAULT_ZOOM_FACTOR);
    mMainToolBar->setMovable(false);
    mQueryTimer->setSingleShot(true);

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

//     A Validator for query input
    QRegExpValidator *v = new QRegExpValidator(QRegExp("[^\\Q ,.\E].*"), this);
    mSrcText->setValidator(v);

    // A Completer for query input
    mCompleter->setModel(mCompleterModel);
    mSrcText->setCompleter(mCompleter);

    mSrcText->setPlaceholderText(tr("Enter word here.."));

    QAction *aZoomOut = new QAction(QP_ICON("zoom-out"), tr("Zoom Out"), this);
    QAction *aZoomIn = new QAction(QP_ICON("zoom-in"), tr("Zoom In"), this);
    aZoomIn->setAutoRepeat(true);
    aZoomOut->setAutoRepeat(true);
    mMainToolBar->addAction(aZoomOut);
    mMainToolBar->addAction(aZoomIn);

    connect(&mDictWorker, SIGNAL(reply(QStringList, QString)), this, SLOT(displayData(QStringList,QString)));
    connect(&mDictWorker, SIGNAL(reply(QStringList)), this, SLOT(setCompletions(QStringList)));
//    connect(&mDictWorker, SIGNAL(reply(QStringList)), this, SLOT(setCompletions(QStringList)));
    connect(&mDictWorker, SIGNAL(finished()), this, SLOT(onFinish()));
    connect(mSrcText, SIGNAL(textChanged(QString)), mQueryTimer, SLOT(start()));
    connect(mQueryTimer, SIGNAL(timeout()), this, SLOT(onQueryComp()));
    connect(mSrcText, SIGNAL(textChanged(QString)), mQueryTimer, SLOT(start()));
    connect(mQueryTimer, SIGNAL(timeout()), this, SLOT(onQueryComp()));
    connect(mCompleter, SIGNAL(activated(QString)), this, SLOT(onQueryWord()));
    connect(mSrcText, SIGNAL(returnPressed()), this, SLOT(onQueryWord()));
    connect(aZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(aZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    mDictWorker.setTimeout(QP_DICTIONARY_TIMEOUT);
}

void DictionaryWidget::setCompletions(const QStringList &comp) {
    QStringList tmp = mCompleterModel->stringList() + comp;
    tmp.removeDuplicates();
    tmp.sort();
    mCompleterModel->setStringList(tmp);
    mSrcText->completer()->complete();
}

void DictionaryWidget::displayData(const QStringList &lst, const QString &name) {
    if(!lst.isEmpty()) {
        mIsEmpty = false;
        qDebug() << "NOTEMPTY" << lst[1];
        mTemplate->createSection(lst, name);
        mResText->setHtml(mTemplate->toHtml());
    }
}

void DictionaryWidget::setDictionaryList(QList<IDictionary *> dicts) {
    LanguagePairList list;

    if(dicts.isEmpty()) {
        mSrcText->setDisabled(true);
        qWarning() << "Warning! Dictionaries is empty!";
        return;
    }

    mDicts = dicts;
    mDictWorker.setDictionaryList(mDicts);
    foreach(IDictionary *dict, dicts) {
        foreach(LanguagePair pair, dict->pairs()) {
            if(!list.contains(pair))
                list.append(pair);
        }
    }
    qSort(list);
    setLangPairs(list);
}

void DictionaryWidget::zoomIn() {
    mResText->setZoomFactor(mResText->zoomFactor()+0.1);
}

void DictionaryWidget::zoomOut() {
    mResText->setZoomFactor(mResText->zoomFactor()-0.1);
}

void DictionaryWidget::setLangPairs(const LanguagePairList lst) {
    mLanguagesComboBox->clear();
    foreach(LanguagePair pair, lst) {
        QString first, second;
        first = QP_LANGUAGE_DB->find(pair.first).name(mNativeNames);
        second = QP_LANGUAGE_DB->find(pair.second).name(mNativeNames);

        if(!first.isEmpty() && !second.isEmpty()) {
            qDebug() << "ADD PAIR: " << pair;
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
        mDictWorker.queryCompletions(mPairs.at(mLanguagesComboBox->currentIndex()), mSrcText->text());
}

void DictionaryWidget::onQueryWord() {
    mIsEmpty = true;
    mLock = true;
    mDictWorker.query(mPairs.at(mLanguagesComboBox->currentIndex()), mSrcText->text());
}

void DictionaryWidget::onFinish() {
    mLock = false;
    mQueryTimer->stop();
    if(mIsEmpty) {
        mResText->setHtml(DictionaryTemplate::NotFound());
        mResText->update();
    }
    mTemplate->clear();
    mCompleterModel->setStringList(QStringList());
}
