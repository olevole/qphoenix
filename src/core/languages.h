/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

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
