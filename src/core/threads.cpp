#include "threads.h"

QPDictionaryThread::QPDictionaryThread()
{
    connect(this, SIGNAL(reply(DictionaryVariantList)), this, SLOT(quit()));
    connect(this, SIGNAL(reply(QStringList)), this, SLOT(quit()));
    mCompletions = false;
}

void QPDictionaryThread::run() {
//    Q_ASSERT(!mPair.first.isEmpty() && !mPair.second.isEmpty());
    if(mQuery.isEmpty())
        return;
    //TODO: Solve this part
    if(mCompletions) {
        QStringList comp;
        foreach(IDictionary *dict, mDictList)
            if(dict->isSupportCompletions())
                comp += dict->completions(mQuery, mSrcLang, mDestLang);
        comp.removeDuplicates();
        qDebug() << "Completions list: " << comp;
        if(comp.count() == 1)
            goto single;
        emit reply(comp);
    } else {
        single:
        qDebug() << "Creating reply...";
        foreach(IDictionary *dict, mDictList) {
//            emit reply(dict->query(mQuery, mPair), dict->name()); TODO
        }
    }
    qDebug() << "Finished!";
    emit finished();
}

void QPDictionaryThread::query(const QString &src_lang, const QString &dest_lang, const QString &query)
{
    mCompletions = false;
    mSrcLang = src_lang;
    mDestLang = dest_lang;
    mQuery = query;
    start();
}

void QPDictionaryThread::queryCompletions(const QString &src_lang, const QString &dest_lang, const QString &query)
{
    mCompletions = true;
    mSrcLang = src_lang;
    mDestLang = dest_lang;
    mQuery = query;
    start();
}


QPTranslatorThread::QPTranslatorThread()
    :mPtr(NULL)
{
    connect(this, SIGNAL(reply(QString)), this, SLOT(quit()));
}

void QPTranslatorThread::run()
{
    const QString _result = mPtr->translate(mSrcText, mSrcLang, mDestLang);
    emit reply(_result);
}

void QPTranslatorThread::query(const QString &src_lang, const QString &res_lang, const QString &src_text)
{
    Q_ASSERT(mPtr);
    Q_ASSERT(mPtr->isLoaded());
    mSrcLang = src_lang;
    mDestLang = res_lang;
    mSrcText = src_text;
    start();
}
