#ifndef LANGUAGECONFIG_H
#define LANGUAGECONFIG_H

#include <QWidget>
#include "configpageinterface.h"
#include <QList>
#include "languages.h"

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

    QStringList keysForEnabled() const;

    void setUseNativeNames(const bool b) {
        mNativeNames = b;
    }
private slots:
    void setAll();
    void unsetAll();
private:
    void createTable();

    void setCbState(const bool state);


    LanguageList mLangList;

    QList<QCheckBox *> mCheckboxList;
    QTableWidget *mTable;
    QPushButton *mSetButton, *mUnsetButton;

    bool mNativeNames;
};

#endif // LANGUAGECONFIG_H
