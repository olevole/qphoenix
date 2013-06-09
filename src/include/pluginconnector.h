#pragma once

class IMainWindow;
class Config;
class TranslationWidget;
class DictionaryWidget;


/*!
 * \brief The PluginConnector struct
 * Structure with public pointers to plugin interfaces
 * QP_MAIN_WINDOW - Main Window interface
 * QP_CONFIG_DIALOG - Config dialog iface
 * QP_TRANSLATOR_WIDGET - Translator widget iface
 * QP_DICTIONARY_WIDGET - Dictionary widget iface
 */
struct PluginConnector
{
    PluginConnector() {
        QP_MAIN_WINDOW = NULL;
        QP_CONFIG_DIALOG = NULL;
        QP_TRANSLATOR_WIDGET = NULL;
        QP_DICTIONARY_WIDGET = NULL;
    }
    IMainWindow *QP_MAIN_WINDOW;
    Config *QP_CONFIG_DIALOG;
    TranslationWidget *QP_TRANSLATOR_WIDGET;
    DictionaryWidget *QP_DICTIONARY_WIDGET;
};

