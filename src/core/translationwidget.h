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

#ifndef TRANSLATIONWIDGET_H
#define TRANSLATIONWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QSettings>
#include "itranslatorwidget.h"
#include "info.h"
#include "itranslator.h"
#include "languages.h"
#include "querywrappers.h"

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





class TranslationWidget : public QWidget, ITranslatorWidget, Info
{
    Q_OBJECT
    Q_INTERFACES(ITranslatorWidget Info)
//    Q_INTERFACES(Info)
public:
    explicit TranslationWidget(QWidget *parent = 0);
    virtual ~TranslationWidget();

    virtual QComboBox   *srcComboBox()      { return mSrcComboBox;      }
    virtual QComboBox   *resComboBox()      { return mResComboBox;      }
    virtual QTextEdit   *srcText()          { return mSrcText;          }
    virtual QTextBrowser*resText()          { return mResText;          }
    virtual QPushButton *translateButton()  { return mTranslateButton;  }
    virtual QToolButton *swapButton()       { return mSwapButton;       }
    virtual QToolBar    *srcToolbar()       { return mSrcToolbar;       }
    virtual QToolBar    *resToolbar()       { return mResToolbar;       }
    virtual QToolBar    *mainToolBar()      { return mMainToolBar;       }

    QComboBox *translatorComboBox() { return mTranslatorComboBox;}

    void setNativeNames(const bool b)           {mNativeNames = b;}
    void setTranslator(ITranslator *t) {
        if(t != NULL && t != mWorker.translator()) {
            mWorker.setTranslator(t);
            updateLanguages();
            readCfg();
        } else {
            qDebug() << "THIS TRANSLATIR IS ALREADY SET: " << t->name();
        }
    }

    void setEnabledKeys(const QStringList &keys){mKeys = keys;}
public slots:
    virtual void swap();
    virtual void copySrcText();
    virtual void copyResText();
private slots:
    void onSourceLanguageChanged();
    void updateButtonState();

    void fillCombobox(QComboBox *cb, QStringList keys);
    void translate();

    // Update languages if translator was changed TODO: finish it!
    void updateLanguages();


    void saveCfg();
    void readCfg();
private:
    QString srcComboboxData();
    QString resComboboxData();

    /*!
     *  Widgets
     */
    QToolBar *mMainToolBar;

    QComboBox
    *mSrcComboBox,
    *mResComboBox,
    *mTranslatorComboBox;

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
};

#endif // TRANSLATIONWIDGET_H
