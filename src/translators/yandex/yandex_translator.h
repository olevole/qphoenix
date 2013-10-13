#pragma once

#include "itranslator.h"
#include <QObject>


class YandexTranslator : public QObject, ITranslator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.translators.yandex")
    Q_INTERFACES(ITranslator)
private:
    bool mLoaded;
    static QStringList mLangs;
    static QString mApiKey;
public:
    YandexTranslator(QObject *parent = 0);

    bool load() {
        if(!isLoaded()) {
            mLoaded = true;
            return true;
        }
        return false;
    }

    bool unload() {
        if(isLoaded()) {
            mLoaded = false;
            return true;
        }
        return false;
    }
    bool isLoaded() const {return mLoaded;}

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang);
};
