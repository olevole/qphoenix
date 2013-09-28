#include "languages.h"
#include <QFile>
#include <QTextStream>

LanguageDB::LanguageDB()
{
    QFile file(":/files/langmap.csv");
    if(!file.open(QFile::ReadOnly))
        qFatal("Unable to open global language database! ");
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString str = in.readLine();
        QStringList result = str.split(",");

        Language lang(result.at(1), result.last());
        mLangList[result.first()] = lang;
    }
    file.close();
}
