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

#include "basemodule.h"
#include "translatorinterface.h"

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
    DictionaryVariant() {}
    enum Abbreviation {
        //!< english
        Verb = 1,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Preposition,
        Conjunction,
        Interjection,
        NoAbbreviation = 1000
    };


    Abbreviation abbr() const;
    QString sourceWord() const;
    QString explaination() const;
    QString translation() const;
};




class DictionaryInterface : public BaseModule {
public:
    virtual ~DictionaryInterface(){}

    virtual QWidget *configWidget()
    {return new QWidget();}

    virtual LanguagePairList pairs() const = 0;
    virtual DictionaryVariantList query(const LanguagePair &pair, const QString &text)  = 0;
};

Q_DECLARE_INTERFACE(DictionaryInterface, "com.qphoenix.interfaces.dictionary/1.0");

