#include "querywrappers.h"
#include "defines.h"


void TranslatorWrapper::setTranslator(TranslatorInterface *ptr) {
    mReady = (ptr != NULL);
    if(!mReady)
        return;
    else
        mPtr = ptr;


    connect(this, SIGNAL(finished()), this, SIGNAL(reply(mResult)));
}


void TranslatorWrapper::run() {

    if(!isReady())
        return;

    exec();
    mResult = mPtr->translate(mSrcText, mSrcLang, mDestLang);
}



