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

#ifndef TRANSLATORWIDGETINTERFACE_H
#define TRANSLATORWIDGETINTERFACE_H


class QComboBox;
class QTextEdit;
class QTextBrowser;
class QPushButton;
class QToolButton;
class QToolBar;

// Inherited by TranslatorWidget
class TranslatorWidgetInterface {
public:



    virtual ~TranslatorWidgetInterface() {}


    virtual QComboBox   *srcComboBox() = 0;
    virtual QComboBox   *resComboBox() = 0;
    virtual QTextEdit   *srcText() = 0;
    virtual QTextBrowser*resText() = 0;
    virtual QPushButton *translateButton() = 0;
    virtual QToolButton *swapButton() = 0;


    virtual QToolBar    *srcToolbar() = 0;
    virtual QToolBar    *resToolbar() = 0;

    virtual void swap() = 0;
//private:
//    virtual void copySrcText() = 0;
//    virtual void copyResText() = 0;

};


Q_DECLARE_INTERFACE(TranslatorWidgetInterface, "com.qphoenix.interfaces.translatorwidget/1.0")


#endif // TRANSLATORWIDGETINTERFACE_H
