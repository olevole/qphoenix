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
#include <QLabel>
#include <QWebView>
#include <QStringList>
#include <QListWidget>
#include <QMutex>
#include <QQueue>

#include "info.h"
#include "idictionarywidget.h"
#include "idictionary.h"
#include "querywrappers.h"






class QComboBox;
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
class QLineEdit;


/*!
 * \brief The DictionaryTemplate class
 * This class is a wrapper for html templates for dictionary QWebView
 * display widget.
 */

class DictionaryTemplate : public QObject {
public:
//    void beginRoot(const QString &title, const bool collapseable);
//    void endDocument();


    /*!
     * \brief beginSection create a document section
     * \param title section title
     * \param collapseable
     */
    void beginSection(const QString &title, const bool collapseable);

    /*!
     * \brief beginSection create a document section with items
     * \param lst a list of items
     * \param title title of section
     * \param collapseable could that section be collapsed?
     */
    void beginSection(const DictionaryVariantList &lst, const QString &title, const bool collapseable);

    /*!
     * \brief endSection end of section
     */
    void endSection();


    /*!
     * \brief addItem add item for current section
     * \param var
     * \return true if beginSection was set correct
     * false - otherwise
     */
    bool addItem(const DictionaryVariant &var);


    QString document() const;
private:
    QString mRoot;
    static QString mTemplateRoot;
    static QString mTemplateSection;
    static QString mTemplateItem;
};

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
    void setDictionaryList(QList<IDictionary *>dicts);

    //TODO: Implement those two functions reactions
    void setMaxVariants(const int count){mMaxVarCount = count;}
    void setInputTimeout(const int t) {mQueryTimer->setInterval(t);}
private slots:
    void setCompletions(const QStringList &comp);
    void displayData(const DictionaryVariantList &lst, const QString &name);

    void zoomIn();
    void zoomOut();

    void setLangPairs(const LanguagePairList lst);
    void onQueryComp();
    void onQueryWord();
    void onFinish();
signals:
    void start();
    void finish();
private:

//    void query(const bool comp);
    /*!
     * Maximal count of displaying variants per dictionary
     * if 0 - unlimited
     */
    int mMaxVarCount;

    bool mNativeNames, mLock;
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


    const QString mTemplateRoot;
    const QString mTemplateSection;
    const QString mTemplateItem;

    QString mLastContent;

    QQueue <IDictionary *> mDictQueue;

    QList<IDictionary *>mDicts;
    DictionaryWorker mDictWorker;
    LanguagePairList mPairs;
};

#endif // DICTIONARYWIDGET_H
