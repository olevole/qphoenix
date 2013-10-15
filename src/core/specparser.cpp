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

#include "specparser.h"

#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>



QPModuleSpecParser::QPModuleSpecParser(QObject *parent) :
    QObject(parent),
    mError(false)
{

}

void QPModuleSpecParser::keyError(const QString &key) {
    qWarning() << "Invalid spec format: cannot find key" << key << " in " << mSpecFile;
    mError = true;
}

QPModuleData QPModuleSpecParser::parse(const QString &specfile) {
    mError = false;
    mSpecFile = specfile;

    QPModuleData data;
    QFile file(specfile);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Cannot read spec file: " << specfile << " " << file.errorString();
        mError = true;
        return data;
    }
    QJsonObject root = QJsonDocument::fromJson(file.readAll()).object();

    if(!root.contains("qphoenix"))
        keyError("qphoenix");

    QJsonObject qphoenix_root = root.value("qphoenix").toObject();

    if(!qphoenix_root.contains("module"))
        keyError("module");

    QJsonObject module_root = qphoenix_root.value("module").toObject();

    const QString type = module_root.value("type").toString();

    if(type == "plugin")
        data.type = Plugin;
    else if(type == "dictionary")
        data.type = Dictionary;
    else if(type == "translator")
        data.type = Translator;
    else
        qWarning() << "Wrong module type: " << type;

    data.libname = module_root.value("libname").toString();

    if(!module_root.contains("info"))
        keyError("info");

    QJsonObject info = module_root.value("info").toObject();

    data.name = info.value("name").toString();
    data.description = info.value("description").toString();
    data.copyright = info.value("copyright").toString();
    data.version = info.value("version").toString();
    data.url = info.value("url").toString();

    if(module_root.contains("languages")) {
        QJsonObject languages = module_root.value("languages").toObject();
        QJsonObject::iterator it;;
        for(it = languages.begin(); it != languages.end(); it++) {
            const QString key = it.key();
            const QVariantList val = it.value().toArray().toVariantList();

            if(data.lang_table.contains(key)) {
                qWarning() << "Duplicate key: " << key;
                continue;
            }
            QStringList destlangs;
            foreach(QVariant var, val) {
                destlangs << var.toString();
            }
            data.lang_table[key] = destlangs;
        }
    }
    return data;
}

bool QPModuleSpecParser::hasError() {
    return mError;
}
