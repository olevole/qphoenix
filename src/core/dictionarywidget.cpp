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



DictionaryWidget::DictionaryWidget(QWidget *parent) :
    QWidget(parent),
    mSrcComboBox(new QComboBox(this)),
    mResComboBox(new QComboBox(this)),
    mSrcText(new QLineEdit(this)),
    mResText(new QTextBrowser(this)),
    mSwapButton(new QToolButton(this)),
    mGroupbox(new QGroupBox(this)),
    mQueryLabel(new QLabel(tr("Query"), this)),
    mLineLayout(new QHBoxLayout),
    mLanguagesLayout(new QHBoxLayout),
    mMainLayout(new QVBoxLayout)
{

    mGroupbox->setTitle(tr("Result"));
    mGroupbox->setLayout(new QHBoxLayout);
    mGroupbox->layout()->addWidget(mResText);

    mLanguagesLayout->addWidget(mSrcComboBox);
    mLanguagesLayout->addWidget(mSwapButton);
    mLanguagesLayout->addWidget(mResComboBox);


    mLineLayout->addWidget(mQueryLabel);
    mLineLayout->addWidget(mSrcText);

    mMainLayout->addLayout(mLineLayout);
    mMainLayout->addLayout(mLanguagesLayout);
    mMainLayout->addWidget(mGroupbox);

    setLayout(mMainLayout);
}
