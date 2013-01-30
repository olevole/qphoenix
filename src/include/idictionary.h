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

class QWidget;
class QString;
class DictionaryItem;


typedef QPair<QString, QString> LanguagePair;
typedef QList<LanguagePair> LanguagePairList;
class DictionaryVariant;
typedef QList<DictionaryVariant> DictionaryVariantList;

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

class DictionaryVariant
{
public:
    DictionaryVariant(const Abbreviation abbr, const QString &src_word,
                      const QString &expl, const QString &trans) {
        setAbbr(abbr);
        setSourceWord(src_word);
        setExplaination(expl);
        setTranslation(trans);
    }


    void setAbbr(const Abbreviation abbr) { mAbbr = abbr;}
    void setSourceWord(const QString &word) { mSrcWord = word;}
    void setExplaination(const QString &expl) {mExpl = expl;}
    void setTranslation(const QString &tr) {mTrans = tr;}

    Abbreviation abbr() const   { return mAbbr;     }
    QString sourceWord() const  { return mSrcWord;  }
    QString explaination() const{ return mExpl;     }
    QString translation() const { return mTrans;    }
private:
    Abbreviation mAbbr;
    QString mSrcWord, mExpl, mTrans;
};


class IDictionary : public IModule {
public:
    virtual ~IDictionary(){}

    virtual QWidget *configWidget()
    {return new QWidget();}

    virtual LanguagePairList pairs() const = 0;
    virtual DictionaryVariantList query(const LanguagePair &pair, const QString &text)  = 0;
    virtual QStringList completions(const QString &str, const LanguagePair &pair) const = 0;


};

Q_DECLARE_INTERFACE(IDictionary, "com.qphoenix.interfaces.dictionary/1.0");

