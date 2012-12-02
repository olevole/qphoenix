#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;
class QTextBrowser;
class QLayout;
class QGroupBox;
class QStatusBar;
class QToolBar;

namespace Gui {

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QString srcLang() const;
    QString resbpiLang() const;
    QString srcText() const;
    QString resText() const;




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
