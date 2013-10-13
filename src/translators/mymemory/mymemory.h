#pragma once

#include "itranslator.h"
#include <QObject>
#include <QCheckBox>

class MyMemory : public QObject, ITranslator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.translators.mymemory")
    Q_INTERFACES(ITranslator)
private:
    bool mLoaded;
public:
    MyMemory(QObject *parent = 0);

    bool load() {
        mLoaded = true;
        return true;
    }

    bool unload() {
        mLoaded = false;
        return true;
    }

    bool isLoaded() const {return mLoaded;}

    QWidget *configWidget() {
        return new QCheckBox("test");
    }

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang);
};

