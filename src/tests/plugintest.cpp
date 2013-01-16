#include <QString>
#include <QtTest/QtTest>
#include "plugintest.h"
#include "loader.h"
#include "plugininterface.h"
#include "translatorinterface.h"

PluginTest::PluginTest()
{
    QVERIFY2(true, "Failure");
//    QFAIL("Testfail!");

}

void PluginTest::testCase1() {
    Loader ldr;
    ldr.addSearchPath("/tmp/qphoenix-build/src/translators/mymemory");

    ModuleList list = ldr.modules();

    TranslatorInterface *iface = qobject_cast<TranslatorInterface *>(list.first());

    QVERIFY(iface->load());
}

void PluginTest::testCase2() {

}


void PluginTest::testCase3() {

}

QTEST_APPLESS_MAIN(PluginTest)

