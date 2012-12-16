#ifndef PLUGINAPI_H
#define PLUGINAPI_H



#include <QString>
#include <QMainWindow>
#include "settingsinterface.h"
#include "translatorinterface.h"

class QToolBar;
class QStatusBar;
class QComboBox;
class QToolButton;
class QPushButton;
class QTextEdit;
class QTextBrowser;
class QMenuBar;
class QLineEdit;

namespace Api {



/*! \brief The MainWindowAPI class
 *
 * This is a MainWindow API for QPhoenix plugins. This  interface class
 * MUST be inherited by MainWindow and all methods should be
 * re-implemented and actualised.
 */





/*!
 * Yes, I know, this is not a best solution,
 * but it the easiest way to take plugins full
 * controll on the widgets. Plugin developers
 * should be carefull using these objects
 * pointers. Do not forget, other plugins
 * can use those objects too, it could take
 * a race condition effect.
 */

// Inherited by TranslatorWidget
class TranslatorWidgetAPI {
public:



    virtual ~TranslatorWidgetAPI() {}


    virtual QComboBox   *srcComboBox() = 0;
    virtual QComboBox   *resComboBox() = 0;
    virtual QTextEdit   *srcText() = 0;
    virtual QTextBrowser*resText() = 0;
    virtual QPushButton *translateButton() = 0;
    virtual QToolButton *swapButton() = 0;
};





// Inherited by DictionaryWidget
class DictionaryWidgetAPI {
public:
    virtual ~DictionaryWidgetAPI() {}

    virtual QComboBox   *languagesComboBox() = 0;
//    virtual QComboBox   *resComboBox() = 0;
    virtual QLineEdit   *srcText() = 0;
    virtual QTextBrowser*resText() = 0;
//    virtual QToolButton *swapButton() = 0;
};

class SettingsWidgetAPI {
public:
    virtual ~SettingsWidgetAPI() {}

    virtual void addPage(QObject *page) = 0;
    virtual void removePage(const QObject *page) = 0;
    virtual SettingsInterface *pageAt(const int i) = 0;
};




class MainWindowTabInterface {
public:
    virtual Info *info() = 0;
    void setValue(const QString &str) {mStr = str;}
    QString value() const { return mStr;}

private:
    QString mStr;
};

class MainWindowAPI {
public:
    // Signals

    virtual void tabChanged(const int i) = 0;
    virtual void setCurrentTab(const int i) = 0;

    // Methods
    virtual void addPage(QWidget *page) = 0;
    virtual void removePage(const QWidget *page) = 0;
    virtual MainWindowTabInterface *pageAt(const int i) = 0;


};



} // end Api namespace

Q_DECLARE_INTERFACE(Api::TranslatorWidgetAPI, "com.qphoenix.interfaces.translatorwidget/1.0")
Q_DECLARE_INTERFACE(Api::DictionaryWidgetAPI, "com.qphoenix.interfaces.dictionarywidget/1.0")
Q_DECLARE_INTERFACE(Api::SettingsWidgetAPI, "com.qphoenix.interfaces.settingswidget/1.0")
Q_DECLARE_INTERFACE(Api::MainWindowAPI, "com.qphoenix.interfaces.mainwindow/1.0")
Q_DECLARE_INTERFACE(Api::MainWindowTabInterface, "com.qphoenix.interfaces.mainwindowtab/1.0")



#endif // PLUGINAPI_H
