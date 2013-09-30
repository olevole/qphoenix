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
#include "itranslationwidget.h"
#include "itranslator.h"
#include "languages.h"
#include "querywrappers.h"
#include "translatorsconfig.h"

class QTextEdit;
class QTextBrowser;
class QToolButton;
class QPushButton;
class QComboBox;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QToolBar;

class TranslationToolBar : public QToolBar {
Q_OBJECT
public:
    explicit TranslationToolBar(QWidget *parent = 0);
public slots:
    void setCopyActionEnabled(bool);
signals:
    void copyRequest();
private:
    QAction *mCopyAction;
};


class TranslationWidget : public QWidget, public ITranslationWidget
{
    Q_OBJECT
public:
    explicit TranslationWidget(QWidget *parent = 0);
    virtual ~TranslationWidget();


    /*
     * begin of API methods
     */
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

    /*
     * end of API methods
     */

    QToolBar    *mainToolBar()      { return mMainToolBar;      }

    void setNativeNames(const bool b) {mNativeNames = b; updateLanguages();}
    void setTranslator(ITranslator *t);
    void setEnabledKeys(const QStringList &keys){mKeys = keys;}
    void setTranslatorsConfig(TranslatorsConfig *cfg);

public slots:
    /*
     * begin of API methods
     */
    virtual void swap();
    virtual void undo();
    virtual void redo();
    virtual void translate();

    virtual void copySrcText();
    virtual void copyResText();
    /*
     * end of API methods
     */
private slots:
    void onSourceLanguageChanged();
    void onResultLanguageChanged();
    void updateButtonState();
    void fillCombobox(QComboBox *cb, QStringList keys);

    /*!
     * \brief setIndexByKey sets combobox index by text (or 0 if not match)
     * \param cb combobox to set
     * \param key key to set
     */
    void setIndexByKey(QComboBox *cb, const QString &key);

    // Update languages if translator was changed TODO: finish it!
    void updateLanguages();

    void saveCfg();
    void readCfg();
private:
    QString srcComboboxData();
    QString resComboboxData();

    TranslatorsConfig *mTranslatorConfig;
    QComboBox *mEmbeddedComboBox;

    /*!
     *  Widgets
     */
    QToolBar *mMainToolBar;

    QComboBox
    *mSrcComboBox,
    *mResComboBox;
    QTextEdit *mSrcText;
    QTextBrowser *mResText;

    QPushButton *mTranslateButton;
    QToolButton *mSwapButton;

    QVBoxLayout *mMainLayout;
    QHBoxLayout *mButtonsLayout;

    TranslationToolBar *mSrcToolbar, *mResToolbar;

    /*!
     *  Logic parts
     */
    QStringList mKeys;
    LanguageTable mTable;
    TranslatorWorker mWorker;

    bool mIsLinear, mNativeNames;
    int mTranslatorIndex;


    QString mLastSrcName, mLastDestName;
signals:
    /*
     * begin of API methods
     */
    void finished();
    void started();
    /*
     * end of API methods
     */
};
