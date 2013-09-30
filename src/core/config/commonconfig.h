#ifndef COMMONCONFIG_H
#define COMMONCONFIG_H

#include <QWidget>
#include "iconfigpage.h"

class QTabWidget;
class QCheckBox;
class QLabel;
class QComboBox;

class CommonConfig : public QWidget, public IConfigPage
{
    Q_OBJECT
    Q_INTERFACES(IConfigPage)
public:
    explicit CommonConfig(QWidget *parent = 0);

    virtual void save();
    virtual void read();
    virtual void reset();
    QString name() const{return "";}
    QIcon icon() const{return QIcon("");}

    bool useNativeNames();
private:
    QTabWidget *mTabWidget;
    QCheckBox *mUseNativeCheckbox;
    QComboBox *mLanguageCombobox;
    QLabel *mLanguageLabel;

};

#endif // COMMONCONFIG_H
