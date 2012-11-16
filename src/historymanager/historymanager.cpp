#include "historymanager.h"
#include "ui_historymanager.h"

#include <QFile>
#include <QDebug>

#include "src/common/defines.h"

HistoryManager::HistoryManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryManager)
{
    ui->setupUi(this);
    init();
    createConnections();
}

HistoryManager::~HistoryManager()
{
    delete ui;
}

int HistoryManager::count() const {
    return hdir.entryList().size();
}

void HistoryManager::init() {
    hdir.setPath(HISTORY_DIR);
}

void HistoryManager::createConnections() {
    connect(ui->filesListWidget, SIGNAL(currentRowChanged(int)),
            this, SLOT(tableChangeHandler(int)));

    connect(ui->delete_toolButton, SIGNAL(clicked()),
            this, SLOT(removeFile()));
    connect(ui->clear_toolButton, SIGNAL(clicked()),
            this, SLOT(clearFiles()));
    connect(ui->import_pushButton,(SIGNAL(clicked())),
            this, SLOT(import()));
}


void HistoryManager::removeFile() {
    int r = ui->filesListWidget->currentRow();
    QListWidgetItem *item = ui->filesListWidget->takeItem(r);
    ui->filesListWidget->removeItemWidget(item);
}

void HistoryManager::clearFiles() {
    ui->filesListWidget->clear();
}


void HistoryManager::updateTable() {

}

void HistoryManager::import() {

}

void HistoryManager::tableChangeHandler(const int i) {
    bool is_empty = (i == -1);
    ui->delete_toolButton->setDisabled(is_empty);
    ui->clear_toolButton->setDisabled(is_empty);


    if(hist_file.isOpen())
        hist_file.close();

    // Associate current row with agj file - required for XML parser.
    hist_file.setFileName(QString("%1%2%3%4")
                          .arg(HISTORY_DIR)
                          .arg(QDir::separator())
                          .arg(ui->filesListWidget->currentItem()->text())
                          .arg(".xml"));


    qDebug() << "State: " << ui->filesListWidget->count();
}

