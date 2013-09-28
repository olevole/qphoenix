#pragma once

#include <QMap>
#include <QString>
#include <QPair>
#include <QStringList>
#include <QObject>
#include <QDebug>
#include <QMutex>

class Language;
typedef QMap<QString, Language> LanguageList;

class Language {
public:
    explicit Language(const QString &name,
                      const QString &native)
    {
        mName = name;
        mNativeName = native;
    }

    explicit Language() {}

    QString name(bool native = false) {
        return native ? mNativeName : mName;
    }

    QString name() const {return mName;}
private:
    QString mName, mNativeName;
};

#define QP_LANGUAGE_DB LanguageDB::instance()

class LanguageDB : public QObject {
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
        return mLangList[key];
    }

    /*!
     * \brief keysForEnabled
     * \return a keys for enabled languages
     */
    LanguageList languages() const {return mLangList;}
private:
    LanguageList mLangList;
    LanguageDB();
    LanguageDB(const LanguageDB& root);
    LanguageDB& operator=(const LanguageDB&);
};
