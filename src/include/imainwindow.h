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

#ifndef MAINWINDOWINTERFACE_H
#define MAINWINDOWINTERFACE_H

#include "itranslatorwidget.h"
#include "idictionarywidget.h"
#include "info.h"


class QToolBar;
class QStatusBar;
class QComboBox;
class QToolButton;
class QPushButton;
class QTextEdit;
class QTextBrowser;
class QMenuBar;
class QLineEdit;
class QMainWindow;

class IMainWindow {
public:
    ~IMainWindow(){}
    // Signals
    virtual void currentIndexChanged(const int i) = 0;

    //Slots
    virtual void setCurrentIndex(const int i) = 0;

    // Methods
    virtual void addPage(QWidget *page) = 0;
    virtual void removePage(const QWidget *page) = 0;
    virtual QWidget *pageAt(const int i) = 0;

    virtual int currentIndex() const = 0;

    // Instances
    virtual QToolBar *toolbar() = 0;
    virtual QStatusBar *statusbar() =0;
    virtual QMenuBar   *menubar() = 0;

    virtual ITranslatorWidget *translationWidget() = 0;
    virtual IDictionaryWidget *dictionaryWidget() = 0;
    virtual QMainWindow *instance() = 0;
};


Q_DECLARE_INTERFACE(IMainWindow, "com.qphoenix.interfaces.mainwindow/1.0")


#endif // MAINWINDOWINTERFACE_H
