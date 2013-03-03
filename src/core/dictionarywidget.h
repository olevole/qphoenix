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
private slots:
    void zoomIn();
    void zoomOut();
signals:
    void queryChanged();
private:
    bool mNativeNames;

    QToolBar *mMainToolBar;

    QTimer *mQueryTimer;
    QComboBox *mLanguagesComboBox;
    QLineEdit *mSrcText;
    QWebView *mResText;
    QGroupBox   *mGroupbox;

    QCompleter *mCompleter;
    QStringListModel *mCompleterModel;

    QHBoxLayout *mLineLayout;
    QVBoxLayout *mMainLayout;    

    QString mBase, mFragment;
};

#endif // DICTIONARYWIDGET_H
