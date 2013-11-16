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

#include "api.h"
#include <QObject>

#define DICTIONARY_VERSION "0.99"

class QNetworkAccessManager;
class QJsonDocument;

class YandexDictionary : public QObject, IDictionary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.dictionaries.wordreference")
    Q_INTERFACES(IDictionary)
public:
    YandexDictionary(QObject *parent = 0);

    QStringList query(const QString &text, const QString &src_lang, const QString &dest_lang, unsigned int max_count);
    QStringList completions(const QString &str, const QString &src_lang, const QString &dest_lang) const;

    bool load() {return true;}
    bool unload() {return true;}
    bool isLoaded() const {return true;}

    bool isSupportCompletions() {return true;}
private:
    static QString mApiKey;
    QString parseTree(QJsonObject root, bool header = false);

//    QString parseText(QJsonObject &text);
//    QString mLastData;
};
