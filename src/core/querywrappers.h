#ifndef QUERYWRAPPERS_H
#define QUERYWRAPPERS_H

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "itranslator.h"
#include "idictionary.h"

//-------------------------------------------------------------------------------------


class IWorker : public QThread
{
    Q_OBJECT
public:
    IWorker()
        :mTimer(new QTimer)
    {
        connect(mTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
        connect(mTimer, SIGNAL(timeout()), this, SLOT(quit()));

        mTimer->setSingleShot(true);
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


class DictionaryWorker : public IWorker {
    Q_OBJECT
public:
    DictionaryWorker();

    void setDictionaryList(QList<IDictionary *> lst)
    { mDictionaryList = lst; }
protected:
    void run();
public slots:
    void query(const LanguagePair &pair, const QString &query);
signals:
    void reply(DictionaryVariantList);
    void reply(QStringList);
private:
    LanguagePair mPair;
    QString mQuery;
    QList<IDictionary *>mDictionaryList;
};

//-------------------------------------------------------------------------------------


/*!
 * \brief The TranslatorWrapper class
 * Wrapper for execute translation query in separated thread
 */

class TranslatorWorker : public IWorker
{
    Q_OBJECT
public:
    TranslatorWorker();

    void setTranslator(ITranslator *ptr)
    {mPtr = ptr;}
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


//-------------------------------------------------------------------------------------


#endif // QUERYWRAPPERS_H
