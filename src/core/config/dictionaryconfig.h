#ifndef DICTIONARYCONFIG_H
#define DICTIONARYCONFIG_H

#include "api.h"
#include "loader.h"
#include <QWidget>

class QTableWidget;



typedef QList<DictionaryInterface *>DictionaryInterfaceList;

class DictionaryConfig : public QWidget, ConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(ConfigPageInterface)
public:
    DictionaryConfig(QWidget *parent = 0);

    void save(){}
    void read(){}
    void reset(){}

    DictionaryInterfaceList dictionaries();
private:
    Loader mLoader;

    QObjectList mDictionaries;

    QTableWidget *mTable;
};

#endif // DICTIONARYCONFIG_H
