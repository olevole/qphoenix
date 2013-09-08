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

#include <QtGui>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include <QTextBrowser>
#include <QToolTip>

#include "translationwidget.h"
#include "itranslatorwidget.h"
#include "scanner.h"

Scanner::Scanner(QObject *parent) :
    QObject(parent),
    mIsLoaded(false)
{
    this->setName("Scanner");
    this->setDescription("Scans selection buffer for text");
    this->setVersion("0.999999");
}

bool Scanner::load() {
    if(!isLoaded()) {
        button = new QPushButton;
        clipboard = qApp->clipboard();
        connect(clipboard, SIGNAL(selectionChanged()), this, SLOT(translate()));
        mIsLoaded = true;
    }
    return true;
}

bool Scanner::unload() {
    if(isLoaded()) {
        delete button;
        disconnect(clipboard, SIGNAL(selectionChanged()), this, SLOT(translate()));
        mIsLoaded = false;
    }
    return true;
}

void Scanner::translate() {
    mConnector.QP_TRANSLATOR_WIDGET->srcText()->setText(clipboard->text(QClipboard::Selection));
}

void Scanner::show() {
    QPoint pos = QCursor::pos();
    QToolTip::showText(pos, mConnector.QP_TRANSLATOR_WIDGET->resText()->toPlainText());
}


void Scanner::setPluginConnector(PluginConnector connector) {
    mConnector = connector;
}

//Q_EXPORT_PLUGIN2(trayicon, TrayIcon);

