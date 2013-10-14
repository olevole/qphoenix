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

#pragma once

#include "iplugin.h"
#include <QObject>
#include <QTemporaryFile>

class QPushButton;
class QClipboard;
class QAction;
class QMediaPlayer;

#define TTS_URL "http://translate.google.com/translate_tts"

class Speech : public QObject, IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID "org.qphoenix.plugins.trayicon")
public:
    explicit Speech(QObject *parent = 0);
    void setPluginConnector(PluginConnector connector);

    bool load();
    bool unload();
    bool isLoaded() const { return mIsLoaded; }
    QString errorString() const {return QString();}
    void say(const QString &text, const QString &lang);
private slots:
    void pronounceSourceText();
    void pronounceResultText();
    void removeTmpFile();
private:
    ITranslationWidget *mTranslatorIface;
    bool mIsLoaded;
    QAction *mSpeechSourceAction;
    QAction *mSpeechResultAction;
    QMediaPlayer *mPlayer;
    QTemporaryFile mMp3File;
};
