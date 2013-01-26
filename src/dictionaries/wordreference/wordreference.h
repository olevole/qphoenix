#ifndef WORDREFERENCE_H
#define WORDREFERENCE_H

#include "api.h"



class WordReference : public DictionaryInterface
{
public:
    WordReference();


    LanguagePairList pairs() const {
        LanguagePairList list;
        list << LanguagePair("en", "fr") << LanguagePair("fr", "en")
                << LanguagePair("es", "en") << LanguagePair("en", "es");

        return list;
    }


    //http://api.wordreference.com/{api_version}/{API_key}/{dictionary}/{term}

    DictionaryVariantList query(const LanguagePair &pair, const QString &text) ;
private:
    const QString apikey = "284e7";
    const QString version = "0.8";

};

#endif // WORDREFERENCE_H
