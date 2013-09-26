#pragma once

#include "api.h"
#include <QObject>

#define DICTIONARY_VERSION "0.99"

class Glosbe : public QObject, IDictionary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.dictionaries.glosbe")
    Q_INTERFACES(IDictionary)
public:
    Glosbe(QObject *parent = 0);


    LanguagePairList pairs() const {
//        LanguagePairList list;
//        for(int i = 0; i < mLangs.count(); i++) {
//            list << LanguagePair("ru", mLangs.at(i))
//                 << LanguagePair(mLangs.at(i), "ru");
//        }

//        return list;
        return mPairList;
    }

    //http://api.Glosbe.com/{api_version}/{API_key}/{dictionary}/{term}

    QStringList query( const QString &text, const LanguagePair &pair, unsigned int max_count);

    QStringList completions(const QString &str, const LanguagePair &pair) const;
    bool load(){}
    bool unload(){}
    bool isLoaded()const{return true;}


    bool isSupportCompletions() const { return true; }
private:
    static LanguagePairList mPairList;
    static QStringList mLangs;
    static QString mApiKey;
    static QString mApiVer;

    QJsonDocument queryData(const QString &str, const LanguagePair &pair) const;
};
