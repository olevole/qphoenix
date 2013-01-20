#ifndef LANGUAGECONFIG_H
#define LANGUAGECONFIG_H

#include <QWidget>
#include "configpageinterface.h"
#include <QList>

class QTableWidget;
class QPushButton;
class QCheckBox;

class LanguageConfig : public QWidget, ConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(ConfigPageInterface)
public:
    explicit LanguageConfig(QWidget *parent = 0);
    
    void save(){}
    void read(){}
    void reset(){}
private:
    QList<QCheckBox *> mCheckboxList;
    QTableWidget *mTable;
    QPushButton *mSetButton, *mUnsetButton;
};

#endif // LANGUAGECONFIG_H
