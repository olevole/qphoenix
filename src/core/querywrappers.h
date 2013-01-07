#ifndef QUERYWRAPPERS_H
#define QUERYWRAPPERS_H

#include <QThread>

#include "translatorinterface.h"


class AbstractWrapper : public QThread {
public:
    virtual bool isReady() const = 0;
    virtual QString errorString() const = 0;
protected:
    virtual void run() = 0;


};




/*!
 * \brief The TranslatorWrapper class
 *
 * Wrapper for execute translation query
 * in separated thread
 *
 */



class TranslatorWrapper : public AbstractWrapper
{
    Q_OBJECT
public:
    TranslatorWrapper(){}
    TranslatorWrapper(TranslatorInterface *ptr) {
        setTranslator(ptr);
    }

    void setTranslator(TranslatorInterface *ptr);


    void execQuery(const QString &src_text, const QString &src_lang,
                      const QString &dest_lang) {
        mSrcText = src_text;
        mSrcLang = src_lang;
        mDestLang = dest_lang;

        this->run();
    }

    virtual bool isReady() const { return mReady; }
    // Not implemented yet
    virtual QString errorString() const {}
protected:
    virtual void run();
private:
    TranslatorInterface *mPtr;
    bool mReady;

    QString mSrcText, mSrcLang, mDestLang, mResult;
signals:
    void reply(QString);
};




#endif // QUERYWRAPPERS_H
