#pragma once

#include "iconfig.h"
#include "iconfigpage.h"
#include <QDialogButtonBox>
#include <QDialog>

class QListWidget;
class QStackedLayout;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QTreeWidgetItem;
class QPushButton;

#define QP_CONFIG_DIALOG_DEFAULT_WIDTH 800
#define QP_CONFIG_DIALOG_DEFAULT_HEIGH 600

class Config : public QDialog, public IConfig
{
    Q_OBJECT
    Q_INTERFACES(IConfig)
    Q_DISABLE_COPY(Config)
public:
    explicit Config(QWidget *parent = 0);
    ~Config();

    void addPage(QWidget *page, const QString &name, const QIcon &icon = QIcon());
    void removePage(QWidget *page);
    QWidget *pageAt(int i);
private:
    QList<IConfigPage *> mPagesList;

    QVBoxLayout *mMainLayout;
    QHBoxLayout *mHorizontalLayout;
    QHBoxLayout *mBottomLayout;
    QStackedLayout *mStackedLayout;
    QListWidget *mListWidget;
    QDialogButtonBox *mButtons;
    QPushButton *mDefaultsButton;
private slots:
    void onWidgetRemove(int idx);
    void save();
    void read();
    void reset();
};
