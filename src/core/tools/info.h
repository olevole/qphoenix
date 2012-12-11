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

#ifndef INFO_H
#define INFO_H

#include <QObject>
#include <QIcon>

//class QIcon;

namespace Tools {

class Info : public QObject
{
    Q_OBJECT
public:
    explicit Info(QObject *parent = 0);
    explicit Info(QObject *parent,
                  const QString &name,
                  const QString &v ,
                  const QString &url,
                  const QString &desc);

    void setName(const QString &n)          {mName = n;         }
    void setVersion(const QString &v)       {mVersion = v;      }
    void setUrl(const QString &u)           {mUrl = u;          }
    void setDescription(const QString &t)   {mDecription = t;   }
    void setIcon(QIcon *icon)         {mIcon = icon;      }


    QString name() const                    {return mName;      }
    QString version() const                 {return mVersion;   }
    QString url() const                     {return mUrl;       }
    QString description() const             {return mDecription;}
    QIcon   *icon() const                   {return mIcon;      }

     Info & operator=(const Info &i);
protected:
    QString mName, mVersion, mUrl, mDecription;
    QIcon *mIcon;
};

} // end Tools namespace

#endif // INFO_H
