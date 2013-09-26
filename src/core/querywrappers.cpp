#include "querywrappers.h"

DictionaryWorker::DictionaryWorker()
{
    connect(this, SIGNAL(reply(DictionaryVariantList)), this, SLOT(quit()));
    connect(this, SIGNAL(reply(QStringList)), this, SLOT(quit()));
    mCompletions = false;
}

void DictionaryWorker::run() {
    Q_ASSERT(!mPair.first.isEmpty() && !mPair.second.isEmpty());
    if(mQuery.isEmpty())
        return;
    //TODO: Solve this part
    if(mCompletions) {
        QStringList comp;
        foreach(IDictionary *dict, mDictList)
            if(dict->isSupportCompletions())
                comp += dict->completions(mQuery, mPair);
        comp.removeDuplicates();
        qDebug() << "Completions list: " << comp;
        if(comp.count() == 1)
            goto single;
        emit reply(comp);
    } else {
        single:
        qDebug() << "Creating reply...";
        foreach(IDictionary *dict, mDictList) {
            emit reply(dict->query(mQuery, mPair), dict->name());
        }
    }
    qDebug() << "Finished!";
    emit finished();
}

void DictionaryWorker::query(const LanguagePair &pair, const QString &query)
{
    mCompletions = false;
    mPair = pair;
    mQuery = query;
    start();
}

void DictionaryWorker::queryCompletions(const LanguagePair &pair, const QString &query)
{
    mCompletions = true;
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
