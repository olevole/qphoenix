#ifndef WORDREFERENCE_H
#define WORDREFERENCE_H

#include "api.h"
#include <QObject>


class WordReference : public QObject, IDictionary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.dictionaries.wordreference")
    Q_INTERFACES(IDictionary)
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
        QStringList sl; sl << "test" << "thanks";


        QString str2("For QCompleter::PopupCompletion and QCompletion::UnfilteredPopupCompletion modes, calling this function displays the popup displaying the current completions. By default, if rect is not specified, the popup is displayed on the bottom of the widget(). If rect is specified the popup is displayed on the left edge of the rectangle.");

        return str2.split(" ");
    }
    bool load(){}
    bool unload(){}
    bool isLoaded()const{return true;}
private:
    DictionaryVariantList parse(const QByteArray content) const;
//    const QString apikey = "284e7";
//    const QString version = "0.8";

};

#endif // WORDREFERENCE_H
