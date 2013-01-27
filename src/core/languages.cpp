
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
