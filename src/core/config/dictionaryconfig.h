#pragma once

#include "api.h"
#include "loader.h"
#include <QWidget>

class QTableWidget;
class QTabWidget;
class QCheckBox;
class QSpinBox;
class QLabel;


#define QP_DEFAULT_RESULT_COUNT 15

class DictionaryConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    DictionaryConfig(QWidget *parent = 0);

    void save();
    void read();
    void reset();

    DictionaryList dictionaries() {
        return mConvertedDicts;
    }
private:
    Loader mLoader;
    QObjectList mDictionaries;
    QList<IDictionary *>mConvertedDicts;
    QTableWidget *mTable;
    QTabWidget *mTabWidget;
//    QCheckBox *mRememberPair;
    QSpinBox *mResultCountSpin;
    QLabel *mResultCountLabel;
};
