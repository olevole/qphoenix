#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QMap>
#include <QString>
#include <QPair>

typedef QPair<QString, QString> Language;
typedef QMap<QString, Language> LanguageList;


class LanguageFactory {
public:
    static  LanguageList list() {
        LanguageList list;

        list["es"] = Language("Spanish", "Espaniol");
        list["ru"] = Language("Russian", "Русский");
        return list;
    }
};


#endif // LANGUAGES_H
