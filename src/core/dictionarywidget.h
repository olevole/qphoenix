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

class DictionaryQueryLine : public QLineEdit {
    Q_OBJECT
public:
    DictionaryQueryLine(QPDictionaryThread *thread, QWidget *parent = 0);

    void setInputTimeout(int msec);
private:
    QTimer *mQueryTimer;
    QCompleter *mCompleter;
    QStringListModel *mModel;
    QPDictionaryThread *mThread;
signals:
    void inputFinished(const QString &);
    void selected(const QString &);
};

class DictionaryWidget : public QWidget, public IDictionaryWidget
{
    Q_OBJECT
public:
    explicit DictionaryWidget(QWidget *parent = 0);


    virtual QString getSourceText() const;
    virtual QString getResultText() const;

    virtual void clearSourceText();
    virtual void clearResultText();

    QToolBar    *getToolBar() {return mMainToolBar;}
public slots:
    virtual void undo();
    virtual void redo();

    void setNativeNames(bool b);
    void setDictionaryList(QPDictionaryList dicts);
    void setMaxItems(unsigned int count);
private slots:
    void displayData(const QStringList &lst, const QString &name);

    void zoomIn();
    void zoomOut();
    void setLanguagePairs(const LanguagePairList &lst);
    void onQueryComp();
    void onQueryWord();
    void onFinish();
signals:
    void started();
    void finished();
private:
    int mMaxItemCount;
    bool mNativeNames;
    bool mLock;
    bool mIsEmpty;

    QToolBar *mMainToolBar;
    QComboBox *mLanguagesComboBox;
    DictionaryQueryLine *mSrcText;
    QWebView *mResText;
    QGroupBox   *mGroupbox;


    QPDictionaryList mDicts;
    QPDictionaryThread mDictThread;
    LanguagePairList mPairs;
    DictionaryTemplate *mTemplate;
};

