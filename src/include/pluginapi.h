#ifndef PLUGINAPI_H
#define PLUGINAPI_H



#include <QString>
#include <QMainWindow>
#include "settingsinterface.h"



namespace Api {

class QToolBar;
class QStatusBar;
class QComboBox;
class QToolButton;
class QPushButton;
class QTextEdit;
class QTextBrowser;
class QMenuBar;
class QLineEdit;

/*!
 * This is an API for QPhoenix plugins. This  interface class
 * MUST be inherited by MainWindow and all methods should be
 * re-implemented and actualised.
 */



/*!
 * \brief The MainWindowAPI class
 */



// Inherited by TranslatorWidget
class TranslatorWidgetAPI {
public:

    /*
     * Yes, I know, this is not a best solution,
     * but it the easiest way to take plugins full
     * controll on the widgets. Plugin developers
     * should be carefull using these objects
     * pointers. Do not forget, other plugins
     * can use those objects too, it could take
     * a race condition effect.
     */

    virtual ~TranslatorWidgetAPI() {}


    virtual QComboBox   *srcComboBox() = 0;
    virtual QComboBox   *resComboBox() = 0;
    virtual QTextEdit   *srcText() = 0;
    virtual QTextBrowser*resTExt() = 0;
    virtual QPushButton *translateButton() = 0;
    virtual QToolButton *swapButton() = 0;
};





// Inherited by DictionaryWidget
class DictionaryWidgetAPI {
public:
    virtual ~DictionaryWidgetAPI() {}

    virtual QComboBox   *srcComboBox() = 0;
    virtual QComboBox   *resComboBox() = 0;
    virtual QLineEdit   *srcText() = 0;
    virtual QTextBrowser*resTExt() = 0;
    virtual QToolButton *swapButton() = 0;
};

class SettingsWidgetAPI {
public:
    virtual ~SettingsWidgetAPI() {}

    virtual void addPage(const SettingsInterface *page) = 0;
    virtual void removePage(const SettingsInterface *page) = 0;
    virtual void pageAt(const int i) = 0;

//virtual int count() const = 0;

};





} // end Api namespace
Q_DECLARE_INTERFACE(Api::TranslatorWidgetAPI, "com.qphoenix.interfaces.translatorwidget/1.0")
Q_DECLARE_INTERFACE(Api::DictionaryWidgetAPI, "com.qphoenix.interfaces.dictionarywidget/1.0")
Q_DECLARE_INTERFACE(Api::SettingsWidgetAPI, "com.qphoenix.interfaces.settingswidget/1.0")


#endif // PLUGINAPI_H
