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

#ifndef TRANSLATORINTERFACE_H
#define TRANSLATORINTERFACE_H

#include <QMap>
#include "basemodule.h"

class QWidget;
class QString;


/*!
 * \brief LanguageTable
 *
 * Provie a table for translators without linear
 * translation betwen languages. (for example, you
 * can translate English word to German or Russian,
 * but you can translate Russian word only to english
 * The key QString is a source langauge, the value -
 * possible result languages. This hash must contain
 * ONLY keys for LanguageList, not a values!
 */
typedef QMap <QString, QStringList> LanguageTable;


/*!
 * \brief LanguageList
 * The key is a language name (e.g. "English")
 * The value - language code used for query.
 * See std/iso639.h for details.
 */
typedef QMap <QString, QString> LanguageList;



class TranslatorInterface : public BaseModule {
public:
    virtual ~TranslatorInterface(){}


    /*!
     * \brief configWidget
     * \return pointer to Translator config widget
     */
    virtual QWidget *configWidget() = 0;


    /*!
     * \brief isLinear
     * \return true if supported pairs are linear
     * or false if not. See \brief LanguageTable
     * for details
     */
    virtual bool isLinear() const = 0;



    virtual LanguageTable table() const = 0;
//    virtual LanguageList  languages() const = 0;


    virtual QString translate(const QString &src_text, const QString &src_lang,
                               const QString &dest_lang) = 0;


};


Q_DECLARE_INTERFACE(TranslatorInterface, "com.qphoenix.interfaces.translator/1.0");




#endif // TRANSLATORINTERFACE_H
