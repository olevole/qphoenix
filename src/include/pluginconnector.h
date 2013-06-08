#pragma once

class MainWindow;
class Config;
class TranslatorWidget;
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
        QP_MAIN_WINDOW = QP_CONFIG_DIALOG = QP_TRANSLATOR_WIDGET = QP_DICTIONARY_WIDGET = 0;
    }
    MainWindow *QP_MAIN_WINDOW;
    Config *QP_CONFIG_DIALOG;
    TranslatorWidget *QP_TRANSLATOR_WIDGET;
    DictionaryWidget *QP_DICTIONARY_WIDGET;
};

