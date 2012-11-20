#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QDialog>
#include <QDir>
#include <QtXml/QDomDocument>

namespace Ui {
class HistoryManager;
}

class QFile;



class HistoryManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit HistoryManager(QWidget *parent = 0);
    ~HistoryManager();

    // Count of history files
    int count() const;

    // Path to currently opened file
//    QString fileName() const;
private:
    Ui::HistoryManager *ui;
    QDir hdir;
    QFile hist_file;
    QDomDocument dom_doc;

    void init();
    void createConnections();


    // Reutrns path to html file generated from xml.
    QString generateHtml() const;

    // True if html are valid, othervise - false
    bool validateHtml(const QString &path) const;

    // Load history files to left panel
    void loadFiles();
private slots:
    void removeFile();
    void clearFiles();
    void updateTable();
    void import();

    void tableChangeHandler(const int i);



};

#endif // HISTORYMANAGER_H
