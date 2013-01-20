#pragma once
#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QMap>
#include <QString>
#include <QPair>
#include <QStringList>
#include <QObject>

//typedef QPair<QString, QString> Language;

class Language;

typedef QMap<QString, Language> LanguageList;


class Language/* : public QObject */{
public:
//    explicit Language(QObject *parent = 0) :QObject(parent){};

    explicit Language(const QString &name,
                      const QString &native,
                      const QString &code)
    {
       setName(name);
       setNativeName(native);
       setCode(code);
    }

    explicit Language(){}

    QString name() const        {return mName;      }
    QString nativeName() const  {return mNativeName;}
    QString code() const        {return mCode;      }

    void setName(const QString &name)           {mName = name;          }
    void setNativeName(const QString &native)   {mNativeName = native;  }
    void setCode(const QString &code)           {mCode = code;          }
private:
    QString mName, mNativeName, mCode;
};




class LanguageEngine : public QObject {
public:
    explicit LanguageEngine(QObject *parent = 0);
    /*!
     * \brief keysForEnabled
     * \return a keys for enabled languages
     */
    LanguageList languages() const
    {return mLangList;}

    QStringList keysToNames(const QStringList &keys,
                                   const bool native = false);

private:
    LanguageList mLangList;
};


#endif // LANGUAGES_H
