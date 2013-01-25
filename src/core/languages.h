#pragma once
#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QMap>
#include <QString>
#include <QPair>
#include <QStringList>
#include <QObject>


class Language;

typedef QMap<QString, Language> LanguageList;


class Language {
public:

    explicit Language(const QString &name,
                      const QString &native)
    {
       setName(name);
       setNativeName(native);
    }

    explicit Language(){}

    QString name() const        {return mName;      }
    QString nativeName() const  {return mNativeName;}

    void setName(const QString &name)           {mName = name;          }
    void setNativeName(const QString &native)   {mNativeName = native;  }
private:
    QString mName, mNativeName;
};


#define QP_LANG_FACTORY LanguageEngine::instance()

class LanguageEngine : public QObject {
public:
//    explicit LanguageEngine(QObject *parent = 0);

    static const LanguageEngine& instance()
    {
            static LanguageEngine theSingleInstance;
            return theSingleInstance;
    }

    /*!
     * \brief keysForEnabled
     * \return a keys for enabled languages
     */
    LanguageList languages() const {return mLangList;}

//    QStringList keysToNames(const QStringList &keys, const bool native = false);

    QString nameToKey(const QString &name, const bool native = false) const {

        const QStringList keys = mLangList.keys();

        foreach(QString key, keys) {
            const QString mname = native ? mLangList[key].nativeName() :    mLangList[key].name();
            if(name == mname)
                return key;


        }

//        for(LanguageList::iterator i = mLangList.begin(); i != mLangList.end(); i++) {
//            const QString _name = native ? i.value().name() : i.value().nativeName();
//            if(_name == name)
//                return i.key();
//        }
    }


//    static LanguageList intersect(const LanguageList &lst1, const LanguageList &lst2);

private:
    LanguageList mLangList;
        LanguageEngine();
        LanguageEngine(const LanguageEngine& root);
        LanguageEngine& operator=(const LanguageEngine&);
};


#endif // LANGUAGES_H
