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

#include <QtGui>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include <QTextBrowser>
#include <QToolTip>
#include <QMediaPlayer>

#include "speech.h"
#include "http.h"

Speech::Speech(QObject *parent) :
    QObject(parent),
    mIsLoaded(false)
{
    mMp3File.setFileTemplate(QDir::tempPath() + "/qphoenixXXXXX.mp3");
}

bool Speech::load() {
    if(!isLoaded()) {
        mSpeechSourceAction = new QAction(QIcon(":icons/media-playback-start.png"), "Say it!", 0);
        mSpeechResultAction = new QAction(QIcon(":icons/media-playback-start.png"),"Say it!", 0);

        mPlayer = new QMediaPlayer;
        mTranslatorIface->addToolbarAction(mSpeechSourceAction, ITranslationWidget::SourceTextToolbar);
        mTranslatorIface->addToolbarAction(mSpeechResultAction, ITranslationWidget::ResultTextToolbar);

        connect(mSpeechSourceAction, SIGNAL(triggered()), this, SLOT(pronounceSourceText()));
        connect(mSpeechResultAction, SIGNAL(triggered()), this, SLOT(pronounceResultText()));
        connect(mPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(removeTmpFile()));
        mIsLoaded = true;
    }
    return true;
}

bool Speech::unload() {
    if(isLoaded()) {
        disconnect(mSpeechSourceAction, SIGNAL(triggered()), this, SLOT(pronounceSourceText()));
        disconnect(mSpeechResultAction, SIGNAL(triggered()), this, SLOT(pronounceResultText()));
        disconnect(mPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(removeTmpFile()));
        delete mSpeechSourceAction;
        delete mSpeechResultAction;
        delete mPlayer;
        mIsLoaded = false;
    }
    return true;
}

void Speech::pronounceSourceText() {
    const QString text = mTranslatorIface->getSourceText();
    const QString lang = mTranslatorIface->getSourceLanguageCode();
    say(text, lang);
}

void Speech::pronounceResultText() {
    const QString text = mTranslatorIface->getResultText();
    const QString lang = mTranslatorIface->getResultLanguageCode();
    say(text, lang);
}


void Speech::say(const QString &text, const QString &lang) {
    if(text.isEmpty() || lang.isEmpty() || mPlayer->state() == QMediaPlayer::PlayingState)
        return;

    const QUrl url  = QString(TTS_URL) + QString("?tl=%1&q=%2").arg(lang, text);
    const QByteArray filedata = HTTP::GET(url);
    mMp3File.open();
    mMp3File.setAutoRemove(false);
    mMp3File.write(filedata);
    mMp3File.close();

    mPlayer->setMedia(QUrl::fromLocalFile(mMp3File.fileName()));
    mPlayer->play();
}

void Speech::removeTmpFile() {
    if (mPlayer->state() == QMediaPlayer::StoppedState)
        mMp3File.remove();
}

void Speech::setPluginConnector(PluginConnector connector) {
    mTranslatorIface = connector.translationwidget;
}
