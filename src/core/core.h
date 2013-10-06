#pragma once

#include <QObject>


class MainWindow;
class QPDictionaryThread;
class QPTranslatorThread;


class Core : public QObject
{
    Q_OBJECT
public:
    Core(MainWindow *mw, QObject *parent = 0);
    QPDictionaryThread *dictionaryWorker();
    QPTranslatorThread *translatorWorker();
    
signals:
    
public slots:
private:
    Core(QObject *parent = 0);
    Core();
    MainWindow *mMainWindow;
    
};




