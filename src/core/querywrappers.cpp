#include "querywrappers.h"


DictionaryWrapper::DictionaryWrapper()
{
    connect(this, SIGNAL(reply(DictionaryVariantList)), this, SLOT(quit()));
    connect(this, SIGNAL(reply(QStringList)), this, SLOT(quit()));

    mSearchAll = false;

}

void DictionaryWrapper::run()
{
    int count = mDictionaryList.count();

    if(!mSearchAll) count = 1;

    for(int i = 0; i < count; i++) {
        IDictionary *iface = mDictionaryList.at(i);
        if(iface == NULL) {
            qWarning("Invalid translator!");
            continue;
        }

        const QStringList c = iface->completions(mQuery, mPair);
        iface->completions(mQuery, mPair);
        iface->completions(mQuery, mPair);


//        if(c.size() > 1)
//            emit reply(c);
//        else
            emit reply(iface->query(mQuery, mPair));

    }
}


void DictionaryWrapper::query(const LanguagePair &pair, const QString &query)
{
    mPair = pair;
    mQuery = query;
    start();
}



//-------------------------------------------------------------------------------------


TranslatorWrapper::TranslatorWrapper()
    :mPtr(0)
{
    connect(this, SIGNAL(reply(QString)), this, SLOT(quit()));
}


void TranslatorWrapper::run()
{
    const QString _result = mPtr->translate(mSrcText, mSrcLang, mDestLang);
    emit reply(_result);
}

void TranslatorWrapper::query(const QString &src_lang, const QString &res_lang, const QString &src_text)
{
    mSrcLang = src_lang;
    mDestLang = res_lang;
    mSrcText = src_text;

    if(!mPtr)
        qFatal("Select TranslatorInterface Before!!!");

    start();
}
