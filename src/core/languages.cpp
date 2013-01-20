
#include "languages.h"
#include <QFile>
#include <QTextStream>


LanguageEngine::LanguageEngine(QObject *parent)
    :QObject(parent)
{
    QFile file(":/langmap.csv");

    if(!file.open(QFile::ReadOnly))
        qFatal("Unable to open language map! ");

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString str = in.readLine();
        QStringList result = str.split(",");

        Language lang;
        lang.setCode(result.first());
        lang.setName(result.at(1));
        lang.setNativeName(result.last());

        mLangList[result.first()] = lang;
    }
    file.close();
}



QStringList LanguageEngine::keysToNames(const QStringList &keys, const bool native) {
    QStringList names;

    foreach (QString key, keys) {
        if(native)
            names << mLangList[key].nativeName();
        else
            names << mLangList[key].name();
    }
    return names;
}


