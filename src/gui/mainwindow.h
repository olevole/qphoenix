#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pluginapi.h"

class QTextEdit;
class QTextBrowser;
class QLayout;
class QGroupBox;
class QStatusBar;
class QToolBar;
class Ui_MainWindow;

namespace Gui {


class MainWindow : public QMainWindow, Api::MainWindowAPI
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString srcLang() const {return "ru";}
    QString resbpiLang() const { return "en";}
    QString srcText() const { return "en";}
    QString resText() const { return "en";}
    
private:


    Ui_MainWindow *ui;



signals:
    // Signals for plugins
    void translationInitiated(const QString &src_text);
    void translationFinished(const QString &src_text, const QString &res_text);

    void sourceLanguageChanged();
    void resultLanguageChanged();
    void languagesSwapped();
};

}// end Gui namespace

#endif // MAINWINDOW_H
