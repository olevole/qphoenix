#pragma once

#include "api.h"
#include "loader.h"
#include <QWidget>
#include <QList>

#define QP_DEFAULT_RESULT_COUNT 15

class QTableWidget;
class QTabWidget;
class QCheckBox;
class QSpinBox;
class QLabel;

struct QPDictionary {
    IDictionary *instance;
    QPModuleData data;
};

typedef QList<QPDictionary> QPDictionaryList;

class DictionaryConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    DictionaryConfig(QWidget *parent = 0);

    void save();
    void read();
    void reset();

    QPDictionaryList dictionaries();
private:
    QPModuleList mDictionaries;
    QPDictionaryList mConvertedDicts;
    QTableWidget *mTable;
    QTabWidget *mTabWidget;
    QSpinBox *mResultCountSpin;
    QLabel *mResultCountLabel;
};
