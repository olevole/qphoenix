#ifndef WORDREFERENCE_H
#define WORDREFERENCE_H

#include "api.h"
#include <QObject>


class WordReference : public QObject, DictionaryInterface
{
    Q_OBJECT
    Q_INTERFACES(DictionaryInterface)
public:
    WordReference(QObject *parent = 0);


    LanguagePairList pairs() const {
        LanguagePairList list;
        list << LanguagePair("en", "fr") << LanguagePair("fr", "en")
                << LanguagePair("es", "en") << LanguagePair("en", "es");

        return list;
    }


    //http://api.wordreference.com/{api_version}/{API_key}/{dictionary}/{term}

    DictionaryVariantList query(const LanguagePair &pair, const QString &text);

    QStringList completions(const QString &str, const LanguagePair &pair) const {
        Q_UNUSED(str)
        Q_UNUSED(pair)
        return QStringList() << "test" << "thanks";
    }
    bool load(){}
    bool unload(){}
    bool isLoaded()const{return true;}
private:
    const QString apikey = "284e7";
    const QString version = "0.8";

};

#endif // WORDREFERENCE_H
