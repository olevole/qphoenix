#ifndef PLUGINAPI_H
#define PLUGINAPI_H


/*
 * This is an API for QPhoenix plugins. This  interface class
 * MUST be inherited by MainWindow and all methods should be
 * re-implemented and actualised.
 */

#include <QString>
#include "plugininterface.h"
#include "settingsinterface.h"

namespace Api {

class MainWindowAPI {
public:
    virtual QString srcLang() const = 0;
    virtual QString resbpiLang() const = 0;
    virtual QString srcText() const = 0;
    virtual QString resText() const = 0;
//signals:
//    // Signals for plugins
//    virtual void translationInitiated(const QString &src_text) = 0 ;
//    virtual void translationFinished(const QString &src_text, const QString &res_text) = 0;

//    virtual void sourceLanguageChanged() = 0;
//    virtual void resultLanguageChanged() = 0;
//    virtual void languagesSwapped() = 0;
};




class SettingsAPI {
public:


};




}


#endif // PLUGINAPI_H
