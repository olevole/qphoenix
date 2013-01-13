#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "../../include/translatorinterface.h"
#include "../../include/info.h"
#include <QObject>

class MyMemoryTranslator : public QObject, TranslatorInterface
{
    Q_OBJECT
    Q_INTERFACES(TranslatorInterface)
//    Q_INTERFACES(Info)
public:
    MyMemoryTranslator(QObject *parent = 0);

    bool load() {}
    bool unload() {}
    QString errorString() const {}

    QWidget *configWidget() {}

    bool isLinear() const{}
    LangTable *table() const {}

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {}
};

#endif // MYMEMORYTRANSLATOR_H
