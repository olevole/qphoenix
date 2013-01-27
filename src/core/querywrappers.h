#ifndef QUERYWRAPPERS_H
#define QUERYWRAPPERS_H

#include <QThread>

#include "translatorinterface.h"
#include "dictionaryinterface.h"



class DictionaryWrapper : public QThread {
    Q_OBJECT
public:
    DictionaryWrapper()
        :m_ptr(0)
    {
        connect(this, SIGNAL(reply(QString)), this, SLOT(quit()));
    }

    void run() {
        DictionaryVariantList list = m_ptr->query(mPair, mQuery);
        emit reply(list);
    }

    void setDictionary(DictionaryInterface *iface)
    {m_ptr = iface;}

public slots:
    void query(const LanguagePair &pair, const QString &query)  {
        mPair = pair;
        mQuery = query;

        if(!m_ptr)
            qFatal("Set DictionaryInterface before!");

        start();
    }

signals:
    void reply(DictionaryVariantList);
private:

    void start(Priority priority = InheritPriority) {
        QThread::start(priority);
    }

    LanguagePair mPair;
    QString mQuery;
    DictionaryInterface *m_ptr;
};


/*!
 * \brief The TranslatorWrapper class
 *
 * Wrapper for execute translation query
 * in separated thread
 *
 */



class TranslatorWrapper : public QTh
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
