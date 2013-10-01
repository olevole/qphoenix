#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QUrl>

typedef QMap<QString, QStringList> LanguageTable;

enum QPModuleType {
    Plugin,
    Translator,
    Dictionary
};

struct QPModuleData {
    QPModuleType type;
    QString name;
    QString description;
    QString libname;
    QString version;
    QString url;

    LanguageTable lang_table;
};

class QPModuleSpecParser : public QObject {
    Q_OBJECT
public:
    QPModuleSpecParser(QObject *parent = 0) {}
    QPModuleData parse(const QString &specfile);
private:
    void keyError(const QString &key);
    QString mSpecFile;
};
