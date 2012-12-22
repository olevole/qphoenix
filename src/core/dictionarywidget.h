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
#include "pluginapi.h"
#include "abstractinfocontainer.h"

//using namespace Tools;

class QComboBox;
class QLineEdit;
class QTextBrowser;
class QToolButton;
class QGroupBox;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;


class DictionaryWidget : public QWidget, Api::DictionaryWidgetAPI, AbstractInfoContainer
{
    Q_OBJECT
    Q_INTERFACES(Api::DictionaryWidgetAPI)
    Q_INTERFACES(AbstractInfoContainer)
public:
    explicit DictionaryWidget(QWidget *parent = 0);

    virtual QComboBox   *languagesComboBox() {return mLanguagesComboBox;   }
    virtual QLineEdit   *srcText()      {return mSrcText;       }
    virtual QTextBrowser*resText()      {return mResText;       }


private:
    QComboBox *mLanguagesComboBox;
    QLineEdit *mSrcText;
    QTextBrowser *mResText;
    QGroupBox   *mGroupbox;
    QLabel      *mQueryLabel;

    QHBoxLayout *mLineLayout;
    QVBoxLayout *mMainLayout;
    
};

#endif // DICTIONARYWIDGET_H
