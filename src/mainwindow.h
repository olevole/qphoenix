#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;


signals:
    // Signals for plugins
    void translationInitiated(const QString &src_text);
    void translationFinished(const QString &src_text, res_text);
};

#endif // MAINWINDOW_H
