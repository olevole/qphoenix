#ifndef SETTINGS_H
#define SETTINGS_H

#include "iconfig.h"
#include "iconfigpage.h"
#include <QTreeWidget>
#include <QDialogButtonBox>
#include <QDialog>

class QListWidget;
class QStackedLayout;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QTreeWidgetItem;
class QPushButton;

/*
 *  This is an implementation of main settings dialog.
 *  All config pages MUST include ConfigPageInteface.
 */

class Config : public QDialog,  IConfig
{
    Q_OBJECT
    Q_INTERFACES(IConfig)
    Q_DISABLE_COPY(Config)

    friend class MainWindow;
public:
    explicit Config(QWidget *parent = 0);
    ~Config();

    /*  Inserting Settings page into the main
     *  settings dialog. All settings pages are
     *  presented by the following interface:
     */
    void addPage(QWidget *page);
    void removePage(const QWidget *page);
    QWidget *pageAt(const int i);
protected:
    void addPage(QWidget *page, bool isplugin);
private:
    QList<IConfigPage *> mPagesList;

    // GUI elements
    QVBoxLayout *mMainLayout;
    QHBoxLayout *mHorizontalLayout;
    QHBoxLayout *mBottomLayout;
    QStackedLayout *mStackedLayout;
    QTreeWidget *mTree;
    QDialogButtonBox *mButtons;
    QPushButton *mDefaultsButton;
private slots:
    void itemChangeHandle();
    void save();
    void read();
    void reset();
};

#endif // SETTINGS_H
