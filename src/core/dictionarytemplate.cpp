#include "dictionarytemplate.h"


DictionaryTemplate::DictionaryTemplate(QObject *parent)
    :QObject(parent),
     mTemplateRoot(getTemplate(":/templates/root.html")),
     mTemplateSection(getTemplate(":/templates/section.html")),
     mTemplateItem(getTemplate(":/templates/item.html")),
     mLastSectionClosed(true)

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

bool DictionaryTemplate::addItem(const QString &str) {
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
    str.replace("[b]", "<b>").replace("[/b]", "</b>", Qt::CaseInsensitive);
    str.replace("[i]", "<i>").replace("[/i]", "</i>", Qt::CaseInsensitive);
    str.replace("[u]", "<u>").replace("[/u]", "</u>", Qt::CaseInsensitive);
    str.replace("[quote]", "<blockquote><p>").replace("[/quote]", "</p></blockquote>", Qt::CaseInsensitive);
    str.replace("\n", "<br>");
    return str;
}

QString DictionaryTemplate::toHtml() const {
    if(!mLastSectionClosed)
        return QString("ERROR");
    QString s = mTemplateRoot;
    return s.replace("{ROOT_CONTENT}", mRoot);
}
