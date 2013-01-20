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




class LanguageEngine : public QObject {
public:
    explicit LanguageEngine(QObject *parent = 0);


    /*!
     * \brief keysForEnabled
     * \return a keys for enabled languages
     */
    LanguageList languages() const {return mLangList;}

    QStringList keysToNames(const QStringList &keys, const bool native = false);


    static LanguageList intersect(const LanguageList &lst1, const LanguageList &lst2);

private:
    LanguageList mLangList;
};


#endif // LANGUAGES_H
