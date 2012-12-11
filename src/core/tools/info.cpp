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

#include "info.h"


using namespace Tools;

Info::Info(QObject *parent) :
    QObject(parent),
    mIcon(new QIcon())
{
}


Info::Info(QObject *parent,
           const QString &name,
           const QString &ver,
           const QString &url,
           const QString &desc)
    :QObject(parent)

{


    setName(name);
    setVersion(ver);
    setUrl(url);
    setDescription(desc);
}


 Info & Info::operator=(const Info &i)  {
    setName(i.name());
    setVersion(i.version());
    setUrl(i.url());
    setDescription(i.description());

    return *this;
}
