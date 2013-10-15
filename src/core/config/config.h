#pragma once
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

#include "iconfig.h"
#include "iconfigpage.h"
#include <QDialogButtonBox>
#include <QDialog>

class QListWidget;
class QStackedLayout;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QTreeWidgetItem;
class QPushButton;

#define QP_CONFIG_DIALOG_DEFAULT_WIDTH 800
#define QP_CONFIG_DIALOG_DEFAULT_HEIGH 600

class Config : public QDialog, public IConfig
{
    Q_OBJECT
    Q_INTERFACES(IConfig)
    Q_DISABLE_COPY(Config)
public:
    explicit Config(QWidget *parent = 0);
    ~Config();

    void addPage(QWidget *page, const QString &name, const QIcon &icon = QIcon());
    void removePage(QWidget *page);
    QWidget *pageAt(int i);
private:
    QList<IConfigPage *> mPagesList;

    QVBoxLayout *mMainLayout;
    QHBoxLayout *mHorizontalLayout;
    QHBoxLayout *mBottomLayout;
    QStackedLayout *mStackedLayout;
    QListWidget *mListWidget;
    QDialogButtonBox *mButtons;
    QPushButton *mDefaultsButton;
private slots:
    void onWidgetRemove(int idx);
    void save();
    void read();
    void reset();
};
