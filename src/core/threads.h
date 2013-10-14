 #pragma once

#include <QThread>
#include <QTimer>
#include <QDebug>
#include "itranslator.h"
#include "idictionary.h"
#include "dictionaryconfig.h"


class IThread : public QThread
{
    Q_OBJECT
public:
    IThread()
        :mTimer(new QTimer(this))
    {
        connect(mTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
        connect(mTimer, SIGNAL(timeout()), this, SLOT(quit()));

        mTimer->setSingleShot(true);
        setTimeout(100000000);
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


class QPDictionaryThread : public IThread {
    Q_OBJECT
public:
    QPDictionaryThread();
    QPDictionaryThread(QPDictionaryList lst) {
        QPDictionaryThread();
        this->setDictionaryList(lst);
    }
    void setDictionaryList(QPDictionaryList &lst){ mDictList = lst; }
    int count(){ return mDictList.count();}
protected:
    void run();
public slots:
    void query(const QString &src_lang, const QString &dest_lang, const QString &query);
    void queryCompletions(const QString &src_lang, const QString &dest_lang, const QString &query);
signals:
    void reply(QStringList, QString);
    void reply(QStringList);
    void finished();
private:
    bool mCompletions;
    QString mSrcLang;
    QString mDestLang;
    QString mQuery;
    QPDictionaryList mDictList;
};

/*!
 * \brief The TranslatorWrapper class
 * Wrapper for execute translation query in separated thread
 */

class QPTranslatorThread : public IThread
{
    Q_OBJECT
public:
    QPTranslatorThread();
    QPTranslatorThread(ITranslator *t) {
        setTranslator(t);
    }
    void setTranslator(ITranslator *ptr){mPtr = ptr;}
    ITranslator *translator(){return mPtr;}
protected:
    void run();
public slots:
    void query(const QString &src_lang, const QString &res_lang, const QString &src_text);
private:
    ITranslator *mPtr;
    QString mSrcText, mSrcLang, mDestLang;
signals:
    void reply(QString);
};
