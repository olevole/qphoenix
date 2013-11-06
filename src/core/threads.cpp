/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Copyright: QPhoenix team
 *    E-Mail: development@qphoenix.org
 *    Years: 2012-2013
 */

#include "threads.h"

QPDictionaryThread::QPDictionaryThread()
{
    mCompletions = false;
}

void QPDictionaryThread::run() {
    if(mQuery.isEmpty())
        return;

    if(mCompletions) {
        QStringList comp;
        foreach(QPDictionary dict, mDictList)
            if(dict.instance->isSupportCompletions())
                comp += dict.instance->completions(mQuery, mSrcLang, mDestLang);
            comp.removeDuplicates();
            emit reply(comp);
            return;
    }
    foreach(QPDictionary dict, mDictList) {
        IDictionary *idict = dict.instance;
        QStringList ret = idict->query(mQuery, mSrcLang, mDestLang);
        emit reply(ret, dict.data.name);
    }
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
