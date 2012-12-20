#ifndef PLUGINAPI_H
#define PLUGINAPI_H



#include <QString>
#include <QMainWindow>
#include "settingsinterface.h"
#include "translatorinterface.h"
#include "plugininterface.h"

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
 * The following clases declare interface FOR access to MainWindow, TranslatorWidget,
 * DictionaryWidget, etc for plugins, plugins SHOULD NOT inherit this classes,
 * only for classes in application core.
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
    virtual QLineEdit   *srcText() = 0;
    virtual QTextBrowser*resText() = 0;
};


//Inherited by Settings
class SettingsAPI {
public:
    virtual ~SettingsAPI() {}

    virtual void addPage(QWidget *page) = 0;
    virtual void removePage(const QWidget *page) = 0;
    virtual QWidget *pageAt(const int i) = 0;
};



class MainWindowAPI {
public:
    // Signals
    virtual void tabChanged(const int i) = 0;

    //Slots
    virtual void setCurrentTab(const int i) = 0;

    // Methods
    virtual void addPage(QWidget *page) = 0;
    virtual void removePage(const QWidget *page) = 0;
    virtual QWidget *pageAt(const int i) = 0;




};



} // end Api namespace

Q_DECLARE_INTERFACE(Api::TranslatorWidgetAPI, "com.qphoenix.interfaces.translatorwidget/1.0")
Q_DECLARE_INTERFACE(Api::DictionaryWidgetAPI, "com.qphoenix.interfaces.dictionarywidget/1.0")
Q_DECLARE_INTERFACE(Api::SettingsAPI, "com.qphoenix.interfaces.settingswidget/1.0")
Q_DECLARE_INTERFACE(Api::MainWindowAPI, "com.qphoenix.interfaces.mainwindow/1.0")
//Q_DECLARE_INTERFACE(Api::MainWindowTabInterface, "com.qphoenix.interfaces.mainwindowtab/1.0")



#endif // PLUGINAPI_H
