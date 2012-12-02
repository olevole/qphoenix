#include "exceptions.h"
#include "ui_exceptions.h"

Exceptions::Exceptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exceptions)
{
    ui->setupUi(this);
}

Exceptions::~Exceptions()
{
    delete ui;
}
