#ifndef INFODIALOG_H
#define INFODIALOG_H

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

#endif // INFODIALOG_H
