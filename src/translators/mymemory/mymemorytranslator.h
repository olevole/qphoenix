#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "itranslator.h"
#include "info.h"
//#include "qxtjson.h"
#include <QObject>
#include <QCheckBox>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QDebug>



class MyMemoryTranslator : public QObject, ITranslator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qphoenix.translators.mymemory")
    Q_INTERFACES(ITranslator)
private:
    QWidget *mConfigWidget;
    bool mLoaded;
public:
    MyMemoryTranslator(QObject *parent = 0);

    bool load() {
        if(!isLoaded()) {
            mConfigWidget = new QWidget;
            mLoaded = true;
            return true;
        }
        return false;
    }

    bool unload() {
        if(isLoaded()) {
            delete mConfigWidget;
            mLoaded = false;
            return true;
        }
        return false;
    }
    bool isLoaded() const {return mLoaded;}


    QWidget *configWidget() {
        return new QCheckBox("test");
    }


    LanguageTable table() const {
        LanguageTable myTable;
        myTable["en"];
        myTable["ru"];
        myTable["de"];
        myTable["es"];
        return myTable;
    }

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang);
};

#endif // MYMEMORYTRANSLATOR_H
