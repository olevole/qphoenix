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

#include <QtMsgHandler>
#include <QFile>
#include <QIcon>
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "mainwindow.h"
#include "defines.h"

#include "loader.h"
#include "specparser.h"

void qpMsgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
#ifdef QP_DEBUG
    case QtDebugMsg:
        fprintf(stderr, "[Debug]:  %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
#endif
    case QtWarningMsg:
        fprintf(stderr, "[Warning]:  %s \n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[Critical]:  %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "[Fatal]: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(qpMsgHandler);

    QCoreApplication::setApplicationName(QP_APP_NAME);
    QCoreApplication::setApplicationVersion(QP_APP_VERSION);
    QCoreApplication::setOrganizationName(QP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(QP_ORG_DOMAIN);

    QDir::addSearchPath("plugins", QP_PLUGINS_PATH);
    QDir::addSearchPath("translators", QP_TRANSLATORS_PATH);
    QDir::addSearchPath("dictionaries", QP_DICTIONARIES_PATH);

    MainWindow mw;
    mw.show();
    mw.setWindowIcon(QP_ICON("dictionary"));

    return a.exec();
}
