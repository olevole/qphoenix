#include <QString>
#include <QtTest/QtTest>
#include "plugintest.h"


void PluginTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PluginTest)

