#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QMap>
#include <QString>
#include <QPair>

typedef QPair<QString, QString> Language;
typedef QMap<QString, Language> LanguageList;

class LanguageFactory {
public:
    static LanguageList list() {
        LanguageList lst;

        lst["es"] = Language("Spanish", "Espaniol");
        return lst;
    }
};


#endif // LANGUAGES_H
