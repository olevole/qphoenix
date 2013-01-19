#pragma once
#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QMap>
#include <QString>
#include <QPair>
#include <QStringList>

typedef QPair<QString, QString> Language;
typedef QMap<QString, Language> LanguageList;



class LanguageFactory {
public:
    static  LanguageList list() {
        LanguageList list;

        list["es"] = Language("Spanish", "Espaniol");
        list["ru"] = Language("Russian", "Русский");
        list["de"] = Language("German", "Deutsche");
        list["en"] = Language("English", "English");
        return list;
    }

//    static QStringList keysToNativeNames(const QStringList &keys, const LanguageList &list) {
//        QStringList nativeNames;

//        foreach (QString key, keys) {
//            nativeNames << list[key].second;
//        }
//        return nativeNames;
//    }
    static QStringList keysToNames(const QStringList &keys,
                                   const LanguageList &list,
                                   const bool native = false) {
        QStringList names;

        foreach (QString key, keys) {
            if(native)
                names << list[key].second;
            else
                names << list[key].first;
        }
        return names;
    }



};


static const LanguageList QP_LANG_LIST = LanguageFactory::list();


class LanguageEngine {
public:
    /*!
     * \brief keysForEnabled
     * \return a keys for enabled languages
     */
    QStringList keysForEnabled() const;
    LanguageList languages() const;

    QStringList keysToNames(const QStringList &keys,
                                   const bool native = false) {
        QStringList names;

        foreach (QString key, keys) {
            if(native)
                names << mLangList[key].second;
            else
                names << mLangList[key].first;
        }
        return names;
    }

private:
    LanguageList mLangList;
};


#endif // LANGUAGES_H
