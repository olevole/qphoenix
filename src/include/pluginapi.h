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


namespace Api {


/*!
 * This is an API for QPhoenix plugins. This  interface class
 * MUST be inherited by MainWindow and all methods should be
 * re-implemented and actualised.
 */


class MainWindowAPI {
public:
    /*!
     * Yes, I know, this is not a best solution,
     * but it the easiest way to take plugins full
     * controll on the widgets. Plugin developers
     * should be carefull using this object
     * pointers. Do not forget, other plugins
     * can use those objects too, it could take
     * a race condition effect.
     */

    virtual QString srcLang() const = 0;
    virtual QString resLang() const = 0;

    virtual QString srcText() const = 0;
    virtual QString resText() const = 0;

    virtual QToolBar    *toolbar() = 0;
    virtual QStatusBar  *statusbar()  = 0;
    virtual QComboBox   *srcComboBox() = 0;
    virtual QComboBox   *resComboBox() = 0;


//signals:
//    virtual void translationInitiated(const QString &src_text) = 0 ;
//    virtual void translationFinished(const QString &src_text, const QString &res_text) = 0;



    virtual void sourceLanguageChanged() = 0;
    virtual void resultLanguageChanged() = 0;
    virtual void languagesSwapped() = 0;

//slots:
//    virtual void setSourceLanguage(const int i) = 0;
};


class SettingsAPI {
public:
    virtual void addPage(const SettingsInterface *iface);


};



} // end Api namespace


#endif // PLUGINAPI_H
