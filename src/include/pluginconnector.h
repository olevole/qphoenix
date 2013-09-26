#pragma once

class IMainWindow;
class IConfig;
class ITranslationWidget;
class IDictionaryWidget;

/*!
 * \brief The PluginConnector struct
 * Structure with public pointers to plugin interfaces
 * mainwindow - Main Window interface
 * configdialog - Config dialog iface
 * translationwidget - Translator widget iface
 * dictionarywidget - Dictionary widget iface
 */

struct PluginConnector
{
    PluginConnector() {
        mainwindow = NULL;
        configdialog = NULL;
        translationwidget = NULL;
        dictionarywidget = NULL;
    }
    IMainWindow *mainwindow;
    IConfig *configdialog;
    ITranslationWidget *translationwidget;
    IDictionaryWidget *dictionarywidget;
};

