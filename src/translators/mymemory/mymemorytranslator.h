#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "../../include/translatorinterface.h"
#include "../../include/info.h"
#include <QObject>

class MyMemoryTranslator : public QObject, TranslatorInterface
{
    Q_OBJECT
    Q_INTERFACES(TranslatorInterface)
public:
    MyMemoryTranslator(QObject *parent = 0);

    bool load() {}
    bool unload() {}
    bool isLoaded() const {}
    QString errorString() const {}

    QWidget *configWidget() {}

    bool isLinear() const{}
    LanguageTable table() const {}

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {}
};

#endif // MYMEMORYTRANSLATOR_H
