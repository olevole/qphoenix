
#include "languages.h"
#include <QFile>
#include <QTextStream>


LanguageEngine::LanguageEngine()
{
    QFile file(":/langmap.csv");

    if(!file.open(QFile::ReadOnly))
        qFatal("Unable to open language map! ");

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString str = in.readLine();
        QStringList result = str.split(",");

        Language lang;
        lang.setName(result.at(1));
        lang.setNativeName(result.last());

        mLangList[result.first()] = lang;
    }
    file.close();
}



//QStringList LanguageEngine::keysToNames(const QStringList &keys, const bool native) {
//    QStringList names;

//    foreach (QString key, keys) {
//        if(native)
//            names << mLangList[key].nativeName();
//        else
//            names << mLangList[key].name();
//    }
//    return names;
//}


LanguageList LanguageEngine::intersect(const LanguageList &lst1, const LanguageList &lst2) {
    return LanguageList();
}

