#ifndef QUERYWRAPPERS_H
#define QUERYWRAPPERS_H

#include <QThread>
#include <QTimer>

#include "itranslator.h"
#include "idictionary.h"

//-------------------------------------------------------------------------------------


class IWrapper : public QThread
{
    Q_OBJECT
public:
    IWrapper()
        :mTimer(new QTimer)
    {
        connect(mTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
        connect(mTimer, SIGNAL(timeout()), this, SLOT(quit()));
    }

    void setTimeout(const int msec)
    {
        mTimer->setInterval(msec);
    }

protected:
    void start(Priority priority = InheritPriority) {
        QThread::start(priority);
        mTimer->start();
    }
    QTimer *mTimer;
signals:
    void timeout();
};

//-------------------------------------------------------------------------------------


class DictionaryWrapper : public IWrapper {
    Q_OBJECT
public:
    DictionaryWrapper()
    {
        connect(this, SIGNAL(reply(DictionaryVariantList)), this, SLOT(quit()));
        connect(this, SIGNAL(reply(QStringList)), this, SLOT(quit()));

    }

    void run() {
        int count = mDictionaryList.count();
        if(!mSearchAll)
            count = 1;

        for(int i = 0; i < count; i++) {
//            DictionaryVariantList list = m_ptr->query(mQuery, mPair);
        }
//        emit reply(list);
    }

    void setDictionaryList(QList<IDictionary *> lst) { mDictionaryList = lst; }
    void setSearchAll(const bool b) { mSearchAll = b; }
public slots:
    void query(const LanguagePair &pair, const QString &query)  {
        mPair = pair;
        mQuery = query;

//        if(!m_ptr)
//            qFatal("Set DictionaryInterface before!");
//        start();
    }



signals:
    void reply(DictionaryVariantList);
    void reply(QStringList);
private:
    LanguagePair mPair;
    QString mQuery;
    bool mSearchAll;

    QList<IDictionary *>mDictionaryList;
//    IDictionary *m_ptr;
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

    void setTranslator(ITranslator *ptr)
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
    ITranslator *mPtr;
    QString mSrcText, mSrcLang, mDestLang;

signals:
    void reply(QString);
};


//-------------------------------------------------------------------------------------


#endif // QUERYWRAPPERS_H
