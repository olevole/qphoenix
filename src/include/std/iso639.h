#pragma once



#include <QMap>
#include <QHash>
#include <QPair>

/*!
 * \brief LanguageInfo
 * first string - name,
 * second one - native name
 */

//typedef QPair <QString, QString> Language;






//LanguageList QP_LANGUAGE_LIST;


//Language lang;
//lang.first = "English";
//lang.second = "Englisch";

//QP_LANGUAGE_LIST["en"] = QPair("English", "English");


class Language {
public:
    Language(const QString &name = QString(),
             const QString &native_name = QString(),
             const QString &code = QString())
    {
        setName(name);
        setNativeName(native_name);
        setCode(code);


        mCode = code;
    }

    void setNativeName(const QString &native_name)
    { mNativeName = native_name;    }

    void setName(const QString &name)
    { mName = name;                 }

    void setCode(const QString &code)
    { mCode = code;                 }


    QString nativeName() const  {return mNativeName;    }
    QString name() const        {return mName;         }
    QString code() const        {return mCode;          }
private:
    QString mName, mNativeName, mCode;

};


typedef QMap <QString, Language> LanguageList;
