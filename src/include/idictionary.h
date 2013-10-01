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

#include "imodule.h"
#include "itranslator.h"
#include <QPair>
#include <QMetaType>

#define QP_DICT_MAX 1000

class QWidget;
class QString;
class IDictionary;


typedef QPair<QString, QString> LanguagePair;
typedef QList<LanguagePair> LanguagePairList;

class IDictionary : public IModule {
public:
    virtual ~IDictionary(){}

    /*!
     * \brief configWidget
     * \return a pointer to configuration widget for this dictionary (optional)
     * If you don't want to provide any config widget, just don't reimplement it
     */
    virtual QWidget *configWidget(){return NULL;}

    /*!
     * \brief query execute a dictionary query
     * \param text a query text
     * \param pair language pair (for example, en, ru)
     * \return DictionaryVariantList with dictionary reply
     */
    virtual QStringList query(const QString &text, const LanguagePair &pair, unsigned int max_count = QP_DICT_MAX)  = 0;

    /*!
     * \brief completions return a word completions variants
     * \param str str for lookup of available variants
     * \param pair a language pair for str
     * \return QStringList with a possible completions
     *
     * Note: If there's only one completion, or if dictionary doesn't support
     * this feature, this function MUST return an empty QStringList
     */
    virtual QStringList completions(const QString &str, const LanguagePair &pair) const = 0;

    /*!
     * \brief isSupportCompletions
     * \return true if dictionary support completions provided by \def completions
     * otherwise - false
     */
    virtual bool isSupportCompletions() const = 0;
};

Q_DECLARE_INTERFACE(IDictionary, "com.qphoenix.interfaces.dictionary/1.0");

