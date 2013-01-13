#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "../../include/translatorinterface.h"
#include "../../include/info.h"

class MyMemoryTranslator : public TranslatorInterface
{
    Q_INTERFACES(TranslatorInterface)
    Q_INTERFACES(Info)
public:
    MyMemoryTranslator();
};

#endif // MYMEMORYTRANSLATOR_H
