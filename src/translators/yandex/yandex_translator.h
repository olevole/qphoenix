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

#include "itranslator.h"
#include <QObject>


class YandexTranslator : public QObject, ITranslator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.translators.yandex")
    Q_INTERFACES(ITranslator)
private:
    bool mLoaded;
    static QStringList mLangs;
    static QString mApiKey;
public:
    YandexTranslator(QObject *parent = 0);

    bool load() {
        mLoaded = true;
        return true;
    }

    bool unload() {
        mLoaded = false;
        return false;
    }
    bool isLoaded() const {return mLoaded;}

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang);
};
