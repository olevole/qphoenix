#ifndef DICTIONARYTEMPLATE_H
#define DICTIONARYTEMPLATE_H

#include <QObject>
#include "api.h"
#include <QFile>

/*!
 * \brief The DictionaryTemplate class
 * This class is a wrapper for html templates for dictionary QWebView
 * display widget.
 */

class DictionaryTemplate : public QObject {
public:
    explicit DictionaryTemplate();


    /*!
     * \brief beginSection create a document section
     * \param title section title
     * \param collapseable
     */
    void beginSection(const QString &title, const bool collapseable = true);

    /*!
     * \brief beginSection create a document section with items
     * \param lst a list of items
     * \param title title of section
     * \param collapseable could that section be collapsed?
     */
    void beginSection(const DictionaryVariantList &lst, const QString &title, const bool collapseable = true);



    /*!
     * \brief addItem add item for current section
     * \param var
     * \return true if beginSection was set correct
     * false - otherwise
     */
    bool addItem(const DictionaryVariant &var);


    /*!
     * \brief endSection end of section
     */
    void endSection();

    QString document() const;
    QString errorString() const;
private:
    bool mLastSectionClosed;
    QString mRoot, mTitle;

    const QString mTemplateRoot;
    const QString mTemplateSection;
    const QString mTemplateItem;


    /*!
     * \brief bb2html turns bbcode string to html
     * \param bb bbcoded string
     * \return  html
     */
    QString bb2html(const QString &bb) const;


    inline QString getTemplate(const QString &path) const {
        QFile f(path);

        if(!f.open(QFile::ReadOnly))
            qFatal("Unable to open templates for dictionary!");

        const QByteArray data = f.readAll();
        f.close();
        return data;
    }
};

#endif // DICTIONARYTEMPLATE_H