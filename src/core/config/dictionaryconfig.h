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

    QObjectList dictionaries() {
        return mDictionaries;
    }
private:
    Loader mLoader;
    QObjectList mDictionaries;
    QTableWidget *mTable;
    QTabWidget *mTabWidget;

    QCheckBox *mRememberPair;
//    QSpinBox *mMaxResults;
};

#endif // DICTIONARYCONFIG_H
