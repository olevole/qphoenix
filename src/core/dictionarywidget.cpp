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
#include "defines.h"
#include <QStringListModel>
#include <QRegExpValidator>
#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <QClipboard>
#include <QToolBar>
#include <QAction>





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
    mMainToolBar(new QToolBar(this))

{

//    mLanguagesComboBox->setLineEdit(new QLineEdit(this));

    mResText->setZoomFactor(0.7);


    mQueryTimer->setInterval(1000);
    mQueryTimer->setSingleShot(true);


    setName(tr("Dictionary"));

    mLineLayout->addWidget(mLanguagesComboBox);
    mLineLayout->addWidget(mSrcText);

    mMainLayout->addLayout(mLineLayout);




    QFrame *fr = new QFrame(this);
    fr->setFrameShape(QFrame::StyledPanel);
    fr->setLayout(new QVBoxLayout);
    fr->layout()->addWidget(mResText);


    mMainLayout->addWidget(fr);
    setIcon(QP_ICON("dictionary"));


    connect(mSrcText, SIGNAL(textChanged(QString)), mQueryTimer, SLOT(start()));
    connect(mQueryTimer, SIGNAL(timeout ()), this, SIGNAL(queryChanged()));


    QRegExpValidator *v = new QRegExpValidator(QRegExp("[^\Q,.\E].*"), this);

    mSrcText->setValidator(v);
    mCompleter->setModel(mCompleterModel);
    mSrcText->setCompleter(mCompleter);

    mSrcText->setPlaceholderText("Put some word here..");

    setLayout(mMainLayout);



    QAction *aZoomOut = new QAction(QP_ICON("zoom-out"), tr("Zoom Out"), this);
    QAction *aZoomIn = new QAction(QP_ICON("zoom-in"), tr("Zoom In"), this);

    aZoomIn->setAutoRepeat(true);
    aZoomOut->setAutoRepeat(true);

    connect(aZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(aZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));


    mMainToolBar->addAction(aZoomOut);
    mMainToolBar->addAction(aZoomIn);



// TODO: Check files!!!

    QFile f1(":/files/dict_template.html");
    QFile f2(":/files/dict_template_item.html");

    f1.open(QFile::ReadOnly);
    f2.open(QFile::ReadOnly);


    mBase = f1.readAll();
    mFragment = f2.readAll();




    f1.close();
    f2.close();





}


void DictionaryWidget::setCompletions(const QStringList &comp) {
    mCompleterModel->setStringList(comp);
}

void DictionaryWidget::displayData(const DictionaryVariantList &lst) {
    qDebug() << "COUNT: " << lst.count() << "SIZE: " << mBase.size();



    QString base;
    foreach(DictionaryVariant var, lst) {


        const QString src_term = var.sourceTerm();
        const QString res_term = var.resultTerm();
        const QString src_sense = var.sourceSense();
        const QString res_sense = var.resultSense();



        // TODO: REMOVE THIS DIRTY HACK!
        QString fragment = mFragment;


        base += fragment.
                replace("{SRC_TERM}", src_term).
                replace("{SRC_SENSE}", src_sense).
                replace("{RES_TERM}", res_term).
                replace("{RES_SENSE}", res_sense);



        qDebug() << "TEMPLATE: " << fragment;
    }

    QString __base = mBase;


    mResText->setHtml(__base.replace("{CONTENT}", base));
}


void DictionaryWidget::zoomIn() {
    mResText->setZoomFactor(mResText->zoomFactor()+0.1);
}


void DictionaryWidget::zoomOut() {
    mResText->setZoomFactor(mResText->zoomFactor()-0.1);

}


