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
#include <QWidget>
#include "imodule.h"



/*!
 * \brief LanguageTable
 *
 * Provide a table for translators without linear
 * translation betwen languages. (for example, you
 * can translate English word to German or Russian,
 * but you can translate Russian word only to English
 * The key QString is a source langauge, the value -
 * possible result languages. This hash must contain
 * ONLY keys for LanguageList, not a values!
 * The key's MUST be an ISO 639-1 codes.
 * More information: en.wikipedia.org/wiki/List_of_ISO_639-1_codes
 */
typedef QMap <QString, QStringList> LanguageTable;





class ITranslator : public IModule {
public:
    virtual ~ITranslator(){}


    /*!
     * \brief configWidget
     * \return pointer to Translator config widget
     */
    virtual QWidget *configWidget()
    {return new QWidget();        }


    /*!
     * \brief table
     * \return  a table with supported language directions
     */
    virtual LanguageTable table() const = 0;


    /*!
     * \brief translate
     * \param src_text Source text
     * \param src_lang Source language name
     * \param dest_lang Destination language name
     * \return Translation result
     */
    virtual QString translate(const QString &src_text, const QString &src_lang,
                               const QString &dest_lang) = 0;
};


Q_DECLARE_INTERFACE(ITranslator, "com.qphoenix.interfaces.translator/1.0");




#endif // TRANSLATORINTERFACE_H
