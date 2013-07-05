#pragma once

#include <QObject>

class MainWindow;
class DictionaryWorker;
class TranslatorWorker;


class Core : public QObject
{
    Q_OBJECT
public:
    Core(MainWindow *mw, QObject *parent = 0);
    DictionaryWorker *dictionaryWorker();
    TranslatorWorker *translatorWorker();
    
signals:
    
public slots:
private:
    Core(QObject *parent = 0);
    Core();
    MainWindow *mMainWindow;
    
};
