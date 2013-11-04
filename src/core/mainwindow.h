/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include "imainwindow.h"
#include "idictionarywidget.h"
#include "dictionarywidget.h"
#include "translationwidget.h"

#define QP_MAINWINDOW_CONFIG_GROUP "MainWindow"

class QStatusBar;
class QToolBar;
class QMenuBar;
class QMenu;
class QAction;
class QClipboard;
class QTabWidget;
class QTimer;
class QCloseEvent;
class QSettings;

class Config;
class PluginsConfig;
class QPTranslatorsConfig;
class LanguageConfig;
class DictionaryConfig;
class CommonConfig;


class MainWindow : public  QMainWindow, public IMainWindow
{
    Q_OBJECT
    Q_INTERFACES(IMainWindow)
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMainWindow *instance() {return this;}

    //Begin API methods
    virtual QString getStatusBarMessage() const;
    virtual void addStatusBarWidget(QWidget *widget);
    virtual void addToolBarAction(QAction *action);
    //End API methods
public slots:
    //Begin API methods
    virtual void setCurrentIndex(int i);
    virtual void setStatusBarMessage(const QString &msg, int timeout = 0);
    //End API methods
private slots:

    //! Update plugins, etc information from config dialog.
    void onConfigAccept();
    void updateTranslatorConfig();

    //! Handle table index change
    void onIndexChange(const int i);

    void readCfg();
    void saveCfg();

    // Menu actions slots
    void open();
    void save();
    void saveAs();
    void print();

    void exit();

    void clear();
//    void copy();
    void undo();
    void redo();
//    void swap();
    void about();
private:
    QSettings *mSettings;
    QString mSavePath;

    QStatusBar  *mStatusBar;
    QToolBar    *mToolBar;
    QMenuBar    *mMenuBar;
    QTabWidget *mTabWidget;

    QMenu   *mFileMenu, *mEditMenu, *mToolsMenu, *mHelpMenu;

    // File menu
    QAction
    *mActionExit,
    *mActionOpen,
    *mActionSave,
    *mActionSaveAs,
    *mActionPrint;

    // Edit Menu
    QAction
    *mActionClear,
    *mActionUndo,
    *mActionRedo,
    *mActionSwap,
    *mActionOptions;

    // Help menu
    QAction *mActionAbout, *mActionAboutQt;

    // Main widgets
    QPTranslationWidget *mTranslationWidget;
    DictionaryWidget *mDictionaryWidget;

    /*!
     * Main config dialog and these pages
     */
    Config *mSettingsDialog;
    PluginsConfig *mPluginsConfig;
    QPTranslatorsConfig *mTranslatorsConfig;
    LanguageConfig *mLanguageConfig;
    DictionaryConfig *mDictionaryConfig;\
    CommonConfig *mCommonConfig;

    static QString mAboutStr;
signals:
    void currentIndexChanged(const int i);
};
