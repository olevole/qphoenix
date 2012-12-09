#ifndef PLUGINAPI_H
#define PLUGINAPI_H



#include <QString>
#include <QMainWindow>
#include "settingsinterface.h"

class QToolBar;
class QStatusBar;
class QComboBox;
class QToolButton;
class QPushButton;
class QTextEdit;
class QTextBrowser;
class QMenuBar;

namespace Api {


/*!
 * This is an API for QPhoenix plugins. This  interface class
 * MUST be inherited by MainWindow and all methods should be
 * re-implemented and actualised.
 */



/*!
 * \brief The MainWindowAPI class
 */

class MainWindowAPI {
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


    virtual QToolBar    *toolbar() = 0;
    virtual QStatusBar  *statusbar()  = 0;
    virtual QComboBox   *srcComboBox() = 0;
    virtual QComboBox   *resComboBox() = 0;
    virtual QTextEdit   *srcText() = 0;
    virtual QTextBrowser*resTExt() = 0;
    virtual QPushButton *translateButton() = 0;
    virtual QToolButton *swapButton() = 0;
    virtual QMenuBar    *menuBar() = 0;
};


class SettingsAPI {
public:
    virtual void addPage(const SettingsInterface *page);
    virtual void removePage(const SettingsInterface *page);

    virtual int count() const = 0;

};



} // end Api namespace


#endif // PLUGINAPI_H
