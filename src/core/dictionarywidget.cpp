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

#include "dictionarywidget.h"
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

#include "defines.h"
#include "languages.h"


QString get_template(const QString &path) {
    QFile f(path);

    if(!f.open(QFile::ReadOnly))
        qFatal("Unable to open templates for dictionary!");

    QByteArray data = f.readAll();
    f.close();
    return data;
}



DictionaryWidget::DictionaryWidget(QWidget *parent) :
    QWidget(parent),
    mLanguagesComboBox(new QComboBox(this)),
    mSrcText(new QLineEdit(this)),
    mResText(new QWebView(this)),
    mLineLayout(new QHBoxLayout),
    mMainLayout(new QVBoxLayout),
    mCompleter(new QCompleter(this)),
    mCompleterModel(new QStringListModel(this)),
    mQueryTimer(new QTimer(this)),
    mMainToolBar(new QToolBar(this)),
    mTemplateRoot(get_template(":/templates/root.html")),
    mTemplateSection(get_template(":/templates/section.html")),
    mTemplateItem(get_template(":/templates/item.html")),
    mChoiceFinished(false)

{
    setName(tr("Dictionary"));
    setIcon(QP_ICON("dictionary"));
    setInputTimeout(1000);

    mResText->setZoomFactor(QP_DICT_DEFAULT_ZOOM_FACTOR);
    mMainToolBar->setMovable(false);

    mQueryTimer->setSingleShot(true);

    mLineLayout->addWidget(mLanguagesComboBox);
    mLineLayout->addWidget(mSrcText);
    mMainLayout->addLayout(mLineLayout);

    QFrame *fr = new QFrame(this);
    fr->setFrameShape(QFrame::StyledPanel);
    fr->setLayout(new QVBoxLayout);
    fr->layout()->addWidget(mResText);

    mMainLayout->addWidget(fr);
    setLayout(mMainLayout);

    // A Validator for query input
    QRegExpValidator *v = new QRegExpValidator(QRegExp("[^\Q,.\E].*"), this);
    mSrcText->setValidator(v);

    // A Completer for query input
    mCompleter->setModel(mCompleterModel);
    mSrcText->setCompleter(mCompleter);

    mSrcText->setPlaceholderText("Put some word here..");





    QAction *aZoomOut = new QAction(QP_ICON("zoom-out"), tr("Zoom Out"), this);
    QAction *aZoomIn = new QAction(QP_ICON("zoom-in"), tr("Zoom In"), this);

    aZoomIn->setAutoRepeat(true);
    aZoomOut->setAutoRepeat(true);

    mMainToolBar->addAction(aZoomOut);
    mMainToolBar->addAction(aZoomIn);


    connect(&mDictWorker, SIGNAL(reply(DictionaryVariantList)), this, SLOT(displayData(DictionaryVariantList)));
    connect(&mDictWorker, SIGNAL(reply(QStringList)), this, SLOT(setCompletions(QStringList)));

    connect(mSrcText, SIGNAL(textChanged(QString)), mQueryTimer, SLOT(start()));
    connect(mQueryTimer, SIGNAL(timeout()), this, SLOT(onQueryComp()));

    connect(mCompleter, SIGNAL(activated(QString)), this, SLOT(onQueryWord()));



    connect(mSrcText, SIGNAL(returnPressed()), this, SLOT(onQueryWord()));


    connect(aZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(aZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    mDictWorker.setTimeout(90000);




}

void DictionaryWidget::setCompletions(const QStringList &comp) {
    QStringList tmp = mCompleterModel->stringList() + comp;
    tmp.removeDuplicates();
    tmp.sort();


    mCompleterModel->setStringList(tmp);

    if(!mDictQueue.isEmpty()) {
        onQueryComp();
    } else {
        mChoiceFinished = true;
        mSrcText->completer()->complete();
    }
}

void DictionaryWidget::displayData(const DictionaryVariantList &lst) {
    qDebug() << "INSERTING WORD!";
    QString root = mTemplateRoot;
    QString sect = mTemplateSection;
    QString item = mTemplateItem;
    QString data;


    sect = sect.replace("{SECTION_ID}", mLastDictName + "_id")
            .replace("{SECTION_TITLE}", mLastDictName);

    foreach(DictionaryVariant var, lst) {
        data
                += item
                .replace("{SRC_TERM}", var.sourceTerm())
                .replace("{RES_TERM}", var.resultTerm())
                .replace("{SRC_SENSE}", var.sourceSense())
                .replace("{RES_SENSE}", var.resultSense());
        item = mTemplateItem;
    }
    sect = sect.replace("{SECTION_CONTENT}", data);
    mLastContent += sect;
    mResText->setHtml(root.replace("{ROOT_CONTENT}", mLastContent));

    if(mDictQueue.isEmpty()) {
        mChoiceFinished = false;
        mLastContent.clear();
    } else {
        onQueryWord();
    }

}

void DictionaryWidget::setDictionaryList(QList<IDictionary *> dicts) {
    Q_ASSERT(!dicts.isEmpty());

    mDicts = dicts;

    foreach(IDictionary *dict, dicts) {
        Q_ASSERT(dict->isLoaded());
        setLangPairs(dict->pairs());
    }
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
        QString first = QP_LANG_FACTORY[pair.first].name();
        QString second = QP_LANG_FACTORY[pair.second].name();

        if(!first.isEmpty() && !second.isEmpty()) {
            QString str = QString("%1 -> %2").arg(first, second);
            mLanguagesComboBox->addItem(str);
            mPairs << pair;
        } else {
            qWarning() << "This pair is not supported in" << QP_APP_NAME  << QP_APP_VERSION << ":" << pair;
        }
    }
}

void DictionaryWidget::onQueryComp() {
    if(mSrcText->text().isEmpty() || mChoiceFinished)
        return;
    qDebug() << "COMPL!";

    if(mDictQueue.isEmpty())
        mDictQueue.append(mDicts);

    IDictionary *dict = mDictQueue.dequeue();
    mDictWorker.setDictionary(dict);

    mDictWorker.queryCompletions(mPairs.at(mLanguagesComboBox->currentIndex()), mSrcText->text());
}

void DictionaryWidget::onQueryWord() {

    if(mSrcText->text().isEmpty())
        return;

    if(mDictQueue.isEmpty())
        mDictQueue.append(mDicts);



    qDebug() << "WORD!!";
    IDictionary *dict = mDictQueue.dequeue();
    mDictWorker.setDictionary(dict);
    mLastDictName = dict->name();
    mDictWorker.query(mPairs.at(mLanguagesComboBox->currentIndex()), mSrcText->text());
}
