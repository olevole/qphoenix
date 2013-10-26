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
#include <QLabel>
#include <QWebView>
#include <QStringList>
#include <QLineEdit>
#include <QTimer>
#include "idictionarywidget.h"
#include "idictionary.h"
#include "threads.h"
#include "dictionaryconfig.h"

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

class DictionaryTemplate;

typedef QPair<QString, QString> LanguagePair;
typedef QList<LanguagePair> LanguagePairList;


class DictionaryWidget : public QWidget, public IDictionaryWidget
{
    Q_OBJECT
public:
    explicit DictionaryWidget(QWidget *parent = 0);

    //!! API METHODS!!
    virtual QString getSourceLanguageCode() const;
    virtual QString getResultLanguageCode() const;

    virtual QString getSourceText() const;
    virtual QString getResultText() const;

    virtual void clearSourceText();
    virtual void clearResultText();
    //!! END API METHODS!!

    QToolBar    *getToolBar() {return mMainToolBar;}
public slots:
    //!! API METHODS!!
    virtual void undo();
    virtual void redo();
    //!! END API METHODS!!

    void setNativeNames(bool b);
    void setDictionaryList(QPDictionaryList dicts);
    void setMaxItems(unsigned int count);
private slots:
    void showData(const QStringList &lst, const QString &name);
    void showCompletions(const QStringList &comp);

    void zoomIn();
    void zoomOut();
    void setLanguagePairs(const LanguagePairList &lst);

    void requestCompletions();
    void requestData(const QString &word);
    void requestData();
    void finish();
signals:
    //!!API METHODS!!
    void started();
    void finished();
    //!! END API METHODS!!
private:
    enum State {Idle = 0, WaitingCompletions, WaitingResponse};

    State mState;

    int mMaxItemCount;
    bool mNativeNames;
    bool mIsEmpty;

    QTimer mTimer;

    QToolBar *mMainToolBar;
    QComboBox *mLanguagesComboBox;

    QCompleter *mCompleter;
    QLineEdit *mSrcText;

    QWebView *mResText;
    QGroupBox   *mGroupbox;

    QPDictionaryList mDicts;
    QPDictionaryThread mThread;
    LanguagePairList mPairs;
    DictionaryTemplate *mTemplate;
};

