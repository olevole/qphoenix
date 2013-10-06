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

#pragma once

#include <QString>
#include <QStringList>

class QAction;

class IDictionaryWidget {
public:
    virtual ~IDictionaryWidget() {}

//    virtual QString getSourceLanguageCode() const = 0;
//    virtual QString getResultLanguageCode() const = 0;
//    virtual QString getResult() const = 0;
////Slots
//    virtual void query(const QString &word, const QString &src_lang, const QString &dest_lang) = 0;
////Signals
//    virtual void started() = 0;
//    virtual void finished() = 0;

};

Q_DECLARE_INTERFACE(IDictionaryWidget, "com.qphoenix.interfaces.dictionarywidget/1.0")
