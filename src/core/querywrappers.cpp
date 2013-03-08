#include "querywrappers.h"


DictionaryWorker::DictionaryWorker()
{
    connect(this, SIGNAL(reply(DictionaryVariantList)), this, SLOT(quit()));
    connect(this, SIGNAL(reply(QStringList)), this, SLOT(quit()));
}

void DictionaryWorker::run()
{
    Q_ASSERT(mDict->isLoaded());
    Q_ASSERT(!mQuery.isEmpty());
    Q_ASSERT(!mPair.first.isEmpty() && !mPair.second.isEmpty());


    const QStringList c = mDict->completions(mQuery, mPair);

    //TODO: Solve this part
//    if(!c.count() <= 1)
//        emit reply(c);
//    else
        emit reply(mDict->query(mQuery, mPair));
}


void DictionaryWorker::query(const LanguagePair &pair, const QString &query)
{
    mPair = pair;
    mQuery = query;
    start();
}



//-------------------------------------------------------------------------------------


TranslatorWorker::TranslatorWorker()
    :mPtr(NULL)
{
    connect(this, SIGNAL(reply(QString)), this, SLOT(quit()));
}


void TranslatorWorker::run()
{
    const QString _result = mPtr->translate(mSrcText, mSrcLang, mDestLang);
    emit reply(_result);
}

void TranslatorWorker::query(const QString &src_lang, const QString &res_lang, const QString &src_text)
{
    Q_ASSERT(mPtr);
    Q_ASSERT(mPtr->isLoaded());

    mSrcLang = src_lang;
    mDestLang = res_lang;
    mSrcText = src_text;

    start();
}
