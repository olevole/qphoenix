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
#include <QMediaPlaylist>


#include "translationwidget.h"
#include "itranslatorwidget.h"
#include "speech.h"
#include "http.h"

Speech::Speech(QObject *parent) :
    QObject(parent),
    mIsLoaded(false)
{
    this->setName("Speech");
    this->setDescription("Text to speech plugin");
    this->setVersion("0.999999");
    mMp3File.setFileTemplate(QDir::tempPath() + "/qphoenixXXXXX.mp3");
}

bool Speech::load() {
    if(!isLoaded()) {
        mSpeechAction = new QAction("Say it!", 0);
        mPlayer = new QMediaPlayer;
        mConnector.QP_TRANSLATOR_WIDGET->srcToolbar()->addAction(mSpeechAction);
        connect(mSpeechAction, SIGNAL(triggered()), this, SLOT(say()));
        connect(mPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(removeTmpFile()));
        mIsLoaded = true;
    }
    return true;
}

bool Speech::unload() {
    qDebug() << "UNLOADING!";
    if(isLoaded()) {
        disconnect(mSpeechAction, SIGNAL(triggered()), this, SLOT(say()));
        disconnect(mPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(removeTmpFile()));
        delete mSpeechAction;
        delete mPlayer;
        mIsLoaded = false;
    }
    qDebug() << "UNLOADED!";
    return true;
}

void Speech::say() {
    if(mPlayer->state() == QMediaPlayer::PlayingState)
        return;
    const QString text = mConnector.QP_TRANSLATOR_WIDGET->srcText()->toPlainText();
    const QString lang = "en";
    const QUrl url  = QString(TTS_URL) + QString("?tl=%1&q=%2").arg(lang, text);
    const QByteArray filedata = HTTP::GET(url);
    mMp3File.open();
    mMp3File.setAutoRemove(false);
    mMp3File.write(filedata);
    mMp3File.close();

    mPlayer->setMedia(QUrl::fromLocalFile(mMp3File.fileName()));
    mPlayer->play();


    qDebug() << "URL____" << url.toString();
    qDebug() << "PATH____" << mMp3File.fileName();

}

void Speech::removeTmpFile() {
    if (mPlayer->state() == QMediaPlayer::StoppedState)
        mMp3File.remove();
}

void Speech::setPluginConnector(PluginConnector connector) {
    mConnector = connector;
}
