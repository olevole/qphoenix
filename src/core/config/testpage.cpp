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

#include "testpage.h"

#include <QLabel>
#include <QHBoxLayout>

TestPage::TestPage(QWidget *parent) :
    QWidget(parent)
{

    QLabel *lb = new QLabel("Test222", this);


    QHBoxLayout *l = new QHBoxLayout;

    l->addWidget(lb);

    setName(tr("Test Options"));
    setIcon(QIcon::fromTheme("application-exit"));
//    setN

    this->setLayout(l);
//    this.


//    information.setName("Blablabla");






}
