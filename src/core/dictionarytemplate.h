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

#include <QObject>
#include "api.h"
#include <QFile>

/*!
 * \brief The DictionaryTemplate class
 * This class is a wrapper for html templates for dictionary QWebView
 * display widget.
 */

class DictionaryTemplate : public QObject {
    Q_OBJECT
public:
    explicit DictionaryTemplate(QObject *parent = 0);

    /*!
     * \brief beginSection create a document section
     * \param title section title
     * \param collapseable
     */
    void beginSection(const QString &title, const bool collapseable = true);

    /*!
     * \brief beginSection create a document section with items
     * \param lst a list of items
     * \param title title of section
     * \param collapseable could that section be collapsed?
     */
    void createSection(const QStringList &lst, const QString &title, const bool collapseable = true);

    /*!
     * \brief addItem add item for current section
     * \param var
     * \return true if beginSection was set correct
     * false - otherwise
     */
    void addItem(const QString &var);

    /*!
     * \brief endSection end of section
     */
    void endSection();

    static QString NotFound() {
        return getTemplate(":/templates/templates/notfound.html");
    }

    void clear();
    QString toHtml() const;
    QString errorString() const;
private:
    bool mLastSectionClosed;
    QString mRoot, mTitle, mSection;
    const QString mTemplateRoot;
    const QString mTemplateSection;
    const QString mTemplateItem;

    /*!
     * \brief bb2html turns bbcode string to html
     * \param bb bbcoded string
     * \return  html
     */
    static QString bb2html(const QString &bb);
    static inline QString getTemplate(const QString &path) {
        QFile file(path);
        if(!file.open(QFile::ReadOnly))
            qFatal("Unable to open templates for dictionary!");

        const QByteArray data = file.readAll();
        file.close();

        if(data.isEmpty())
            qFatal("Oops! Something is wrong with templates");
        return data;
    }
};
