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

class QWidget;
class QString;
class DictionaryItem;


typedef QPair<QString, QString> LanguagePair;
typedef QList<LanguagePair> LanguagePairList;
class DictionaryVariant;
typedef QList<DictionaryVariant> DictionaryVariantList;






class DictionaryVariant
{
public:
    DictionaryVariant(const QString &src_term, const QString &res_term,
                      const QString &src_sense, const QString &res_sense) {
        setSourceTerm(src_term);
        setResultTerm(res_term);
        setSourceSense(src_sense);
        setResultSense(res_sense);
    }

    void setSourceTerm(const QString &term){mSrcTerm = term;}
    void setResultTerm(const QString &term){mResTerm = term;}

    void setSourceSense(const QString &sense){mSrcSense = sense;}
    void setResultSense(const QString &sense){mResSense = sense;}

    QString sourceTerm() const {return mSrcTerm;}
    QString resultTerm() const {return mResTerm;}

    QString sourceSense() const{return mSrcSense;}
    QString resultSense() const{return mResSense;}
private:
    QString mSrcSense, mResSense, mSrcTerm, mResTerm;

};


class IDictionary : public IModule {
public:
    virtual ~IDictionary(){}


    /*!
     * \brief configWidget
     * \return a pointer to configuration widget for this dictionary (optional)
     * If you don't want to provide any config widget, just don't reimplement it
     */

    virtual QWidget *configWidget()
    {return new QWidget();}


    /*!
     * \brief pairs
     * \return List of supported language pairs
     */
    virtual LanguagePairList pairs() const = 0;

    /*!
     * \brief query execute a dictionary query
     * \param text a query text
     * \param pair language pair (for example, en, ru)
     * \return DictionaryVariantList with dictionary reply
     */
    virtual DictionaryVariantList query(const QString &text, const LanguagePair &pair)  = 0;

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




};

Q_DECLARE_INTERFACE(IDictionary, "com.qphoenix.interfaces.dictionary/1.0");

