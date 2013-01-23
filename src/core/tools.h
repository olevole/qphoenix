#ifndef TOOLS_H
#define TOOLS_H

#include <QStringList>
#include <QSet>
#include "languages.h"
#include "translatorinterface.h"

class Tools
{
public:
    Tools();
    static QStringList intersects(const QStringList &lst1, const QStringList &lst2) {
//        QSet <QString> set1, set2;

//        set1.fromList(lst1);
//        set2.fromList(lst2);

//        return set1.intersect(set2).toList();


        return lst1.toSet().intersect(lst2.toSet()).toList();
    }


    static QString nameToCode(const QString &name,const LanguageList &lst);


};




#endif // TOOLS_H
