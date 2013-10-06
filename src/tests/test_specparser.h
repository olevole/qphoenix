#pragma once

#include <QObject>

class Test_Specparser : public QObject
{
    Q_OBJECT
public:
    explicit Test_Specparser(QObject *parent = 0);

private slots:
    void parse();
};

