#include <QTest>
#include <QDebug>
#include "test_specparser.h"
#include "specparser.h"

Test_Specparser::Test_Specparser(QObject *parent) :
    QObject(parent)
{
}

void Test_Specparser::parse()
{
    QPModuleSpecParser parser;

    QPModuleData data = parser.parse(QString(FILEPATH) +"/sample.spec");
    QVERIFY(!parser.hasError());

    QCOMPARE(data.type, Dictionary);
    QCOMPARE(QString(data.name), QString("Myplugin"));
    QCOMPARE(QString(data.url), QString("http://slashdot.com"));
    QCOMPARE(QString(data.description), QString("This is very nice plugin!"));
    QCOMPARE(QString(data.libname), QString("target.so"));

}

QTEST_MAIN(Test_Specparser)
