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

        mLangList << Language(result.first(), result.at(1), result.last());
    }
    file.close();
}
