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

class QObject;
class QAction;

// Inherited by TranslatorWidget
class ITranslatorWidget {
public:
    virtual ~ITranslatorWidget() {}

    virtual QString getSourceText() const = 0;
    virtual QString getResultText() const = 0;

    virtual void setSourceText(const QString &text) = 0;
    virtual void setResultText(const QString &text) = 0;

    virtual void clearSourceText() = 0;
    virtual void clearResultText() = 0;

    enum TranslationWidgetToolbar {
        MainToolbar,
        SourceTextToolbar,
        ResultTextToolbar,
    };


    virtual QString getSourceLanguageCode() = 0;
    virtual QString getResultLanguageCode() = 0;

    virtual void addToolbarAction(QAction *action, TranslationWidgetToolbar toolbar) = 0;
    virtual QObject *qobject() = 0;


// Slots
    virtual void swap() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void translate() = 0;
// Signals
    virtual void finished() = 0;
};


Q_DECLARE_INTERFACE(ITranslatorWidget, "com.qphoenix.interfaces.translatorwidget/1.0")


