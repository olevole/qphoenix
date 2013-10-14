#pragma once

#include "api.h"
#include <QObject>

#define DICTIONARY_VERSION "0.99"

class QNetworkAccessManager;
class QJsonDocument;

class WordReference : public QObject, IDictionary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.dictionaries.wordreference")
    Q_INTERFACES(IDictionary)
public:
    WordReference(QObject *parent = 0);

    QStringList query(const QString &text, const QString &src_lang, const QString &dest_lang, unsigned int max_count);
    QStringList completions(const QString &str, const QString &src_lang, const QString &dest_lang) const;

    bool load() {return true;}
    bool unload() {return true;}
    bool isLoaded() const {return true;}

    bool isSupportCompletions() {return true;}
private:
    static QString mApiKey;
    static QString mApiVer;

    QJsonDocument queryData(const QString &str, const QString &src_lang, const QString &dest_lang) const;
};
