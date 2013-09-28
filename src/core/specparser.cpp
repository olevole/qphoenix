#include "specparser.h"

#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


void ModuleSpecParser::keyError(const QString &key) {
    qWarning() << "Invalid spec format: cannot find key'" << key << "' in :" << mSpecFile;
}

ModuleSpecData ModuleSpecParser::parse(const QString &specfile) {
    mSpecFile = specfile;

    ModuleSpecData data;
    QFile file(specfile);
    if(!file.open(QFile::ReadOnly)) {
        qWarning() << "Cannot parse spec file: " << specfile;
        return data;
    }

    QJsonObject root = QJsonDocument::fromJson(file.readAll()).object();

    if(!root.contains("qphoenix"))
        keyError("qphoenix");

    QJsonObject qphoenix_root = root.value("qphoenix").toObject();

    if(!qphoenix_root.contains("module"))
        keyError("module");


    QJsonObject module_root = qphoenix_root.value("module").toObject();

    data.type = module_root.value("type").toString();
    data.libname = module_root.value("libname").toString();

    if(!module_root.contains("info"))
        keyError("info");

    QJsonObject info = module_root.value("info").toObject();

    data.name = info.value("name").toString();
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
