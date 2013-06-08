#pragma once

#include <QDialog>

class QDialogButtonBox;

class InfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InfoDialog(QWidget *parent = 0);
private:
    QDialogButtonBox *buttons;
};
