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

#ifndef Info_H
#define Info_H

#include <QString>
#include <QIcon>

class Info
{
public:
//    virtual ~Info(){}

    QString name() const                    {return mName;      }
    QString version() const                 {return mVersion;   }
    QString url() const                     {return mUrl;       }
    QString description() const             {return mDecription;}
    QIcon   icon() const                    {return mIcon;      }
protected:
    void setName(const QString &n)          {mName = n;         }

    void setVersion(const QString &v)       {mVersion = v;      }
    void setUrl(const QString &u)           {mUrl = u;          }
    void setDescription(const QString &t)   {mDecription = t;   }
    void setIcon( const QIcon &icon)        {mIcon = icon;      }

    QString mName, mVersion, mUrl, mDecription;
    QIcon mIcon;
};



Q_DECLARE_INTERFACE(Info, "com.qphoenix.interfaces.info/1.0");


#endif // Info_H
