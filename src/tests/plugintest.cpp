#include <QString>
#include <QtTest/QtTest>

class PluginTest : public QObject
{
    Q_OBJECT
    
public:
    PluginTest();
    
private Q_SLOTS:
    void testCase1();
};

PluginTest::PluginTest()
{
}

void PluginTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PluginTest)

//#include "moc_plugintest.cxx"
