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

#include <QWidget>
#include <QToolBar>
#include <QSettings>
#include <QComboBox>
#include "itranslationwidget.h"
#include "itranslator.h"
#include "languages.h"
#include "threads.h"
#include "translatorsconfig.h"
#include "loader.h"

class QTextEdit;
class QTextBrowser;
class QToolButton;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QToolBar;

class QPTranslationToolBar : public QToolBar {
Q_OBJECT
public:
    explicit QPTranslationToolBar(QWidget *parent = 0);
public slots:
    void setCopyActionEnabled(bool);
signals:
    void copyRequest();
private:
    QAction *mCopyAction;
};

class QPLanguageComboBox : public QComboBox {
public:
    explicit QPLanguageComboBox(QWidget *parent = 0);
    QString currentData() const;
};

class QPTranslationWidget : public QWidget, public ITranslationWidget
{
    Q_OBJECT
public:
    explicit QPTranslationWidget(QWidget *parent = 0);
    virtual ~QPTranslationWidget();


    //begin of API methods
    virtual QString getSourceText() const;
    virtual QString getResultText() const;
    virtual void setSourceText(const QString &text);
    virtual void setResultText(const QString &text);
    virtual void clearSourceText();
    virtual void clearResultText();
    virtual QString getSourceLanguageCode();
    virtual QString getResultLanguageCode();
    virtual QObject *qobject();
    virtual void addToolbarAction(QAction *action, TranslationWidgetToolbar toolbar);
    //end of API methods

    QToolBar    *mainToolBar() {return mMainToolBar;}

    // Config section
    void setNativeNames(const bool b) {mNativeNames = b;}
    void setTranslatorsNames(const QStringList &lst);
    void setTranslator(QPTranslator &translator);
    void setEnabledLanguages(const QStringList &lst) {mEnabledLanguages = lst;}
private:
    void setIndexByKey(QComboBox *combobox, const QString &key);
public slots:
    //begin of API methods
    virtual void swap();
    virtual void undo();
    virtual void redo();
    virtual void translate();
    virtual void copySourceText();
    virtual void copyResultText();
    //end of API methods
    void setTranslatorIndex(int idx);
private slots:
    void updateComboxes();
    void updateResultComboBox();
    void saveCfg();
    void readCfg();
private:
    QComboBox *mTranslatorsComboBox;
    QToolBar *mMainToolBar;
    QPTranslationToolBar *mSrcToolbar, *mResToolbar;
    QPLanguageComboBox *mSrcComboBox;
    QPLanguageComboBox *mResComboBox;
    QTextEdit *mSrcText;
    QTextBrowser *mResText;
    QPushButton *mTranslateButton;
    QToolButton *mSwapButton;
    QVBoxLayout *mMainLayout;
    QHBoxLayout *mButtonsLayout;

    QPTranslatorThread mThread;
    QStringList mEnabledLanguages;
    LanguageTable mTable;
    ITranslator *mTranslator;
    bool mNativeNames;
    bool mLanguageTableIsFlat;
signals:
   //begin of API methods
    void finished();
    void started();
    //end of API methods

    void translatorIndexChanged(int);
};
