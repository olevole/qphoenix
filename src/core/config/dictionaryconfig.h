#ifndef DICTIONARYCONFIG_H
#define DICTIONARYCONFIG_H

#include "api.h"
#include "loader.h"
#include <QWidget>

class QTableWidget;
class QTabWidget;
class QCheckBox;
class QSpinBox;


class DictionaryConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    DictionaryConfig(QWidget *parent = 0);

    void save(){}
    void read(){}
    void reset(){}

    QList<IDictionary *> dictionaries() {
        return mConvertedDicts;
    }
private:
    Loader mLoader;
    QObjectList mDictionaries;
    QList<IDictionary *>mConvertedDicts;
    QTableWidget *mTable;
    QTabWidget *mTabWidget;

    QCheckBox *mRememberPair;
};

#endif // DICTIONARYCONFIG_H
