#ifndef PLUGINAPI_H
#define PLUGINAPI_H


/*
 * This is an API for QPhoenix plugins. This  interface class
 * MUST be inherited by MainWindow and all methods should be
 * re-implemented and actualised.
 */

#include <QString>

namespace Api {

class PluginAPI  {

public:
    QString srcLang() const;
    QString resbpiLang() const;
    QString srcText() const;
    QString resText() const;
signals:
    // Signals for plugins
    void translationInitiated(const QString &src_text);
    void translationFinished(const QString &src_text, const QString &res_text);

    void sourceLanguageChanged();
    void resultLanguageChanged();
    void languagesSwapped();
};




}


#endif // PLUGINAPI_H
