#pragma once

#include <QtPlugin>
#include <QIcon>

class QWidget;


/*!
 * \brief The ConfigInterface class
 *
 * This interface allow plugins to access main
 * config dialog (add their own setting pages)
 */

class IConfig {
public:
    virtual ~IConfig() {}

    /*  Inserting Settings page into the main
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */
    virtual void addPage(QWidget *page, const QString &name, const QIcon &icon = QIcon()) = 0;

    /*!
     * \brief removePage removing page
     * \param page page to remove
     */
    virtual void removePage(QWidget *page) = 0;

    /*!
     * \brief pageAt returns page by index
     * \param index of page
     * \return page widget
     */
    virtual QWidget *pageAt(int i) = 0;
};

Q_DECLARE_INTERFACE(IConfig, "com.qphoenix.interfaces.configpage/1.0")

