#ifndef WORDREFERENCE_H
#define WORDREFERENCE_H

#include "api.h"
#include <QObject>


class QNetworkAccessManager;
class QJsonDocument;

class WordReference : public QObject, IDictionary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.dictionaries.wordreference")
    Q_INTERFACES(IDictionary)
public:
    WordReference(QObject *parent = 0);


    LanguagePairList pairs() const {
        LanguagePairList list;
        for(int i = 0; i < mLangs.count(); i++) {
            list << LanguagePair("en", mLangs.at(i))
                 << LanguagePair(mLangs.at(i), "en");
        }

        return list;
    }


    //http://api.wordreference.com/{api_version}/{API_key}/{dictionary}/{term}

    DictionaryVariantList query( const QString &text, const LanguagePair &pair, const int max_count);

    QStringList completions(const QString &str, const LanguagePair &pair) const;
    bool load(){}
    bool unload(){}
    bool isLoaded()const{return true;}


    bool isSupportCompletions() const { return true; }
private:
    static QStringList mLangs;
    static QString mApiKey;
    static QString mApiVer;

    QJsonDocument queryData(const QString &str, const LanguagePair &pair) const;
};

#endif // WORDREFERENCE_H
