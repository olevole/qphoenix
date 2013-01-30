#include <QString>
#include <QtTest/QtTest>
#include "plugintest.h"
#include "loader.h"
#include "iplugin.h"
#include "itranslator.h"

PluginTest::PluginTest()
{
    QVERIFY2(true, "Failure");
//    QFAIL("Testfail!");

}

void PluginTest::testCase1() {
    Loader ldr;
    ldr.addSearchPath("/tmp/qphoenix-build/src/translators/mymemory");

    QObjectList list = ldr.modules();

    ITranslator *iface = qobject_cast<ITranslator *>(list.first());

    QVERIFY(iface->load());
}

void PluginTest::testCase2() {

}


void PluginTest::testCase3() {

}

QTEST_APPLESS_MAIN(PluginTest)

