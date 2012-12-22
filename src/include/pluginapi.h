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









// Inherited by DictionaryWidget


//Inherited by Settings










} // end Api namespace




//Q_DECLARE_INTERFACE(Api::MainWindowTabInterface, "com.qphoenix.interfaces.mainwindowtab/1.0")

\

#endif // PLUGINAPI_H
