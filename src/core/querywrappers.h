#ifndef QUERYWRAPPERS_H
#define QUERYWRAPPERS_H

#include <QThread>
#include <QTimer>

#include "translatorinterface.h"
#include "dictionaryinterface.h"

//-------------------------------------------------------------------------------------


class IWrapper : public QThread
{
public:
    IWrapper()
        :mTimer(new QTimer)
    {
        connect(mTimer, SIGNAL(timeout()), this, SLOT(quit()));
    }

    void setTimeout(const int msec)
    {
        mTimer->setInterval(msec);
    }

protected:
    void start(Priority priority = InheritPriority) {
        QThread::start(priority);
    }
private:
    QTimer *mTimer;
};

//-------------------------------------------------------------------------------------


class DictionaryWrapper : public IWrapper {
    Q_OBJECT
public:
    DictionaryWrapper()
        :m_ptr(0)
    {
        connect(this, SIGNAL(reply(DictionaryVariantList)), this, SLOT(quit()));
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
    LanguagePair mPair;
    QString mQuery;
    DictionaryInterface *m_ptr;
};

//-------------------------------------------------------------------------------------


/*!
 * \brief The TranslatorWrapper class
 *
 * Wrapper for execute translation query
 * in separated thread
 *
 */



class TranslatorWrapper : public IWrapper
{
    Q_OBJECT
public:
    TranslatorWrapper()
        :mPtr(0)
    {
        connect(this, SIGNAL(reply(QString)), this, SLOT(quit()));
    }

    void setTranslator(TranslatorInterface *ptr)
    {mPtr = ptr;}

    void run() {
        const QString _result = mPtr->translate(mSrcText, mSrcLang, mDestLang);
        emit reply(_result);
    }

public slots:
    void query(const QString &src_lang, const QString &res_lang, const QString &src_text) {
        mSrcLang = src_lang;
        mDestLang = res_lang;
        mSrcText = src_text;

        if(!mPtr)
            qFatal("Select TranslatorInterface Before!!!");

        start();
    }


private:
    TranslatorInterface *mPtr;
    QString mSrcText, mSrcLang, mDestLang;

signals:
    void reply(QString);
};


//-------------------------------------------------------------------------------------


#endif // QUERYWRAPPERS_H
