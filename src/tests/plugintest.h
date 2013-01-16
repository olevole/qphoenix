

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


