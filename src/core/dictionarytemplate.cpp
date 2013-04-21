#include "dictionarytemplate.h"





DictionaryTemplate::DictionaryTemplate()
    :mTemplateRoot(getTemplate(":/templates/root.html")),
     mTemplateSection(getTemplate(":/templates/section.html")),
     mTemplateItem(getTemplate(":/templates/item.html")),
     mLastSectionClosed(true)

{
    qDebug() << mTemplateRoot << mTemplateItem <<mTemplateSection;
}


void DictionaryTemplate::beginSection(const QString &title, const bool collapseable) {
    if(!mLastSectionClosed) {
        qWarning()<< "Dictionary  template section isn't closed, unable to open new one";
        return;
    }
    mLastSectionClosed = false;

}

void DictionaryTemplate::beginSection(const DictionaryVariantList &lst, const QString &title, const bool collapseable) {
    beginSection(title, collapseable);
    foreach(DictionaryVariant v, lst)
        addItem(v);

}


bool DictionaryTemplate::addItem(const DictionaryVariant &var) {

}


void DictionaryTemplate::endSection() {
    mLastSectionClosed = true;
}


QString DictionaryTemplate::bb2html(const QString &bb) const {
    QString str = bb;
    str.replace("[b]", "<b>").replace("[/b]", "</b>", Qt::CaseInsensitive);
    str.replace("[i]", "<i>").replace("[/i]", "</i>", Qt::CaseInsensitive);
    str.replace("[u]", "<u>").replace("[/u]", "</u>", Qt::CaseInsensitive);
    str.replace("[quote]", "<blockquote><p>").replace("[/quote]", "</p></blockquote>", Qt::CaseInsensitive);
    str.replace("\n", "<br>");

    return str;
}
