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
#include <QTextEdit>
#include <QTextBrowser>

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
        clipboard = qApp->clipboard();

        connect(clipboard, SIGNAL(selectionChanged()), this, SLOT(translate()));
//        mWindowIface->translatorWidget();
//        connect(mWindowIface->translatorWidget()->instance(), SIGNAL(finished()), this, SLOT(show()));
        mIsLoaded = true;
    }
    return true;
}

bool TrayIcon::unload() {
    if(isLoaded()) {
        delete button;
        disconnect(clipboard, SIGNAL(selectionChanged()), this, SLOT(translate()));

        mIsLoaded = false;
    }
    return true;
}

void TrayIcon::setMainWindowPTR(IMainWindow *ptr) {
    mWindowIface = ptr;
}

void TrayIcon::translate() {
    mWindowIface->translatorWidget()->srcText()->setText(clipboard->text(QClipboard::Selection));
    mWindowIface->translatorWidget()->translateButton()->click();
}

void TrayIcon::show() {
    QPoint pos = QCursor::pos();
    QToolTip::showText(pos, mWindowIface->translatorWidget()->resText()->toPlainText());
}

void TrayIcon::setSettingsPTR(IConfig *ptr) {

}




//Q_EXPORT_PLUGIN2(trayicon, TrayIcon);

