#pragma once

#include <QWidget>
#include <QList>
#include <QTableWidget>
#include "iconfigpage.h"
#include "languages.h"

class QPushButton;
class QCheckBox;

class LanguageConfig : public QWidget, IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    explicit LanguageConfig(QWidget *parent = 0);
    
    void save();
    void read();
    void reset();

    QStringList getEnabledLanguages() const;
    void setNativeNames(bool b);
private slots:
    void pickAll();
    void unpickAll();
private:
    bool mNativeNames;
    QList <QCheckBox *> mCheckBoxList;
    LanguageList mLangList;
    QTableWidget *mTableWidget;

    QPushButton *mSetButton, *mUnsetButton;
};

