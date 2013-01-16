#ifndef LOADER_H
#define LOADER_H

#include <QObject>


class PluginTest : public QObject
{
    Q_OBJECT
public:
    PluginTest();
private slots:
    void testCase1();
    void testCase2();
    void testCase3();

};


#endif
