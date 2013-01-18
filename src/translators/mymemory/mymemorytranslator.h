#ifndef MYMEMORYTRANSLATOR_H
#define MYMEMORYTRANSLATOR_H

#include "../../include/translatorinterface.h"
#include "../../include/info.h"
#include <QObject>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QDebug>

class MyMemoryTranslator : public QObject, TranslatorInterface
{
    Q_OBJECT
    Q_INTERFACES(TranslatorInterface)
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
//        QCheckBox *cb = new QCheckBox;
//        cb->setText("Disable google?");

//        return cb;
        return mConfigWidget;

    }

    bool isLinear() const{ return false; }

    LanguageTable table() const {
        QStringList english;

        english << "Russian" << "German" << "Spanish";

        QStringList russian;
        russian << "German" << "English";


        QStringList german;
        german << "Russian" << "English";

        QStringList spanish;
        spanish << "German" << "Russian";

        LanguageTable myTable;
        myTable["English"] = english;
        myTable["Russian"] = russian;
        myTable["German"] = german;
        myTable["Spanish"] = spanish;

        return myTable;

        qDebug() << "Keys2: " << myTable.keys();



    }

    QString translate(const QString &src_text, const QString &src_lang, const QString &dest_lang) {

        return QString("Result text | " + src_text);
    }
};

#endif // MYMEMORYTRANSLATOR_H
