#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pluginapi.h"
#include "fancytabwidget.h"

class QTextEdit;
class QTextBrowser;
class QLayout;
class QGroupBox;
class QStatusBar;
class QToolBar;
class Ui_MainWindow;

namespace Gui {


class MainWindow : public  QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString srcLang() const { return "ru";}
    QString resLang() const { return "en";}
    QString srcText() const { return "en";}
    QString resText() const { return "en";}
private:


    Ui_MainWindow *ui;



signals:
//    void languageChange();
public slots:
//    void setSou

};

}// end Gui namespace

#endif // MAINWINDOW_H
