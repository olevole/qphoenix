#include "mymemorytranslator.h"
#include <QtGui>

#include <QtGlobal>
MyMemoryTranslator::MyMemoryTranslator(QObject *parent)
    :QObject(parent)
{
    setName("Google translate");

}


Q_EXPORT_PLUGIN2(mymemory, MyMemoryTranslator);

