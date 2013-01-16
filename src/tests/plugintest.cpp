#include <QString>
#include <QtTest/QtTest>
#include "plugintest.h"
#include "loader.h"


PluginTest::PluginTest()
{
    QVERIFY2(true, "Failure");
//    QFAIL("Testfail!");

}

void PluginTest::testCase1() {


}

void PluginTest::testCase2() {

}


void PluginTest::testCase3() {

}

QTEST_APPLESS_MAIN(PluginTest)

