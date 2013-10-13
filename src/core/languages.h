#pragma once

#include <QMap>
#include <QString>
#include <QPair>
#include <QList>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include <QMutex>

class Language;
typedef QList<Language> LanguageList;

class Language {
public:
    explicit Language(const QString &code, const QString &name, const QString &native)
    {
        mCode = code;
        mName = name;
        mNativeName = native;
    }

    explicit Language() {}

    QString name(bool native = false) {
        return native ? mNativeName : mName;
    }

    QString code() const {return mCode;}
private:
    QString mName;
    QString mNativeName;
    QString mCode;
};

#define QP_LANGUAGE_DB LanguageDB::instance()

class LanguageDB : public QObject {
    Q_OBJECT
public:
    static  LanguageDB* instance()
    {
        static QMutex mutex;
        static LanguageDB *singleton = 0;

        if(!singleton) {
            mutex.lock();
            singleton =  new LanguageDB;
            mutex.unlock();
        }
        return singleton;
    }

    Language find(const QString &key) const {
        foreach(Language lang, mLangList) {
            if(lang.code() == key)
                return lang;
        }
        return Language();
    }

    LanguageList languages() {return mLangList;}
private:
    LanguageList mLangList;
    LanguageDB();
    LanguageDB(const LanguageDB& root);
    LanguageDB& operator=(const LanguageDB&);
};
