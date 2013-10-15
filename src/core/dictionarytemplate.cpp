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

#include "dictionarytemplate.h"
#include <QDebug>

DictionaryTemplate::DictionaryTemplate(QObject *parent)
    :QObject(parent),
     mLastSectionClosed(true),
     mTemplateRoot(getTemplate(":/templates/templates/root.html")),
     mTemplateSection(getTemplate(":/templates/templates/section.html")),
     mTemplateItem(getTemplate(":/templates/templates/item.html"))
{
}

void DictionaryTemplate::beginSection(const QString &title, const bool collapseable) {
    if(!mLastSectionClosed) {
        qWarning()<< "Dictionary  template section isn't closed, unable to open new one";
        return;
    }
    mLastSectionClosed = false;
    mTitle = title;
}

void DictionaryTemplate::createSection(const QStringList &lst, const QString &title, const bool collapseable) {
    beginSection(title, collapseable);
    foreach(QString v, lst)
        addItem(v);
    endSection();
}

void DictionaryTemplate::addItem(const QString &str) {
    QString s = mTemplateItem;
    mSection += s.replace("{ITEM_DATA}", bb2html(str));
}

void DictionaryTemplate::endSection() {
    QString s = mTemplateSection;
    mRoot += s.replace("{SECTION_CONTENT}", mSection)
            .replace("{SECTION_TITLE}", mTitle)
            .replace("{SECTION_ID}", mTitle + QString::number(qrand() % ((100 + 1) - 1) + 1));
    mSection.clear();
    mLastSectionClosed = true;
}

void DictionaryTemplate::clear() {
    mRoot.clear();
    mTitle.clear();
    endSection();
}

QString DictionaryTemplate::bb2html(const QString &bb) {
    QString str = bb;
    str.replace("[b]", "<b>", Qt::CaseInsensitive).replace("[/b]", "</b>", Qt::CaseInsensitive);
    str.replace("[i]", "<i>", Qt::CaseInsensitive).replace("[/i]", "</i>", Qt::CaseInsensitive);
    str.replace("[u]", "<u>", Qt::CaseInsensitive).replace("[/u]", "</u>", Qt::CaseInsensitive);
    str.replace("[quote]", "<blockquote><p>", Qt::CaseInsensitive).replace("[/quote]", "</p></blockquote>", Qt::CaseInsensitive);
    str.replace("\n", "<br>");
    return str;
}

QString DictionaryTemplate::toHtml() const {
    if(!mLastSectionClosed)
        return QString("ERROR");
    QString s = mTemplateRoot;
    return s.replace("{ROOT_CONTENT}", mRoot);
}
