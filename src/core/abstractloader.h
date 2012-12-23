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

#ifndef ABSTRACTLOADER_H
#define ABSTRACTLOADER_H

class QStringList;

class AbstractLoader {
public:
    virtual ~AbstractLoader(){}

    virtual bool load(const int i)=0;
    virtual bool load(const QString &name)=0;

    virtual void addSearchPath(const QString &str)=0;
    virtual void addSearchPaths(const QStringList &lst)=0;

    // List of available for load instances.
    virtual QStringList list() const=0;
};

#endif // ABSTRACTLOADER_H
