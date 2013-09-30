#pragma once

#include <QWidget>
#include "iconfigpage.h"
#include <QList>
#include "languages.h"

class QTableWidget;
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
    QString name() const{return "";}
    QIcon icon() const{return QIcon("");}
    /*!
     * \brief keysForEnabled
     * \return  list with keys of enabled languages
     */
    QStringList keysForEnabled() const;

    /*!
     * \brief setNativeNames
     * \param b enable native names if true, disable otherwise
     */
    void setNativeNames(const bool b) {
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

