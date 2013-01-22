#ifndef QUERYWRAPPERS_H
#define QUERYWRAPPERS_H

#include <QThread>

#include "translatorinterface.h"


//class AbstractWrapper : public QThread {
//public:
//    virtual bool isReady() const = 0;
//    virtual QString errorString() const = 0;
//protected:
//    virtual void run() = 0;


//};




/*!
 * \brief The TranslatorWrapper class
 *
 * Wrapper for execute translation query
 * in separated thread
 *
 */



class TranslatorWrapper : public QObject
{
    Q_OBJECT
public:
    TranslatorWrapper(){}
    TranslatorWrapper(TranslatorInterface *ptr)
    {setTranslator(ptr);}

    void setTranslator(TranslatorInterface *ptr)
    {mPtr = ptr;}
public slots:
    void execute() {
        emit reply(mPtr->translate(mSrcText, mSrcLang, mDestLang));
    }

    void setParams(const QString &src_text, const QString &src_lang, const QString &dest_lang) {
        mSrcText = src_text;
        mSrcLang = src_lang;
        mDestLang = dest_lang;
    }
private:
    TranslatorInterface *mPtr;
    QString mSrcText, mSrcLang, mDestLang;

signals:
    void reply(QString);
};


//-------------------------------------------------------------------------------------


#endif // QUERYWRAPPERS_H
