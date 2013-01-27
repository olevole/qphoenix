#ifndef DICTIONARYCONFIG_H
#define DICTIONARYCONFIG_H

#include "api.h"
#include "loader.h"
#include <QWidget>

class QTableWidget;




class DictionaryConfig : public QWidget, ConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(ConfigPageInterface)
public:
    DictionaryConfig(QWidget *parent = 0);

    void save(){}
    void read(){}
    void reset(){}

    QObjectList dictionaries() {
        return mDictionaries;
    }

private:
    Loader mLoader;
    QObjectList mDictionaries;
    QTableWidget *mTable;
};

#endif // DICTIONARYCONFIG_H
