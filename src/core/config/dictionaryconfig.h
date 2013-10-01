#pragma once

#include "api.h"
#include "loader.h"
#include <QWidget>
#include <QList>

class QTableWidget;
class QTabWidget;
class QCheckBox;
class QSpinBox;
class QLabel;


#define QP_DEFAULT_RESULT_COUNT 15

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
    QString name() const{return "";}
    QIcon icon() const{return QIcon("");}

    QPDictionaryList dictionaries() {
        return mConvertedDicts;
    }
private:
    QPModuleList mDictionaries;
    QPDictionaryList mConvertedDicts;
    QTableWidget *mTable;
    QTabWidget *mTabWidget;
    QSpinBox *mResultCountSpin;
    QLabel *mResultCountLabel;
};
