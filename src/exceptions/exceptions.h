#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QDialog>

namespace Ui {
class Exceptions;
}

class Exceptions : public QDialog
{
    Q_OBJECT
    
public:
    explicit Exceptions(QWidget *parent = 0);
    ~Exceptions();
    
private:
    Ui::Exceptions *ui;

    void addException();
    void removeException();
    void clear();
};

#endif // EXCEPTIONS_H
