#include "mymemorytranslator.h"
#include <QtGui>



#include <QtGlobal>
MyMemoryTranslator::MyMemoryTranslator(QObject *parent)
    :QObject(parent)
{
    setName("MyMemory");
    setUrl("http://mymemory.translated.net");

}


Q_EXPORT_PLUGIN2(mymemory, MyMemoryTranslator);

