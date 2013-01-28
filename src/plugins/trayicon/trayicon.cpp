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

#include "trayicon.h"
#include <QtGui>
#include <QPushButton>
#include <QToolBar>
#include <QAction>

#include <QToolTip>

TrayIcon::TrayIcon(QObject *parent) :
    QObject(parent),
    mIsLoaded(false)
{
    this->setName("Selection Buffer");
    this->setDescription("This is my best plugin!");
    this->setVersion("0.999999");
}


bool TrayIcon::load() {
    if(!isLoaded()) {
        button = new QPushButton;
        mIsLoaded = true;
    }
    return true;
}

bool TrayIcon::unload() {
    if(isLoaded()) {
        delete button;
        mIsLoaded = false;
    }
    return true;
}

void TrayIcon::setMainWindowPTR(MainWindowInterface *ptr) {
    mWindowIface = ptr;
//    ptr->setCurrentPage(1);
//    ptr->toolbar()->addWidget(button);

//    ptr->dictionaryWidget()->srcText()->setText("Test");

    clipboard = qApp->clipboard();

    connect(clipboard, SIGNAL(selectionChanged()), this, SLOT(translate()));
}

void TrayIcon::translate() {
    mWindowIface->translationWidget()->srcText()->setText(clipboard->text(QClipboard::Selection));
    mWindowIface->translationWidget()->translateButton()->click();

    QPoint pos = QCursor::pos();

    QToolTip::showText(pos, mWindowIface->translationWidget()->resText()->toPlainText());
}

void TrayIcon::setSettingsPTR(ConfigInterface *ptr) {

}




Q_EXPORT_PLUGIN2(trayicon, TrayIcon);

