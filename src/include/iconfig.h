#pragma once

#include <QGroupBox>

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
    virtual void addPage(QWidget *page, bool is_plugin = false) = 0;

    /*!
     * \brief removePage removing page
     * \param page page to remove
     */
    virtual void removePage(const QWidget *page) = 0;

    /*!
     * \brief pageAt returns page by index
     * \param index of page
     * \return page widget
     */
    virtual QWidget *pageAt(const int i) = 0;
};

Q_DECLARE_INTERFACE(IConfig, "com.qphoenix.interfaces.settingspage/1.0")

