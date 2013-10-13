#include "commonconfig.h"

#include <QTabWidget>
#include <QCheckBox>
#include <QSettings>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

CommonConfig::CommonConfig(QWidget *parent) :
    QWidget(parent),
    mTabWidget(new QTabWidget(this)),
    mUseNativeCheckbox(new QCheckBox(this)),
    mLanguageCombobox(new QComboBox(this)),
    mLanguageLabel(new QLabel(this))
{
    mUseNativeCheckbox->setText(tr("Use native language names"));
    mLanguageLabel->setText(tr("Inteface language"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    mainLayout->addWidget(mTabWidget);

    QWidget *page1 = new QWidget(mTabWidget);
    QVBoxLayout *page1_layout = new QVBoxLayout;
    QHBoxLayout *languageLayout = new QHBoxLayout;
    languageLayout->addWidget(mLanguageLabel);
    languageLayout->addWidget(mLanguageCombobox);
    page1->setLayout(page1_layout);
    page1_layout->addWidget(mUseNativeCheckbox);
    page1_layout->addLayout(languageLayout);
    page1_layout->addStretch();

    mTabWidget->addTab(page1, tr("Language"));
}

void CommonConfig::save() {
    QSettings s;
    s.beginGroup("Common");
    s.setValue("UseNativeNames", mUseNativeCheckbox->isChecked());

}

void CommonConfig::read() {
    QSettings s;
    s.beginGroup("Common");
    mUseNativeCheckbox->setChecked(s.value("UseNativeNames", false).toBool());
}

void CommonConfig::reset() {
    mUseNativeCheckbox->setChecked(false);
}

bool CommonConfig::getNativeNamesEnabled() {
    return mUseNativeCheckbox->isChecked();
}
