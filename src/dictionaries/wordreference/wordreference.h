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
        for(int i = 0; i < other.count(); i++) {
            list << LanguagePair(first, other.at(i))
                 << LanguagePair(other.at(i), first);
        }

        return list;
    }


    //http://api.wordreference.com/{api_version}/{API_key}/{dictionary}/{term}

    DictionaryVariantList query( const QString &text, const LanguagePair &pair);

    QStringList completions(const QString &str, const LanguagePair &pair) const;
    bool load(){}
    bool unload(){}
    bool isLoaded()const{return true;}
private:
    QString first;
    QStringList other;


    QJsonDocument queryData(const QString &str, const LanguagePair &pair) const;
//    const QString apikey = "284e7";
//    const QString version = "0.8";

};

#endif // WORDREFERENCE_H
