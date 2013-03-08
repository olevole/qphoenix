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

#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include <QWidget>

#include <QStringList>
#include <QListWidget>
#include "info.h"
#include "idictionarywidget.h"
#include "idictionary.h"
#include "querywrappers.h"

#include <QLabel>
#include <QWebView>


class QComboBox;
class QLineEdit;
class QTextBrowser;
class QToolButton;
class QGroupBox;
class QLabel;
class QCompleter;
class QHBoxLayout;
class QVBoxLayout;
class QStringListModel;
class QTimer;
class QWebView;
class QToolBar;



class DictionaryWidget : public QWidget, IDictionaryWidget, Info
{
    Q_OBJECT
    Q_INTERFACES(IDictionaryWidget Info)
public:
    explicit DictionaryWidget(QWidget *parent = 0);

    virtual QComboBox   *languagesComboBox() {return mLanguagesComboBox;   }
    virtual QLineEdit   *srcText()      {return mSrcText;       }
    virtual QWebView    *resText()      {return mResText;       }
    virtual QToolBar    *mainToolBar()  { return mMainToolBar;       }
public slots:
    void setNativeNames(const bool b) { mNativeNames = b;}

    void setCompletions(const QStringList &comp);
    void displayData(const DictionaryVariantList &lst);


    void setDictionaryList(QList<IDictionary *>dicts);
    void setMaxVariants(const int count){mMaxVarCount = count;}
private slots:
    void zoomIn();
    void zoomOut();

    void setLangPairs(const LanguagePairList lst);

    void onQuery();
private:
    /*!
     * Maximal count of displaying variants per dictionary
     * if 0 - unlimited
     */
    int mMaxVarCount;

    bool mNativeNames;
    QToolBar *mMainToolBar;
    QTimer *mQueryTimer;
    QComboBox *mLanguagesComboBox;
    QLineEdit *mSrcText;
    QWebView *mResText;
    QGroupBox   *mGroupbox;


    /*!
     *  A completer and model for input lineedit
     */
    QCompleter *mCompleter;
    QStringListModel *mCompleterModel;

    QHBoxLayout *mLineLayout;
    QVBoxLayout *mMainLayout;    

    /*!
     * Strings contains html templates
     * NOTE: Subject to changes
     */
    QString mBase, mFragment;

    QList<IDictionary *>mDicts;


    DictionaryWorker mDictWorker;
    LanguagePairList mPairs;
};

#endif // DICTIONARYWIDGET_H
