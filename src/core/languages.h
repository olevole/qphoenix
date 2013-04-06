#pragma once
#ifndef LANGUAGES_H
#define LANGUAGES_H

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


#define QP_LANG_FACTORY LanguageEngine::instance()->languages()

class LanguageEngine : public QObject {
public:

    static  LanguageEngine* instance()
    {
        static QMutex mutex;
            static LanguageEngine *singleton = 0;

            if(!singleton) {
                mutex.lock();
                singleton =  new LanguageEngine;
            }
            mutex.unlock();

            return singleton;
    }

    /*!
     * \brief keysForEnabled
     * \return a keys for enabled languages
     */
    LanguageList languages() const {return mLangList;}
private:
    LanguageList mLangList;
    LanguageEngine();
    LanguageEngine(const LanguageEngine& root);
    LanguageEngine& operator=(const LanguageEngine&);
};


#endif // LANGUAGES_H
