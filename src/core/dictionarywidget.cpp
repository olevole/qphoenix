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


DictionaryWidget::DictionaryWidget(QWidget *parent) :
    QWidget(parent),
    mLanguagesComboBox(new QComboBox(this)),
    mSrcText(new QLineEdit(this)),
    mResText(new QTextBrowser(this)),
    mLineLayout(new QHBoxLayout),
    mMainLayout(new QVBoxLayout),
    mCompleter(new QCompleter(this)),
    mCompleterModel(new QStringListModel(this)),
    mQueryChangeDelay(new QTimer(this))

{

    mQueryChangeDelay->setInterval(1000);
    mQueryChangeDelay->setSingleShot(true);

    setName(tr("Dictionary"));

    mLineLayout->addWidget(mLanguagesComboBox);
    mLineLayout->addWidget(mSrcText);

    mMainLayout->addLayout(mLineLayout);
    mMainLayout->addWidget(mResText);
    setIcon(QP_ICON("dictionary"));


    connect(mSrcText, SIGNAL(textChanged(QString)), mQueryChangeDelay, SLOT(start()));
    connect(mQueryChangeDelay, SIGNAL(timeout ()), this, SIGNAL(queryChanged()));


    QRegExpValidator *v = new QRegExpValidator(QRegExp("[^\Q,.\E].*"), this);

    mSrcText->setValidator(v);
    mCompleter->setModel(mCompleterModel);
    mSrcText->setCompleter(mCompleter);

    mSrcText->setPlaceholderText("Put some word here..");

    setLayout(mMainLayout);
}


void DictionaryWidget::setCompletions(const QStringList &comp) {
    mCompleterModel->setStringList(comp);
}

void DictionaryWidget::displayData(const DictionaryVariantList &lst) {
    qDebug() << "COUNT: " << lst.count();
    mResText->clear();

    foreach(DictionaryVariant var, lst) {
        const QString text = mResText->toPlainText() + var.translation() + "|" + var.explaination() +"\n";
        qDebug() << "ITERATION: " << text;
        mResText->setPlainText(text);
    }
}
