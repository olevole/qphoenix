#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QUrl>

typedef QMap<QString, QStringList> LanguageTable;

enum ModuleType {
    Plugin,
    Translator,
    Dictionary
};

struct ModuleSpecData {
    ModuleType type;
    QString name;
    QString description;
    QString libname;
    QString version;
    QString url;

    LanguageTable lang_table;
};

class ModuleSpecParser : public QObject {
    Q_OBJECT
public:
    ModuleSpecParser(QObject *parent = 0) {}
    ModuleSpecData parse(const QString &specfile);
private:
    void keyError(const QString &key);
    QString mSpecFile;
};
